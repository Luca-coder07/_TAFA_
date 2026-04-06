#ifndef TYPES_H
#define TYPES_H

#include "raylib.h"

typedef enum GameScreen
{
	UNKNOWN = -1,
	LOGO = 0,
	TITLE,
	OPTIONS,
	GAMEPLAY,
	ENDING
} GameScreen;
typedef enum SubGameScreen
{
	LEVEL_1,
	LEVEL_2,
	LEVEL_3
} SubGameScreen;

extern int screen_width;
extern int screen_height;
extern GameScreen currentScreen;
extern SubGameScreen currentSubScreen;
extern int mouseX;
extern int mouseY;
extern Font font;
extern Music music;
extern Sound fxCoin;
extern bool gameShouldClose;
extern bool fxCoinLoaded;

#endif // TYPES_H
