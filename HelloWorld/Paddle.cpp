#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "constants.h"
#include "paddle.h"

using namespace Play;

// Draws the paddle as a filled rectangle
void DrawPaddle(const Paddle& paddle) {
    float paddleWidth = 75.0f;
    float paddleHeight = 15.0f;

    Play::Vector2f topLeft(paddle.position.x, paddle.position.y);
    Play::Vector2f bottomRight(paddle.position.x + paddleWidth, paddle.position.y + paddleHeight);

    Play::Colour col = Play::cOrange;// Set paddle color

    Play::DrawRect(topLeft, bottomRight, col, true);
}
// Updates the paddle position based on player input and ensures it stays within screen bounds
void UpdatePaddle(Paddle& paddle, float elapsedTime) {
    float paddleSpeed = 200.0f; // Paddle speed in pixels per second
    float paddleWidth = 75.0f; // Paddle width for boundary checks

    // Move paddle left on key press
    if (Play::KeyDown(Play::KeyboardButton::KEY_LEFT)) {
        paddle.position.x -= paddleSpeed * elapsedTime;
    }
    // Move paddle right on key press
    if (Play::KeyDown(Play::KeyboardButton::KEY_RIGHT)) {
        paddle.position.x += paddleSpeed * elapsedTime;
    }
    // Ensure paddle stays within screen bounds
    if (paddle.position.x < 0) {
        paddle.position.x = 0;
    }
    else if (paddle.position.x + paddleWidth > DISPLAY_WIDTH) {
        paddle.position.x = DISPLAY_WIDTH - paddleWidth;
    }
}
// Returns the maximum of two values
float Max(float a, float b) {
    return (a > b) ? a : b;
}
// Returns the minimum of two values
float Min(float a, float b) {
    return (a < b) ? a : b;
}
bool IsColliding(const Paddle& paddle, const Play::GameObject& obj) {
    Play::Vector2f paddleTopLeft(paddle.position.x, paddle.position.y);
    Play::Vector2f paddleBottomRight(paddle.position.x + paddle.width, paddle.position.y + paddle.height);

    const float dx = obj.pos.x - Max(paddleTopLeft.x, Min(obj.pos.x, paddleBottomRight.x));
    const float dy = obj.pos.y - Max(paddleTopLeft.y, Min(obj.pos.y, paddleBottomRight.y));

    return (dx * dx + dy * dy) < (obj.radius * obj.radius);
}