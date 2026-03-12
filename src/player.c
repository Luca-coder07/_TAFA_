#include "player.h"

static float gravity = 100.0f;
static float ground_level = SCREEN_HEIGHT * 0.85f;

void	InitPlayer(t_player *player)
{
	gravity = 100.0f;
	ground_level = SCREEN_HEIGHT * 0.85f;

	player->pos_x = SCREEN_WIDTH * 0.1;
	player->pos_y = ground_level;
	player->speed_x = 100.0f;
	player->vy = 0.0f;
	player->jump_force = 500.0f;
	player->dir = 0;

	player->current_frame = 0;
	player->timer = 0;
	player->frame_time = 0.1f;

	player->state = IDLE;

	// IDLE Texture
	player->idle_image[0] = LoadTextureFromFile("resources/IDLE/idle_01.png");
	player->idle_image[1] = LoadTextureFromFile("resources/IDLE/idle_02.png");
	player->idle_image[2] = LoadTextureFromFile("resources/IDLE/idle_03.png");
	player->idle_image[3] = LoadTextureFromFile("resources/IDLE/idle_04.png");
	player->idle_image[4] = LoadTextureFromFile("resources/IDLE/idle_05.png");
	player->idle_image[5] = LoadTextureFromFile("resources/IDLE/idle_06.png");
	player->idle_image[6] = LoadTextureFromFile("resources/IDLE/idle_07.png");
	player->idle_image[7] = LoadTextureFromFile("resources/IDLE/idle_08.png");


	// WALK Texture
	player->walk_image[0] = LoadTextureFromFile("resources/WALK/walk_01.png");
	player->walk_image[1] = LoadTextureFromFile("resources/WALK/walk_02.png");
	player->walk_image[2] = LoadTextureFromFile("resources/WALK/walk_03.png");
	player->walk_image[3] = LoadTextureFromFile("resources/WALK/walk_04.png");
	player->walk_image[4] = LoadTextureFromFile("resources/WALK/walk_05.png");
	player->walk_image[5] = LoadTextureFromFile("resources/WALK/walk_06.png");
	player->walk_image[6] = LoadTextureFromFile("resources/WALK/walk_07.png");
	player->walk_image[7] = LoadTextureFromFile("resources/WALK/walk_08.png");

	// JUMP Texture
	player->jump_image[0] = LoadTextureFromFile("resources/JUMP/jump_01.png");
	player->jump_image[1] = LoadTextureFromFile("resources/JUMP/jump_02.png");
	player->jump_image[2] = LoadTextureFromFile("resources/JUMP/jump_03.png");
	player->jump_image[3] = LoadTextureFromFile("resources/JUMP/jump_04.png");
	player->jump_image[4] = LoadTextureFromFile("resources/JUMP/jump_05.png");

}

void	UpdatePlayer(t_player *player, float dt)
{
	player->timer += dt;
    if (player->pos_y < SCREEN_HEIGHT * 0.85f || player->vy < 0)
    {
        player->vy += gravity * dt;
        player->pos_y += player->vy * dt;
    }
    else
    {
        // Le joueur est au sol
        player->pos_y = SCREEN_HEIGHT * 0.85f;
        player->vy = 0;
        if (player->state == JUMP)
            player->state = IDLE;
    }

	if (player->timer >= player->frame_time)
	{
		if (player->state != JUMP)
			player->current_frame = (player->current_frame + 1) % 8;
		else
			player->current_frame = (player->current_frame + 1) % 5;
		player->timer = 0.0f;
	}

	if (IsKeyDown(KEY_LEFT))
	{
		player->pos_x -= player->speed_x * dt;
		if (player->state != JUMP)
			player->state = WALK;
		player->dir = -1;
	}
	else if (IsKeyDown(KEY_RIGHT))
	{
		player->pos_x += player->speed_x * dt;
		if (player->state != JUMP)
			player->state = WALK;
		player->dir = 1;
	}
	else if (player->state != JUMP)
		player->state = IDLE;
	
	if (IsKeyPressed(KEY_SPACE) && player->pos_y >= SCREEN_HEIGHT * 0.85f)
	{
		player->vy = -player->jump_force;
		player->state = JUMP;
	}
}

void	DrawPlayer(t_player player)
{
	Vector2		origin;
	Rectangle	source_rec;
	Rectangle	dest_rec;

	if (player.state == IDLE)
	{
		source_rec = (Rectangle) {0, 0,
			(float)player.idle_image[player.current_frame].width,
			(float)player.idle_image[player.current_frame].height};
		
		dest_rec = (Rectangle){player.pos_x, player.pos_y,
			(float)player.idle_image[player.current_frame].width / 2.0f,
			(float)player.idle_image[player.current_frame].height / 2.0f};
		
		origin = (Vector2){
			player.idle_image[player.current_frame].width / 4.0f,
			player.idle_image[player.current_frame].height / 4.0f
		};

		if (player.dir == -1)
		{
			source_rec.width = -source_rec.width;
		}

		DrawTexturePro(player.idle_image[player.current_frame], source_rec, dest_rec, origin, 0.0f, WHITE);
	}

	if (player.state == WALK)
	{
		source_rec = (Rectangle) {0, 0,
			(float)player.walk_image[player.current_frame].width,
			(float)player.walk_image[player.current_frame].height};
		
		dest_rec = (Rectangle){player.pos_x, player.pos_y,
			(float)player.walk_image[player.current_frame].width / 2.0f,
			(float)player.walk_image[player.current_frame].height / 2.0f};
		
		origin = (Vector2){
			player.walk_image[player.current_frame].width / 4.0f,
			player.walk_image[player.current_frame].height / 4.0f
		};
		
		if (player.dir == -1)
		{
			source_rec.width = -source_rec.width;
		}

		DrawTexturePro(player.walk_image[player.current_frame], source_rec, dest_rec, origin, 0.0f, WHITE);
	}
	
	if (player.state == JUMP)
	{
		source_rec = (Rectangle) {0, 0,
			(float)player.jump_image[player.current_frame].width,
			(float)player.jump_image[player.current_frame].height};
		
		dest_rec = (Rectangle){player.pos_x, player.pos_y,
			(float)player.jump_image[player.current_frame].width / 2.0f,
			(float)player.jump_image[player.current_frame].height / 2.0f};
		
		origin = (Vector2){
			player.jump_image[player.current_frame].width / 4.0f,
			player.jump_image[player.current_frame].height / 4.0f
		};
		
		if (player.dir == -1)
		{
			source_rec.width = -source_rec.width;
		}

		DrawTexturePro(player.jump_image[player.current_frame], source_rec, dest_rec, origin, 0.0f, WHITE);
	}
}

void UnloadPlayer(t_player *player)
{
	for (int i = 0; i < 8; i++)
	{
		if (i < 5)
			UnloadTexture(player->jump_image[i]);
		UnloadTexture(player->idle_image[i]);
		UnloadTexture(player->walk_image[i]);
	}
}
