#pragma once
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "paddle.h"

void SpawnBall();
void StepFrame(float elapsedTime);
void SetupScene();
void SaveScore(int score);
void CreateManagers();
bool BrickCollision(int brick, Play::GameObject& obj2);
void SaveScores();
void LoadScores();




