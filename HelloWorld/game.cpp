#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "game.h"
#include "Play.h"
#include "paddle.h"
#include "constants.h"
using namespace std;

Paddle playerPaddle;

void SpawnBall() 
{
	const int objectId = Play::CreateGameObject(ObjectType::TYPE_BALL, { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2 }, 4, "ball");
	GameObject& ball = Play::GetGameObject(objectId);
	ball.velocity = normalize({ 1, -1 }) * ballSpeed;
}

//The function StepFrame takes in a float value that represents the elapsed time since last step
//Takes one simulation step and renders a single frame of the application
void StepFrame(float elapsedTime)
{

	//Returns a vector that contains the object ids for all balls that have been created
	const vector<int> ballIds = Play::CollectGameObjectIDsByType(TYPE_BALL);
	const vector<int> brickIds = Play::CollectGameObjectIDsByType(TYPE_BRICK);

	//Loop through vector and draw each ball in it
	for (int ballId : ballIds)
	{
		GameObject& ball = Play::GetGameObject(ballId);
		if (ball.pos.x > DISPLAY_WIDTH || ball.pos.x < 0)
		{
			ball.velocity.x *= -1;
		}
		else if (ball.pos.y > DISPLAY_HEIGHT || ball.pos.y < 0)
		{
			ball.velocity.y *= -1;
		}
		//Check for paddle collision
		else if (IsColliding(playerPaddle, ball))
		{
			ball.velocity.y *= -1;
		}
		Play::UpdateGameObject(ball);
		Play::DrawObject(ball);
	}

	//Loop through vector and draw each brick in it
	for (int brickId : brickIds)
	{
		GameObject& brick = Play::GetGameObject(brickId);
		Play::UpdateGameObject(brick);
		Play::DrawObject(brick);
		for (int ballId : ballIds)
		{
			GameObject& ball = Play::GetGameObject(ballId);
			if (Play::IsColliding(brick, ball))
			{
				Play::DestroyGameObject(brickId);
				ball.velocity *= -1;
			}
		}
	}

	//Draw the paddle
	UpdatePaddle(playerPaddle);
	DrawPaddle(playerPaddle);
}

//Creates all the brick objects
void SetupScene()
{
	Play::CreateManager(DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE);

	//Create bricks
	//int brickHeight = Play::GetSpriteHeight(Play::GetGameObjectByType(ObjectType::TYPE_BRICK).spriteId);
	//int brickWidth = Play::GetSpriteWidth(Play::GetGameObjectByType(ObjectType::TYPE_BRICK).spriteId);
	for (int i = 6; i < DISPLAY_WIDTH - 18; i += 18)
	{
		for (int j = DISPLAY_HEIGHT - 12; j > DISPLAY_HEIGHT - 9 * 12; j -= 12)
		{
			Play::CreateGameObject(ObjectType::TYPE_BRICK, { i, j }, 6, "brick");
		}	
	}
	
	//initialize paddle position
	playerPaddle.xPos = DISPLAY_WIDTH / 2;
	playerPaddle.yPos = 8;
	playerPaddle.width = 100;
	playerPaddle.height = 8;
}

