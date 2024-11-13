#ifndef PADDLE_H
#define PADDLE_H
#include "Play.h"
#include "game.h"

// Struct to define the paddle object, with position, width, and height
struct Paddle {
    Play::Vector2f position; // Position of the paddle
    float width = 75.0f;  // Default width of the paddle
    float height = 15.0f; // Default height of the paddle

    Paddle(float x, float y) : position(x, y) {}     // Constructor to initialize the paddle position
};

void DrawPaddle(const Paddle& paddle); // Draws the paddle on the screen
void UpdatePaddle(Paddle& paddle, float elapsedTime); // Updates paddle position based on user input and frame time

bool IsColliding(const Paddle& paddle, const Play::GameObject& obj);

#endif
