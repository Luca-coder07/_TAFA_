#include "screens.h"

typedef enum { PLAY, OPTION, QUIT } HoverState;
//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;
static HoverState hover_state = PLAY;
//----------------------------------------------------------------------------------
// Title Screen Functions Definition
//----------------------------------------------------------------------------------

// Title Screen Initialization logic
void InitTitleScreen(void)
{
	// TODO: Initialize TITLE screen variables here!
	framesCounter = 0;
	finishScreen = 0;
	hover_state = PLAY;
}

// Title Screen Update logic
void UpdateTitleScreen(void)
{
	// TODO: Update TITLE screen variables here!
	if (IsKeyPressed(KEY_UP)) { 
		if (hover_state == PLAY) hover_state = QUIT;
		else hover_state--;
	}
	if (IsKeyPressed(KEY_DOWN)) {
		if (hover_state == QUIT) hover_state = PLAY;
		else hover_state++;
	}

	// Press enter or tap to change to GAMEPLAY screen
	if (IsKeyPressed(KEY_ENTER))
	{
		if (hover_state == PLAY) finishScreen = 2;   // GAMEPLAY
		if (hover_state == OPTION) finishScreen = 1;   // OPTIONS
		if (hover_state == QUIT) gameShouldClose = true;   // QUIT - close game
		// Play sound only if audio device is ready
		if (IsAudioDeviceReady() && fxCoinLoaded) PlaySound(fxCoin);
	}
}

// Title Screen Draw logic
void DrawTitleScreen(void)
{
	// TODO: Draw TITLE screen here!
	Vector2 pos = { SCREEN_WIDTH / 2 - MeasureTextEx(font, "TAFA", font.baseSize*5.0f, 4).x / 2, 50};
	DrawTextEx(font, "TAFA", pos, font.baseSize*5.0f, 4, GRAY);
    
	Vector2 pos_1 = { hover_state == PLAY ? 10 + font.baseSize : 10, SCREEN_HEIGHT / 2 - MeasureTextEx(font, "Hilalao", font.baseSize, 2).y };
	Vector2 pos_2 = { hover_state == OPTION ? 10 + font.baseSize : 10, SCREEN_HEIGHT / 2 + MeasureTextEx(font, "PARAMETRES", font.baseSize, 2).y };
	Vector2 pos_3 = { hover_state == QUIT ? 10 + font.baseSize : 10, font.baseSize*2.0f + SCREEN_HEIGHT / 2 + MeasureTextEx(font, "Hiala", font.baseSize, 2).y };
	Vector2 pos_cursor = { 10,  pos_1.y };
	if (hover_state == PLAY) pos_cursor.y = pos_1.y;
	if (hover_state == OPTION) pos_cursor.y = pos_2.y;
	if (hover_state == QUIT) pos_cursor.y = pos_3.y;

	DrawTextEx(font, "> ", pos_cursor, font.baseSize*2.0f, 2, BLACK);
	DrawTextEx(font, "Hilalao", pos_1, font.baseSize*2.0f, 2, hover_state == PLAY ? BLACK : GRAY);
	DrawTextEx(font, "PARAMETRES", pos_2, font.baseSize*2.0f, 2, hover_state == OPTION ? BLACK : GRAY);
	DrawTextEx(font, "Hiala", pos_3, font.baseSize*2.0f, 2, hover_state == QUIT ? BLACK : GRAY);
}

// Title Screen Unload logic
void UnloadTitleScreen(void)
{
    // TODO: Unload TITLE screen variables here!
}

// Title Screen should finish?
int FinishTitleScreen(void)
{
    return finishScreen;
}
