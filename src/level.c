#include "level.h"

void LoadLevel(t_level *level, SubGameScreen levelType)
{
    level->type = levelType;
    level->name = "Level 1";

    if (level->type == LEVEL_1)
    {
        level->one.prologue_text[0] = "Ao anaty tontolo feno aizina,";                            //"Dans un monde plongé dans les ténèbres,",
        level->one.prologue_text[1] = "izay hanjakan'ny tahotra sy fahadisoam-panantenana,";      //"où la peur et le désespoir règnent en maîtres,",
        level->one.prologue_text[2] = "izay ny tsirairay dia gejain'ny safidiny sy ny filàny..."; //"où chacun est prisonnier de ses choix et désirs...",
        level->one.prologue_text[3] = "raha tsy...";

        level->one.quiz_text[0] = "Quiz 1:";
        level->one.quiz_text[1] = "Lehilahy iray mijery sary.";
        level->one.quiz_text[2] = "Nisy olona nanontany azy: \"Iza io?\"";
        level->one.quiz_text[3] = "Namaly izy: \"Tsy manana anabavy sy rahalahy aho,";
        level->one.quiz_text[4] = "fa ny dadan'io olona io dia zanaky ny dadako.\"";
        level->one.quiz_text[5] = "Iza ilay amin'ny sary?";

        level->one.quiz_answer[0] = "Izy tenany ihany.";
        level->one.quiz_answer[1] = "Zanany ihany.";
        level->one.quiz_answer[2] = "Rafilahiny.";
        level->one.quiz_answer[3] = "Dadatoany.";

        level->one.black_box = (Rectangle){screen_width * 0.8, screen_height * 0.85, screen_width * 0.05, screen_width * 0.05};
        level->one.show_quiz = false;
        level->one.hide_text = false;
        level->one.timer = 0.0f;
    }
}

void UpdateLevel(t_level *level, float dt, t_player *player)
{
    UpdatePlayer(player, dt);
    if (level->type == LEVEL_1)
    {
        if (level->one.timer <= 5.0f)
        {
            level->one.timer += dt * 1.0f;
            level->one.hide_text = false;
            player->can_move = false;
        }
        else
        {
            level->one.hide_text = true;
            player->can_move = true;
        }
        Rectangle hitbox = {
            player->pos.x - player->pos.width / 4,
            player->pos.y - player->pos.height / 4,
            player->pos.width / 2,
            player->pos.height / 2};
        if (CheckCollisionRecs(hitbox, level->one.black_box))
        {
            level->one.show_quiz = true;
        }
        else
            level->one.show_quiz = false;
    }
}

