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
	ClearBackground(WHITE); // Use a clean white background

    const float titleFontSize = font.baseSize * 6.0f;
    Vector2 titleTextSize = MeasureTextEx(font, "TAFA", titleFontSize, 2);
    Vector2 titlePos = { (screen_width - titleTextSize.x) / 2, 60 };
    DrawTextEx(font, "TAFA", titlePos, titleFontSize, 2, BLACK);

    const float menuFontSize = font.baseSize * 2.5f;
    const float menuSpacing = menuFontSize * 1.8f;
    float menuStartY = screen_height / 2 - menuSpacing;

    const char *menuItems[] = {"Play", "Options", "Quit"};
    const int menuCount = 3;

    for (int i = 0; i < menuCount; i++) {
        Vector2 textSize = MeasureTextEx(font, menuItems[i], menuFontSize, 2);
        Vector2 pos = { (screen_width - textSize.x) / 2, menuStartY + i * menuSpacing };

        Color color = (hover_state == i) ? BLACK : GRAY;

        if (hover_state == i) {
            Rectangle highlightRec = { pos.x - 20, pos.y - 5, textSize.x + 40, textSize.y + 10 };
            DrawRectangleRec(highlightRec, BLACK);
            DrawTextEx(font, menuItems[i], (Vector2){pos.x, pos.y}, menuFontSize, 2, WHITE);
        } else {
            DrawTextEx(font, menuItems[i], pos, menuFontSize, 2, color);
        }
    }
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
