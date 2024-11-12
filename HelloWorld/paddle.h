#pragma once
#include "Constants.h"
#include "Play.h"

struct Paddle
{
	Play::Point2D position = { DISPLAY_WIDTH/2, 20 };
	int width = 50;
	int height = 8;
};

void MovePaddle(Paddle& paddle, float elapsedTime);

void DrawPaddle(Paddle& paddle);
