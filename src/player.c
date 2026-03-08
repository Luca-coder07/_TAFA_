#include "player.h"

void	InitPlayer(t_player *player)
{
	player->pos_x = SCREEN_WIDTH * 0.1;
	player->pos_y = SCREEN_HEIGHT * 0.85;
	player->speed = 100.0f;
	player->dir = 0;

	player->current_frame = 0;
	player->timer = 0;
	player->frame_time = 0.1f;

	player->state = IDLE;

	// IDLE Texture
	player->idle_image[0] = LoadTextureFromFile("resources/IDLE/fighter_Idle_0001.png");
	player->idle_image[1] = LoadTextureFromFile("resources/IDLE/fighter_Idle_0002.png");
	player->idle_image[2] = LoadTextureFromFile("resources/IDLE/fighter_Idle_0003.png");
	player->idle_image[3] = LoadTextureFromFile("resources/IDLE/fighter_Idle_0004.png");
	player->idle_image[4] = LoadTextureFromFile("resources/IDLE/fighter_Idle_0005.png");
	player->idle_image[5] = LoadTextureFromFile("resources/IDLE/fighter_Idle_0006.png");
	player->idle_image[6] = LoadTextureFromFile("resources/IDLE/fighter_Idle_0007.png");
	player->idle_image[7] = LoadTextureFromFile("resources/IDLE/fighter_Idle_0008.png");


	// WALK Texture
	player->walk_image[0] = LoadTextureFromFile("resources/WALK/fighter_walk_0001.png");
	player->walk_image[1] = LoadTextureFromFile("resources/WALK/fighter_walk_0002.png");
	player->walk_image[2] = LoadTextureFromFile("resources/WALK/fighter_walk_0003.png");
	player->walk_image[3] = LoadTextureFromFile("resources/WALK/fighter_walk_0004.png");
	player->walk_image[4] = LoadTextureFromFile("resources/WALK/fighter_walk_0005.png");
	player->walk_image[5] = LoadTextureFromFile("resources/WALK/fighter_walk_0006.png");
	player->walk_image[6] = LoadTextureFromFile("resources/WALK/fighter_walk_0007.png");
	player->walk_image[7] = LoadTextureFromFile("resources/WALK/fighter_walk_0008.png");
}

void	UpdatePlayer(t_player *player, float dt)
{
	player->timer += dt;
	if (player->timer >= player->frame_time)
	{
		player->current_frame = (player->current_frame + 1) % 8;
		player->timer = 0.0f;
	}
	if (IsKeyDown(KEY_LEFT))
	{
		if (player->dir == 1) {
			FlipTextureVertical(&(player->idle_image[player->current_frame]));
			FlipTextureVertical(&(player->walk_image[player->current_frame]));
		}
		player->pos_x -= player->speed * dt;
		player->state = WALK;
		player->dir = -1;
	}
	else if (IsKeyDown(KEY_RIGHT))
	{
		if (player->dir == -1) {
			FlipTextureVertical(&(player->idle_image[player->current_frame]));
			FlipTextureVertical(&(player->walk_image[player->current_frame]));
		}
		player->pos_x += player->speed * dt;
		player->state = WALK;
		player->dir = 1;
	}
	else
		player->state = IDLE;
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
	
		DrawTexturePro(player.walk_image[player.current_frame], source_rec, dest_rec, origin, 0.0f, WHITE);
	}
}

void UnloadPlayer(t_player *player)
{
	for (int i = 0; i < 8; i++)
	{
		UnloadTexture(player->idle_image[i]);
		UnloadTexture(player->walk_image[i]);
	}
}
