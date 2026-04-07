#ifndef STRUCT_H
#define STRUCT_H

#include "tafa.h"

typedef struct s_one
{
	char *prologue_text[4];
	char *quiz_text[6];
	char *quiz_answer[4];
	Rectangle black_box;
	bool show_quiz;
	bool hide_text;
	float timer;
} t_one;

typedef struct s_title
{
	float menu_font_size;
	Vector2 text_size[3];
	Vector2 text_pos[3];
	Rectangle highlight_rec[3];
	int hover_state;
} t_title;

typedef struct s_player
{
	Rectangle pos;
	bool can_move;
	float speed_x;
	float vy;
	float jump_force;
	bool is_jumping;
	float jump_timer;
	float jump_cooldown;
	int dir; // -1: left; 1: right;
	int current_frame;
	float timer;
	float frame_time;
	PlayerState state;
	Texture2D idle_image[8];
	Texture2D walk_image[8];
	Texture2D run_image[8];
	Texture2D jump_image[5];
} t_player;

typedef struct s_level
{
	SubGameScreen type;
	const char *name;
	t_one one;
} t_level;

#endif