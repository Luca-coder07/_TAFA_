#include "player.h"

const float anim_speeds[] = {[IDLE] = 0.1f, [WALK] = 0.1f, [JUMP] = 0.2f, [RUN] = 0.1f};
const int frames_count[] = {[IDLE] = 8, [WALK] = 8, [JUMP] = 5, [RUN] = 8};

static float gravity = 900.0f;
static float ground_level = 0;

void InitPlayer(t_player *player)
{
	for (int i = 0; i < 8; i++)
	{
		player->idle_image[i] = (Texture2D){0};
		player->walk_image[i] = (Texture2D){0};
		if (i < 5)
			player->jump_image[i] = (Texture2D){0};
	}

	// IDLE Texture
	const char *idle_paths[8] = {
		"resources/IDLE/idle_01.png",
		"resources/IDLE/idle_02.png",
		"resources/IDLE/idle_03.png",
		"resources/IDLE/idle_04.png",
		"resources/IDLE/idle_05.png",
		"resources/IDLE/idle_06.png",
		"resources/IDLE/idle_07.png",
		"resources/IDLE/idle_08.png"};

	// WALK Texture
	const char *walk_paths[8] = {
		"resources/WALK/walk_01.png",
		"resources/WALK/walk_02.png",
		"resources/WALK/walk_03.png",
		"resources/WALK/walk_04.png",
		"resources/WALK/walk_05.png",
		"resources/WALK/walk_06.png",
		"resources/WALK/walk_07.png",
		"resources/WALK/walk_08.png"};

	// RUN Texture
	const char *run_paths[8] = {
		"resources/RUN/run_01.png",
		"resources/RUN/run_02.png",
		"resources/RUN/run_03.png",
		"resources/RUN/run_04.png",
		"resources/RUN/run_05.png",
		"resources/RUN/run_06.png",
		"resources/RUN/run_07.png",
		"resources/RUN/run_08.png"};

	// JUMP Texture
	const char *jump_paths[5] = {
		"resources/JUMP/jump_01.png",
		"resources/JUMP/jump_02.png",
		"resources/JUMP/jump_03.png",
		"resources/JUMP/jump_04.png",
		"resources/JUMP/jump_05.png"};

	for (int i = 0; i < 8; i++)
	{
		player->idle_image[i] = LoadTextureFromFile(idle_paths[i]);
		player->walk_image[i] = LoadTextureFromFile(walk_paths[i]);
		player->run_image[i] = LoadTextureFromFile(run_paths[i]);
		if (i < 5)
			player->jump_image[i] = LoadTextureFromFile(jump_paths[i]);
	}

	gravity = 900.0f;
	ground_level = screen_height * 0.85f;

	player->pos = (Rectangle){screen_width * 0.1, ground_level, player->idle_image[0].width / 2, player->idle_image[0].height / 2};
	player->speed_x = 100.0f;
	player->vy = 0.0f;

	player->jump_force = 400.0f;
	player->is_jumping = false;
	player->jump_timer = 0.0f;
	player->jump_cooldown = 0.2f;

	player->dir = 0;

	player->current_frame = 0;
	player->timer = 0;
	player->frame_time = 0;

	player->state = IDLE;
}

void UpdatePlayer(t_player *player, float dt)
{
	player->timer += dt;
	player->frame_time = anim_speeds[player->state];
	if (player->pos.y >= ground_level)
	{
		// Le joueur est au sol
		player->pos.y = ground_level;
		player->vy = 0;
		player->state = IDLE;
		player->is_jumping = false;
	}
	else
		player->state = JUMP;

	if (player->timer >= player->frame_time)
	{
		player->current_frame = (player->current_frame + 1) % frames_count[player->state];
		player->timer = 0.0f;
	}

	if (IsKeyDown(KEY_LEFT) && player->can_move)
	{
		if (IsKeyDown(KEY_LEFT_SHIFT))
		{
			player->pos.x -= (player->speed_x * 3) * dt;
			if (player->state != JUMP)
				player->state = RUN;
		}
		else
		{
			player->pos.x -= player->speed_x * dt;
			if (player->state != JUMP)
				player->state = WALK;
		}
		player->dir = -1;
	}
	else if (IsKeyDown(KEY_RIGHT) && player->can_move)
	{
		if (IsKeyDown(KEY_LEFT_SHIFT))
		{
			player->pos.x += (player->speed_x * 3) * dt;
			if (player->state != JUMP)
				player->state = RUN;
		}
		else
		{
			player->pos.x += player->speed_x * dt;
			if (player->state != JUMP)
				player->state = WALK;
		}
		player->dir = 1;
	}
	else
	{
		if (player->state != JUMP)
			player->state = IDLE;
	}
	if (player->pos.x < 50)
		player->pos.x = 50;
	if (player->pos.x >= screen_width - 50)
		player->pos.x = screen_width - 50;

	if (IsKeyPressed(KEY_SPACE) && !player->is_jumping && player->jump_timer <= 0.0f)
	{
		player->current_frame = 0;
		player->vy = -player->jump_force;
		player->is_jumping = true;
		player->jump_timer = player->jump_cooldown;
	}

	if (player->jump_timer > 0.0f)
		player->jump_timer -= dt;

	player->vy += gravity * dt;
	player->pos.y += player->vy * dt;
}

void DrawPlayer(t_player player)
{
	Texture2D *current_anim = NULL;
	switch (player.state)
	{
	case IDLE:
		current_anim = player.idle_image;
		break;
	case WALK:
		current_anim = player.walk_image;
		break;
	case JUMP:
		current_anim = player.jump_image;
		break;
	case RUN:
		current_anim = player.run_image;
		break;
	}
	// origine et source_rec peuvent être precalculés dans InitPlayer et stockés dans player si nécessaire
	Vector2 origin = (Vector2){current_anim[player.current_frame].width / 4.0f, current_anim[player.current_frame].height / 4.0f};
	Rectangle source_rec = (Rectangle){0, 0, (float)current_anim[player.current_frame].width, (float)current_anim[player.current_frame].height};
	if (player.dir == -1)
		source_rec.width = -source_rec.width;

	DrawTexturePro(current_anim[player.current_frame], source_rec, player.pos, origin, 0.0f, WHITE);
}

void UnloadPlayer(t_player *player)
{
	for (int i = 0; i < 8; i++)
	{
		if (player->idle_image[i].id != 0)
			UnloadTexture(player->idle_image[i]);
		if (player->walk_image[i].id != 0)
			UnloadTexture(player->walk_image[i]);
		if (player->run_image[i].id != 0)
			UnloadTexture(player->run_image[i]);
		if (i < 5 && player->jump_image[i].id != 0)
			UnloadTexture(player->jump_image[i]);
	}
}
