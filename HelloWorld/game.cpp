#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "game.h"
#include "Play.h"
#include "paddle.h"
#include "constants.h"
#include <fstream>
#include <array>
#include <string>
using namespace std;

Paddle playerPaddle;

//Creates the initial instance of the ball object and sets its velocity
void SpawnBall() 
{
	const int objectId = Play::CreateGameObject(ObjectType::TYPE_BALL, { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2 }, 4, "ball");
	GameObject& ball = Play::GetGameObject(objectId);
	ball.velocity = normalize({ rand(), rand()}) * ballSpeed;
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

		//Loop through vector and draw each brick in it
		for (int brickId : brickIds)
		{
			GameObject& brick = Play::GetGameObject(brickId);
			Play::UpdateGameObject(brick);
			Play::DrawObject(brick);
			for (int ballId : ballIds)
			{
				GameObject& ball = Play::GetGameObject(ballId);
				//Destroy brick if colliding with ball and reverse ball's velocity and increase the playerScore by 1
				if (BrickCollision(brickId, ball))
				{
					Play::DestroyGameObject(brickId);
					playerScore++;
					break;
				}
			}
		}

		//Check for wall collision
		if (ball.pos.x > DISPLAY_WIDTH || ball.pos.x < 0)
		{
			ball.velocity.x *= -1;
		}
		else if (ball.pos.y > DISPLAY_HEIGHT)
		{
			ball.velocity.y *= -1;
		}
		//If ball hits the bottom of the screen
		else if (ball.pos.y < 0)
		{
			//Put playerScore into proper placement in highScore
			//Destroy ball and bricks
			//Reset the score and scene and respawn ball
			SaveScore(playerScore);
			Play::DestroyGameObject(ballId);
			for (int brickId : brickIds)
			{
				Play::DestroyGameObject(brickId);
			}
			playerScore = 0;
			SetupScene();
			SpawnBall();
			break;
		}
		//Check for paddle collision
		else if (IsColliding(playerPaddle, ball))
		{
			ball.velocity.y *= -1;
		}
		Play::UpdateGameObject(ball);
		Play::DrawObject(ball);
	}

	//Update and draw the paddle
	UpdatePaddle(playerPaddle);
	DrawPaddle(playerPaddle);

	//Draw top five high scores at bottom right of screen
	for (int i = 0; i < highScoresSize; i++)
	{
		Play::DrawDebugText(Play::Point2D(DISPLAY_WIDTH - 10, 70 - 15*i), to_string(highScores[i]).c_str(), Play::cWhite, true);
	}

	//Draw player score at bottom left of screen
	Play::DrawDebugText(Play::Point2D(10, 10), to_string(playerScore).c_str(), Play::cWhite, true);
}

//Creates all the brick objects
void SetupScene()
{
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
	
	//initialize playerPaddle position and dimensions
	playerPaddle.xPos = DISPLAY_WIDTH / 2;
	playerPaddle.yPos = 8;
	playerPaddle.width = 100;
	playerPaddle.height = 8;
}

//Takes in a score and enters it into the top five scores and sorts the array
void SaveScore(int score)
{
	for (int i = 0; i < highScoresSize; i++)
	{
		int curScore = highScores[i];
		if (score > curScore)
		{
			highScores[i] = score;
			i++;
			//Re-sort all scores following the new score
			while (i < highScoresSize)
			{
				int nextScore = highScores[i];
				highScores[i] = curScore;
				curScore = nextScore;
				i++;
			}
			break;
		}
	}
}

void CreateManagers()
{
	Play::CreateManager(DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE);
}

//Takes in two game objects and checks if they are colliding
bool BrickCollision(int brick, Play::GameObject& obj2)
{
	GameObject& obj1 = Play::GetGameObject(brick);
	Vector2f obj1SpriteSize = Play::Graphics::GetSpriteSize(obj1.spriteId);
	//Vector2f obj2SpriteSize = Play::Graphics::GetSpriteSize(obj2.spriteId);
	Play::Point2f topRight = Play::Point2f(obj1.pos.x + obj1SpriteSize.width / 2, obj1.pos.y + obj1SpriteSize.height / 2);
	Play::Point2f bottomLeft = Play::Point2f(obj1.pos.x - obj1SpriteSize.width / 2, obj1.pos.y - obj1SpriteSize.height / 2);
	const float dx = obj2.pos.x - Min(topRight.x, Max(obj2.pos.x, bottomLeft.x));
	const float dy = obj2.pos.y - Min(topRight.y, Max(obj2.pos.y, bottomLeft.y));
	if ((dx * dx + dy * dy) < (obj2.radius * obj2.radius))
	{
		if (dx != 0)
		{
			obj2.velocity.x *= -1;
		}
		else if (dy != 0)
		{
			obj2.velocity.y *= -1;
		}
		return true;
	}
	else
	{
		return false;
	}
}

//Writes highscores to a text file and frees the allocated memory of the array highScores
void SaveScores()
{
	ofstream highscores;
	highscores.open("highscores.txt", ofstream::out | ofstream::trunc);
	if (highscores.is_open())
	{
		//for each element in highScores, put it in its own line in the text document
		for (int i = 0; i < highScoresSize; i++)
		{
			highscores << highScores[i];
			if (i + 1 < highScoresSize)
			{
				highscores << "\n";
			}
		}
		highscores.close();
	}
	delete[] highScores;
}

//Reads the file "highscores.txt" and puts each line of the document into the array as its own element
void LoadScores()
{
	ifstream highscores;
	highscores.open("highscores.txt");
	string score;
	int i = 0;
	highScoresSize = GetFileLineCount("highscores.txt");
	highScores = new unsigned int[highScoresSize];
	while (getline(highscores, score))
	{
		highScores[i] = stoi(score);
		i++;
	}
	highscores.close();
}

//Takes in a string filename and returns the number of lines in that text file
int GetFileLineCount(string fileName)
{
	ifstream file;
	file.open(fileName);
	int lineCount = 0;
	string line;
	while (getline(file, line))
	{
		lineCount++;
	}
	file.close();
	return lineCount;
}
