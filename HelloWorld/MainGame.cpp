#include "Play.h"
#include "game.h"

// Entry point for the game - initializes the game manager and scene
void MainGameEntry(PLAY_IGNORE_COMMAND_LINE)
{
    Play::CreateManager(DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE);
    SetupScene();
    SpawnBall();
}
// Main game loop, called once per frame
bool MainGameUpdate(float elapsedTime)
{
    Play::ClearDrawingBuffer(Play::cBlack);// Clear screen

    StepFrame(elapsedTime); // Update game objects

    Play::PresentDrawingBuffer(); // Render the frame
    return Play::KeyDown(Play::KeyboardButton::KEY_ESCAPE); // Exit on Escape key
}

// Cleanup when the game exits
int MainGameExit(void)
{
    Play::DestroyManager();
    return PLAY_OK;
}