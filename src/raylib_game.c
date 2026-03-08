#include "screens.h"    // NOTE: Declares global (extern) variables and screens functions

#include <stdio.h>
#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

//----------------------------------------------------------------------------------
// Shared Variables Definition (global)
// NOTE: Those variables are shared between modules through screens.h
//----------------------------------------------------------------------------------
GameScreen currentScreen = LOGO;
Font font = { 0 };
Music music = { 0 };
Sound fxCoin = { 0 };
bool gameShouldClose = false;
bool fxCoinLoaded = false;

// Required variables to manage screen transitions (fade-in, fade-out)
static float transAlpha = 0.0f;
static bool onTransition = false;
static bool transFadeOut = false;
static int transFromScreen = -1;
static GameScreen transToScreen = UNKNOWN;

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
static void ChangeToScreen(int screen);     // Change to screen, no transition effect

static void TransitionToScreen(int screen); // Request transition to next screen
static void UpdateTransition(void);         // Update transition effect
static void DrawTransition(void);           // Draw transition effect (full-screen rectangle)

static void UpdateDrawFrame(float dt);          // Update and draw one frame

//----------------------------------------------------------------------------------
// Program main entry point
//----------------------------------------------------------------------------------
int main(void)
{
	//SetTraceLogLevel(LOG_WARNING);
	// Initialization
	//---------------------------------------------------------
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "TAFA with GOD");

    InitAudioDevice();      // Initialize audio device

    // Load global data (assets that must be available in all screens, i.e. font)
    font = LoadFont("resources/mecha.png");
    //music = LoadMusicStream("resources/ambient.ogg"); // TODO: Load music

    // Load sound only if audio device was initialized correctly
    if (IsAudioDeviceReady())
    {
        fxCoin = LoadSound("resources/coin.wav");
        fxCoinLoaded = true;
    }

    // Start music only if audio device is ready and music was loaded
    if (IsAudioDeviceReady())
    {
        if (music.ctxData != 0)
        {
            SetMusicVolume(music, 1.0f);
            PlayMusicStream(music);
        }
    }

	// Setup and init first screen
	currentScreen = LOGO;
	InitLogoScreen();

	#if defined(PLATFORM_WEB)
    		emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
	#else
    	SetTargetFPS(60);       // Set our game to run at 60 frames-per-second
    	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose() && !gameShouldClose)
	{
		float dt = GetFrameTime();
		UpdateDrawFrame(dt);
	}
	#endif

	// De-Initialization
	//--------------------------------------------------------------------------------------
    // De-Initialization trace
    fprintf(stderr, "[EXIT] Starting de-initialization (currentScreen=%d)\n", currentScreen);
    // Unload current screen data before closing
    switch (currentScreen)
    {
        case LOGO: fprintf(stderr, "[EXIT] Unloading LOGO screen\n"); UnloadLogoScreen(); break;
        case TITLE: fprintf(stderr, "[EXIT] Unloading TITLE screen\n"); UnloadTitleScreen(); break;
        case OPTIONS: fprintf(stderr, "[EXIT] Unloading OPTIONS screen\n"); UnloadOptionsScreen(); break;
        case GAMEPLAY: fprintf(stderr, "[EXIT] Unloading GAMEPLAY screen\n"); UnloadGameplayScreen(); break;
        case ENDING: fprintf(stderr, "[EXIT] Unloading ENDING screen\n"); UnloadEndingScreen(); break;
        default: break;
    }
    fprintf(stderr, "[EXIT] Screens unloaded\n");


    // Unload global data loaded
    fprintf(stderr, "[EXIT] Unloading global assets\n");
    UnloadFont(font);
    if (music.ctxData != 0)
    {
        if (IsAudioDeviceReady()) { fprintf(stderr, "[EXIT] Unloading music stream\n"); UnloadMusicStream(music); }
    }
    // Audio shutdown can hang on some backends (PulseAudio/miniaudio) during CloseAudioDevice.
    // To avoid a silent freeze on exit we skip explicit audio device close/unload here.
    if (IsAudioDeviceReady() && fxCoinLoaded)
    {
        fprintf(stderr, "[EXIT] Skipping UnloadSound(fxCoin) to avoid potential hang\n");
    }
    if (IsAudioDeviceReady())
    {
        fprintf(stderr, "[EXIT] Skipping CloseAudioDevice() to avoid potential hang\n");
    }

    fprintf(stderr, "[EXIT] Closing window\n");
    CloseWindow();          // Close window and OpenGL context
    fprintf(stderr, "[EXIT] De-initialization complete\n");
	//--------------------------------------------------------------------------------------

	return 0;
}

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
// Change to next screen, no transition
static void ChangeToScreen(int screen)
{
    // Unload current screen
    switch (currentScreen)
    {
        case LOGO: UnloadLogoScreen(); break;
        case TITLE: UnloadTitleScreen(); break;
        case OPTIONS: UnloadOptionsScreen(); break;
        case GAMEPLAY: UnloadGameplayScreen(); break;
        case ENDING: UnloadEndingScreen(); break;
        default: break;
    }

    // Init next screen
    switch (screen)
    {
        case LOGO: InitLogoScreen(); break;
        case TITLE: InitTitleScreen(); break;
        case OPTIONS: InitOptionsScreen(); break;
        case GAMEPLAY: InitGameplayScreen(); break;
        case ENDING: InitEndingScreen(); break;
        default: break;
    }

    currentScreen = screen;
}

