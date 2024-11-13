#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "game.h"
#include "paddle.h"

using namespace Play;
// Screen dimensions and scaling factor for the display
int DISPLAY_WIDTH = 630;
int DISPLAY_HEIGHT = 360;
int DISPLAY_SCALE = 2;

// Function to create a ball object and initialize its velocity
void SpawnBall() {
    const int objectId = Play::CreateGameObject(ObjectType::TYPE_BALL, { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT - 130 }, 4, "ball");
    GameObject& ball = Play::GetGameObject(objectId);
    ball.velocity = Play::normalize({ 1, -1 }) * BALL_SPEED;
}

// Global paddle instance with initial position
Paddle paddle(DISPLAY_WIDTH / 2 - 50, DISPLAY_HEIGHT - 330); // Initial paddle position

// Function to set up the initial game scene with bricks and other objects
void SetupScene()
{
    const int brickWidth = 15;
    const int brickHeight = 10;
    const int padding = 2;
    const int numRows = 6;
    const int numColumns = 37;

    const int startY = 275; // Starting vertical position for brick rows

    // Create grid of brick objects
    for (int row = 0; row < numRows; ++row)
    {
        for (int col = 0; col < numColumns; ++col)
        {
            int x = col * (brickWidth + padding);
            int y = startY + row * (brickHeight + padding);

            if (y < 0) {
                y = 0;
            }
            // Create brick game object at the calculated position
            Play::CreateGameObject(ObjectType::TYPE_BRICK, { x, y }, 6, "brick");
        }
    }
}
// Updates all game objects on each frame based on the elapsed time
void StepFrame(float elapsedTime) {
    static Paddle paddle(DISPLAY_WIDTH / 2 - 50, DISPLAY_HEIGHT - 340);
    const std::vector<int> ballIds = Play::CollectGameObjectIDsByType(ObjectType::TYPE_BALL);
    const std::vector<int> brickIds = Play::CollectGameObjectIDsByType(ObjectType::TYPE_BRICK); 

    const float brickWidth = 40.0f;
    const float brickHeight = 10.0f;
    // Process each ball's movement and boundary collision
    for (int ballid : ballIds) {
        Play::GameObject& ball = Play::GetGameObject(ballid);
        ball.pos += ball.velocity * elapsedTime;
        if (IsColliding(paddle, ball)) {
            ball.velocity.y = -ball.velocity.y;
        }
        // Reverse direction on horizontal boundary collision
        if (ball.pos.x <= 0 || ball.pos.x >= DISPLAY_WIDTH)
        {
            ball.velocity.x = -ball.velocity.x;
        }
        // Reverse direction on vertical boundary collision
        if (ball.pos.y <= 0 || ball.pos.y >= DISPLAY_HEIGHT)
        {
            ball.velocity.y = -ball.velocity.y;
        }
       
       Play::DrawObject(ball);
    }
    // Check for brick collisions with each ball
    for (int id : brickIds) {
        GameObject& brick = Play::GetGameObject(id);
        Play::DrawObject(brick);

        for (int ballId : ballIds)
        {
            GameObject& ball = Play::GetGameObject(ballId);
            float brickLeft = brick.pos.x;
            float brickRight = brick.pos.x + brickWidth;
            float brickTop = brick.pos.y;
            float brickBottom = brick.pos.y + brickHeight;

            // Detect and respond to collision between ball and brick
            if (Play::IsColliding(ball, brick)) {
                Play::DestroyGameObject(id);
                // Adjust ball direction based on collision position
                if (ball.pos.x < brickLeft || ball.pos.x > brickRight) {
                    ball.velocity.x = -ball.velocity.x;
                }
                if (ball.pos.y < brickTop || ball.pos.y > brickBottom) {
                    ball.velocity.y = -ball.velocity.y;
                }
                break;
            }
        }
    }
    // Update paddle based on player input
    UpdatePaddle(paddle, elapsedTime);
    DrawPaddle(paddle);
}