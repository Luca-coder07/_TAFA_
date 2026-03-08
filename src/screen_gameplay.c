#include "screens.h"

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;
static t_player	player;

//----------------------------------------------------------------------------------
// Gameplay Screen Functions Definition
//----------------------------------------------------------------------------------

// Gameplay Screen Initialization logic
void InitGameplayScreen(void)
{
	// TODO: Initialize GAMEPLAY screen variables here!
	framesCounter = 0;
	finishScreen = 0;

	InitPlayer(&player);
}

// Gameplay Screen Update logic
void UpdateGameplayScreen(float dt)
{
	// TODO: Update GAMEPLAY screen variables here!
	UpdatePlayer(&player, dt);
	// Press enter or tap to change to ENDING screen
	if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
	{
		finishScreen = 1;
		if (IsAudioDeviceReady() && fxCoinLoaded) PlaySound(fxCoin);
	}
}

// Gameplay Screen Draw logic
void DrawGameplayScreen(void)
{
    // TODO: Draw GAMEPLAY screen here!
    DrawRectangle(0, SCREEN_HEIGHT - 50, SCREEN_WIDTH, SCREEN_HEIGHT, GRAY);
    DrawLineEx((Vector2){0, SCREEN_HEIGHT - 50}, (Vector2){SCREEN_WIDTH, SCREEN_HEIGHT - 50}, 5, BLACK);
    DrawPlayer(player);
}

// Gameplay Screen Unload logic
void UnloadGameplayScreen(void)
{
    // TODO: Unload GAMEPLAY screen variables here!
    UnloadPlayer(&player);
}

// Gameplay Screen should finish?
int FinishGameplayScreen(void)
{
    return finishScreen;
}
