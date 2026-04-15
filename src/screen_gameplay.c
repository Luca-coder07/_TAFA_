#include "tafa.h"
#include "level.h"

static int framesCounter = 0;
static int finishScreen = 0;
static t_player player;
static t_level level;

void InitGameplayScreen(void)
{
	framesCounter = 0;
	finishScreen = 0;
	LoadLevel(&level, currentSubScreen);
	InitPlayer(&player);
}

void UpdateGameplayScreen(float dt)
{
	UpdateLevel(&level, dt, &player);
	if (IsKeyPressed(KEY_ENTER))
	{
		finishScreen = 1;
		if (IsAudioDeviceReady() && fxCoinLoaded) PlaySound(fxCoin);
	}
}

void DrawGameplayScreen(void)
{
	DrawLevel(level, player);
}

void UnloadGameplayScreen(void)
{
	UnloadLevel(&level);
	UnloadPlayer(&player);
}

int FinishGameplayScreen(void)
{
	return finishScreen;
}
