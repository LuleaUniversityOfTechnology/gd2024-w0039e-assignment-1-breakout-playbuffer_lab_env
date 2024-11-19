#pragma once
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"

struct Paddle
{
	float xPos;
	float yPos;
	float width;
	float height;
};

void DrawPaddle(const Paddle& p);
void UpdatePaddle(Paddle& p);
bool IsColliding(const Paddle& p, const Play::GameObject& obj);
float Max(float a, float b);
float Min(float a, float b);



