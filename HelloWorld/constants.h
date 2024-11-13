#pragma once
// Display dimensions and scale factors for the game screen
extern int DISPLAY_WIDTH;
extern int DISPLAY_HEIGHT;
extern int DISPLAY_SCALE;

// Enum for different object types in the game
enum ObjectType {
	TYPE_BALL, // Represents a ball object
	TYPE_BRICK, // Represents a brick object
};

// Speed constant for ball movement
#define BALL_SPEED 150.0f;