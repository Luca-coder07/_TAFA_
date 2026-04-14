#ifndef SCREENS_H
#define SCREENS_H

#include "raylib.h"
#include "types.h"
#include "struct.h"
#include <stddef.h>
#include "player.h"
#include <math.h>
#include "raylib_utils.h"

#ifdef __cplusplus
extern "C"
{ // Prevents name mangling of functions
#endif

	//----------------------------------------------------------------------------------
	// Logo Screen Functions Declaration
	//----------------------------------------------------------------------------------
	void InitLogoScreen(void);
	void UpdateLogoScreen(void);
	void DrawLogoScreen(void);
	void UnloadLogoScreen(void);
	int FinishLogoScreen(void);

	//----------------------------------------------------------------------------------
	// Title Screen Functions Declaration
	//----------------------------------------------------------------------------------
	void InitTitleScreen(t_title *title);
	void UpdateTitleScreen(t_title *title);
	void DrawTitleScreen(t_title title);
	void UnloadTitleScreen(void);
	int FinishTitleScreen(void);

	//----------------------------------------------------------------------------------
	// Options Screen Functions Declaration
	//----------------------------------------------------------------------------------
	void InitOptionsScreen(void);
	void UpdateOptionsScreen(void);
	void DrawOptionsScreen(void);
	void UnloadOptionsScreen(void);
	int FinishOptionsScreen(void);

	//----------------------------------------------------------------------------------
	// Gameplay Screen Functions Declaration
	//----------------------------------------------------------------------------------
	void InitGameplayScreen(void);
	void UpdateGameplayScreen(float dt);
	void DrawGameplayScreen(void);
	void UnloadGameplayScreen(void);
	int FinishGameplayScreen(void);

	//----------------------------------------------------------------------------------
	// Ending Screen Functions Declaration
	//----------------------------------------------------------------------------------
	void InitEndingScreen(void);
	void UpdateEndingScreen(void);
	void DrawEndingScreen(void);
	void UnloadEndingScreen(void);
	int FinishEndingScreen(void);

#ifdef __cplusplus
}
#endif

#endif // SCREENS_H
