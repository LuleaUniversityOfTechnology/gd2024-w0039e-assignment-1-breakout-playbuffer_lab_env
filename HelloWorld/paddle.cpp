#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "paddle.h"
using namespace std;

void DrawPaddle(const Paddle& p)
{
	Play::Point2f topRight = Play::Point2f(p.xPos + p.width/2, p.yPos + p.height/2);
	Play::Point2f bottomLeft = Play::Point2f(p.xPos - p.width/2, p.yPos - p.height/2);
	Play::DrawRect(bottomLeft, topRight, Play::cCyan, true);
}

void UpdatePaddle(Paddle& p)
{
	int keyLeft = Play::KeyDown(Play::KeyboardButton::KEY_LEFT);
	int keyRight = Play::KeyDown(Play::KeyboardButton::KEY_RIGHT);
	int moveDir = keyRight - keyLeft;
	p.xPos += 5 * moveDir;
}

bool IsColliding(const Paddle& p, const Play::GameObject& obj)
{
	Play::Point2f topRight = Play::Point2f(p.xPos + p.width / 2, p.yPos + p.height / 2);
	Play::Point2f bottomLeft = Play::Point2f(p.xPos - p.width / 2, p.yPos - p.height / 2);
	const float dx = obj.pos.x - Min(topRight.x, Max(obj.pos.x, bottomLeft.x));
	const float dy = obj.pos.y - Min(topRight.y, Max(obj.pos.y, bottomLeft.y));
	return (dx * dx + dy * dy) < (obj.radius * obj.radius);
}

float Max(float a, float b)
{
	return a > b ? a : b;
}

float Min(float a, float b)
{
	return a < b ? a : b;
}
