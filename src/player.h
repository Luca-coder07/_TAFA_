#ifndef PLAYER_H
#define PLAYER_H

#include "screens.h"

typedef enum {IDLE, WALK, JUMP} PlayerState;

typedef struct s_player {
	float		pos_x;
	float		pos_y;
	float		speed_x;
	float		vy;
	float		jump_force;
	int			dir; // -1: left; 1: right; 
	int			current_frame;
	float		timer;
	float		frame_time;
	PlayerState	state;
	Texture2D	idle_image[8];
	Texture2D	walk_image[8];
	Texture2D	jump_image[5];
}	t_player;

void	InitPlayer(t_player *player);
void	UpdatePlayer(t_player *player, float dt);
void	DrawPlayer(t_player player);
void	UnloadPlayer(t_player *player);

#endif
