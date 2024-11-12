#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "Game.h"
#include "paddle.h"


Paddle paddle;


void SpawnBall()
{
	const int objectId = Play::CreateGameObject(ObjectType::TYPE_BALL, { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT - 350 }, 4, "ball");
	GameObject& ball = Play::GetGameObject(objectId);
	ball.velocity = normalize({ 1, 1 }) * ballSpeed;
}

void StepFrame(float timePassed)
{
	const std::vector<int> brickIds = Play::CollectGameObjectIDsByType(TYPE_BRICK);
	const std::vector<int> ballIds = Play::CollectGameObjectIDsByType(TYPE_BALL);

	DrawPaddle(paddle);
	
	
	for (int brick : brickIds)
	{
		GameObject& currentBrick = Play::GetGameObject(brick);
		for (int ball : ballIds)
		{
			GameObject& currentBall = Play::GetGameObject(ball);
			if (Play::IsColliding(currentBrick, currentBall))
			{
				Play::DestroyGameObject(brick);
				currentBall.velocity *= -1;
			}
		}
		

		Play::UpdateGameObject(Play::GetGameObject(brick));
		Play::DrawObject(Play::GetGameObject(brick));
	}


	
	for (int ball : ballIds)
	{
		GameObject& obj_ball = Play::GetGameObject(ball);
		if ((obj_ball.pos.x > DISPLAY_WIDTH-5) || (obj_ball.pos.x < 0))
		{
			obj_ball.velocity.x *= -1;
		}

		if ((obj_ball.pos.y > DISPLAY_HEIGHT-5) || (obj_ball.pos.y < 0))
		{
			obj_ball.velocity.y *= -1;
		}

		Play::UpdateGameObject(Play::GetGameObject(ball));
		Play::DrawObject(Play::GetGameObject(ball));
	}
}


void SetupScene()
{
	for (int x = 6; x < DISPLAY_WIDTH-5; x+=17)
	{
		for (int y = DISPLAY_HEIGHT-15; y > 200; y-=11)
		{
			const int objectId = Play::CreateGameObject(ObjectType::TYPE_BRICK, { x, y }, 6, "brick");
		}
	}
}
