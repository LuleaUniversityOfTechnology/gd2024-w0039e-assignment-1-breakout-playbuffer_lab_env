#include "paddle.h"

void MovePaddle(Paddle& paddle, float translationX)
{
	paddle.position.x += translationX;
}

void DrawPaddle(Paddle& paddle)
{
	const Play::Point2D bottomLeft = { paddle.position.x - (paddle.width / 2), paddle.position.y };
	const Play::Point2D topRigth = { paddle.position.x + (paddle.width / 2), paddle.position.y + paddle.height };
	Play::DrawRect(bottomLeft, topRigth, Play::cRed, true);
}
