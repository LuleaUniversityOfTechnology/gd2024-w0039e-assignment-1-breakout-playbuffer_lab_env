#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "paddle.h"
using namespace std;

//Takes in a paddle and draws it from its defined variables
void DrawPaddle(const Paddle& p)
{
	Play::Point2f topRight = Play::Point2f(p.xPos + p.width/2, p.yPos + p.height/2);
	Play::Point2f bottomLeft = Play::Point2f(p.xPos - p.width/2, p.yPos - p.height/2);
	Play::DrawRect(bottomLeft, topRight, Play::cCyan, true);
}

//Takes in a paddle and updates its x value based on keyboard input
void UpdatePaddle(Paddle& p)
{
	int keyLeft = Play::KeyDown(Play::KeyboardButton::KEY_LEFT);
	int keyRight = Play::KeyDown(Play::KeyboardButton::KEY_RIGHT);
	int moveDir = keyRight - keyLeft;
	p.xPos += 5 * moveDir;
}

//Checks if the paddle is colliding with a game object
//takes in a paddle object and a game object
//returns true if paddle and passed in game object are colliding, else false
bool IsColliding(const Paddle& p, const Play::GameObject& obj)
{
	Play::Point2f topRight = Play::Point2f(p.xPos + p.width / 2, p.yPos + p.height / 2);
	Play::Point2f bottomLeft = Play::Point2f(p.xPos - p.width / 2, p.yPos - p.height / 2);
	const float dx = obj.pos.x - Min(topRight.x, Max(obj.pos.x, bottomLeft.x));
	const float dy = obj.pos.y - Min(topRight.y, Max(obj.pos.y, bottomLeft.y));
	return (dx * dx + dy * dy) < (obj.radius * obj.radius);
}

//Takes in two floats and returns the greater of the two using the ternary operator
float Max(float a, float b)
{
	return a > b ? a : b;
}

//Takes in two floats and returns the lesser of the two using the ternary operator
float Min(float a, float b)
{
	return a < b ? a : b;
}
