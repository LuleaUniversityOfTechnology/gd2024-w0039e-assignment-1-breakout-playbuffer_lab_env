#pragma once
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "constants.h"

// Spawns a ball at the initial location
void SpawnBall();

// Updates game objects based on the time elapsed in each frame
void StepFrame(float elapsedTime);

// Sets up the initial scene layout with bricks and other objects
void SetupScene();