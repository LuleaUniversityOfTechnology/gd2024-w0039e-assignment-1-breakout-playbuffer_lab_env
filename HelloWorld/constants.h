#pragma once

int DISPLAY_WIDTH = 640;
int DISPLAY_HEIGHT = 360;
int DISPLAY_SCALE = 2;

float ballSpeed = 5;

int highScoresSize = 0;
unsigned int* highScores = new unsigned int[highScoresSize];
int playerScore = 0;

enum ObjectType 
{
	TYPE_BALL,
	TYPE_BRICK
};