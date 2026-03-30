#include "level.h"

float timer = 0.0f;
float hide_text = false;

char *prologue_text[4] = {
    "Dans un monde plongé dans les ténèbres,",
    "où la peur et le désespoir règnent en maîtres,",
    "où chacun est prisonnier de ses choix et désirs...",
    "jusqu'à ce que..."};

void LoadLevel(t_level *level, SubGameScreen levelType)
{
    level->type = levelType;
    level->name = "Level 1";
}

void UpdateLevel(t_level *level, float dt)
{
    if (level->type == LEVEL_1 && timer <= 10.0f)
    {
        timer += dt * 1.0f;
        hide_text = false;
    }
    else
    {
        hide_text = true;
    }
}

void DrawLevel(t_level *level)
{
    DrawRectangle(0, screen_height * 0.9, screen_width, screen_height, GRAY);
    DrawLineEx((Vector2){0, screen_height * 0.9}, (Vector2){screen_width, screen_height * 0.9}, 4, BLACK);
    switch (level->type)
    {
    case LEVEL_1:
        if (!hide_text)
        {
            for (int i = 0; i < 4; i++)
            {
                DrawText(prologue_text[i], screen_width / 2 - MeasureText(prologue_text[i], 40) / 2, screen_height / 3 + (i * 40), 40, BLACK);
            }
        }
        // TO DO: Draw Black Box and check if player is in collision with this.
        Rectangle blackBox = {screen_width * 0.8, screen_height * 0.85, screen_width * 0.05, screen_width * 0.05};
        DrawRectangleRec(blackBox, (Color){10, 10, 10, 255});
        break;
    }
}

void UnloadLevel(t_level *level)
{
    (void)level;
}