void DrawLevel(t_level level, t_player player)
{
    Vector2 answerPos[4];
    DrawRectangle(0, screen_height * 0.9, screen_width, screen_height, GRAY);
    DrawLineEx((Vector2){0, screen_height * 0.9}, (Vector2){screen_width, screen_height * 0.9}, 4, BLACK);
    switch (level.type)
    {
    case LEVEL_1:
        if (!level.one.hide_text)
        {
            for (int i = 0; i < 4; i++)
            {
                int textWidth = MeasureText(level.one.prologue_text[i], 40);
                DrawText(level.one.prologue_text[i], screen_width / 2 - textWidth / 2, screen_height / 3 + (i * 40), 40, BLACK);
            }
        }
        DrawRectangleRec(level.one.black_box, (Color){10, 10, 10, 255});
        if (level.one.show_quiz)
        {
            int quizWidth = 550;
            int quizHeight = 300;
            Rectangle quizRect = {screen_width / 2 - quizWidth / 2, screen_height / 2 - quizHeight / 2, quizWidth, quizHeight};
            DrawRectangleRec(quizRect, Fade((Color){30, 30, 30, 230}, 0.9f)); // semi-transparent dark rectangle

            // Draw the quiz inside the rectangle
            for (int i = 0; i < 6; i++)
                DrawText(level.one.quiz_text[i], quizRect.x + 10, quizRect.y + 10 + i * 40, 20, RAYWHITE);

            // Positions pour les réponses
            int padding = 10;
            int lineHeight = 30;

            // 1er texte : à gauche, milieu haut (au quart hauteur)
            int x1 = quizRect.x - MeasureText(level.one.quiz_answer[0], 20) - padding;
            int y1 = quizRect.y + quizRect.height / 4 - lineHeight / 2;
            answerPos[0] = (Vector2){x1 + MeasureText(level.one.quiz_answer[0], 20) * 0.5f, y1 + 10.0f};
            DrawText(level.one.quiz_answer[0], x1, y1, 20, BLACK);

            // 2e texte : en bas à gauche
            int x2 = quizRect.x + padding;
            int y2 = quizRect.y + quizRect.height + lineHeight - padding;
            answerPos[1] = (Vector2){x2 + MeasureText(level.one.quiz_answer[1], 20) * 0.5f, y2 + 10.0f};
            DrawText(level.one.quiz_answer[1], x2, y2, 20, BLACK);

            // 3e texte : en bas à droite
            int textWidth3 = MeasureText(level.one.quiz_answer[2], 20);
            int x3 = quizRect.x + quizRect.width - textWidth3 - padding;
            int y3 = y2; // même hauteur que 2e texte
            answerPos[2] = (Vector2){x3 + MeasureText(level.one.quiz_answer[2], 20) * 0.5f, y3 + 10.0f};
            DrawText(level.one.quiz_answer[2], x3, y3, 20, BLACK);

            // 4e texte : à droite, milieu haut (quart hauteur)
            int x4 = quizRect.x + quizRect.width + padding;
            int y4 = y1;
            answerPos[3] = (Vector2){x4 + MeasureText(level.one.quiz_answer[3], 20) * 0.5f, y4 + 10.0f};
            DrawText(level.one.quiz_answer[3], x4, y4, 20, BLACK);

            // Definire la taille du bouton
            int buttonWidth = (quizWidth - 50) / 4;
            int buttonHeight = 40;
            int buttonY = quizRect.y + quizHeight - buttonHeight - 20;

            const char *choices[] = {"A", "B", "C", "D"};
            for (int i = 0; i < 4; i++)
            {
                Rectangle btn = {
                    quizRect.x + 10 + i * (buttonWidth + 10),
                    buttonY,
                    buttonWidth,
                    buttonHeight};

                bool hovered = CheckCollisionPointRec((Vector2){mouseX, mouseY}, btn);

                DrawRectangleRec(btn, hovered ? SKYBLUE : DARKGRAY);
                DrawRectangleLinesEx(btn, 2, RAYWHITE);

                int letterWidth = MeasureText(choices[i], 30);
                DrawText(choices[i],
                         btn.x + btn.width / 2 - letterWidth / 2,
                         btn.y + btn.height / 2 - 15,
                         30,
                         RAYWHITE);

                // Taille approximative du texte des réponses (même font que DrawText(..., 20,...))
                float fontSizeAns = 20.0f;
                float textW = MeasureText(level.one.quiz_answer[i], (int)fontSizeAns);

                // Milieu horizontal du texte (on suppose qu’on a dessiné depuis x* / y* en top-left)
                Vector2 end = (Vector2){
                    answerPos[i].x,                  // ton x est déjà vers le milieu horizontal via MeasureText*0.5f
                    answerPos[i].y + fontSizeAns / 2 // corrige l’ancrage: DrawText ancre en haut-gauche
                };

                // Départ : on utilise un “bord” du bouton plutôt que le centre
                Vector2 start = (Vector2){btn.x + btn.width / 2, btn.y + btn.height / 2};

                switch (i)
                {
                case 0: // A: vers le haut
                    start.x = btn.x;
                    break;
                case 1: // B: vers le bas
                    start.y = btn.y + btn.height;
                    break;
                case 2: // C: vers la droite
                    start.y = btn.y + btn.height;
                    break;
                case 3: // D: vers le haut (proche de ta zone milieu haut)
                    start.x = btn.x + btn.width;
                    break;
                }

                // Contrôle Bezier: courbure automatique selon la direction
                Vector2 control = (Vector2){
                    (start.x + end.x) * 0.5f,
                    (start.y + end.y) * 0.5f};

                // “Push” pour éviter les courbes trop plates
                float push = 80.0f;
                if (i == 0 || i == 3)
                    control.y -= push; // A/D courbés vers le haut
                else
                    control.y += push; // B/C courbés vers le bas

                // dessine
                DrawArrowBezierQuad(start, control, end, 5.0f, BLACK);
            }
        }
        break;
    case LEVEL_2:
        DrawText("LEVEL 2", 0, 0, 10, BLACK);
        break;
    case LEVEL_3:
        DrawText("LEVEL 3", 0, 0, 10, BLACK);
        break;
    }
    DrawPlayer(player);
}

void UnloadLevel(t_level *level)
{
    (void)level;
}