// Request transition to next screen
static void TransitionToScreen(int screen)
{
    onTransition = true;
    transFadeOut = false;
    transFromScreen = currentScreen;
    transToScreen = screen;
    transAlpha = 0.0f;
}

// Update transition effect (fade-in, fade-out)
static void UpdateTransition(void)
{
    if (!transFadeOut)
    {
        transAlpha += 0.05f;

        // NOTE: Due to float internal representation, condition jumps on 1.0f instead of 1.05f
        // For that reason we compare against 1.01f, to avoid last frame loading stop
        if (transAlpha > 1.01f)
        {
            transAlpha = 1.0f;

            // Unload current screen
            switch (transFromScreen)
            {
                case LOGO: UnloadLogoScreen(); break;
                case TITLE: UnloadTitleScreen(); break;
                case OPTIONS: UnloadOptionsScreen(); break;
                case GAMEPLAY: UnloadGameplayScreen(); break;
                case ENDING: UnloadEndingScreen(); break;
                default: break;
            }

            // Load next screen
            switch (transToScreen)
            {
                case LOGO: InitLogoScreen(); break;
                case TITLE: InitTitleScreen(); break;
                case OPTIONS: InitOptionsScreen(); break;
                case GAMEPLAY: InitGameplayScreen(); break;
                case ENDING: InitEndingScreen(); break;
                default: break;
            }

            currentScreen = transToScreen;

            // Activate fade out effect to next loaded screen
            transFadeOut = true;
        }
    }
    else  // Transition fade out logic
    {
        transAlpha -= 0.02f;

        if (transAlpha < -0.01f)
        {
            transAlpha = 0.0f;
            transFadeOut = false;
            onTransition = false;
            transFromScreen = -1;
            transToScreen = UNKNOWN;
        }
    }
}

// Draw transition effect (full-screen rectangle)
static void DrawTransition(void)
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, transAlpha));
}

// Update and draw game frame
static void UpdateDrawFrame(float dt)
{
    // Update
    //----------------------------------------------------------------------------------
    //UpdateMusicStream(music);       // NOTE: Music keeps playing between screens

    if (!onTransition)
    {
        switch(currentScreen)
        {
            case LOGO:
            {
                UpdateLogoScreen();

                if (FinishLogoScreen()) TransitionToScreen(TITLE);

            } break;
            case TITLE:
            {
                UpdateTitleScreen();

                if (FinishTitleScreen() == 1) TransitionToScreen(OPTIONS);
                else if (FinishTitleScreen() == 2) TransitionToScreen(GAMEPLAY);

            } break;
            case OPTIONS:
            {
                UpdateOptionsScreen();

                if (FinishOptionsScreen()) TransitionToScreen(TITLE);

            } break;
            case GAMEPLAY:
            {
                UpdateGameplayScreen(dt);

                if (FinishGameplayScreen() == 1) TransitionToScreen(ENDING);
                //else if (FinishGameplayScreen() == 2) TransitionToScreen(TITLE);

            } break;
            case ENDING:
            {
                UpdateEndingScreen();

                if (FinishEndingScreen() == 1) TransitionToScreen(TITLE);

            } break;
            default: break;
        }
    }
    else UpdateTransition();    // Update transition (fade-in, fade-out)
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

        ClearBackground(RAYWHITE);

        switch(currentScreen)
        {
            case LOGO: DrawLogoScreen(); break;
            case TITLE: DrawTitleScreen(); break;
            case OPTIONS: DrawOptionsScreen(); break;
            case GAMEPLAY: DrawGameplayScreen(); break;
            case ENDING: DrawEndingScreen(); break;
            default: break;
        }

        // Draw full screen rectangle in front of everything
        if (onTransition) DrawTransition();

        //DrawFPS(10, 10);

    EndDrawing();
    //----------------------------------------------------------------------------------
}
