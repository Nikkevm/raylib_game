#include <stdio.h>
#include "raylib.h"
#include "resources.h"
#include "raymath.h"
#include "map.h"
#include "entity.h"
#include "enemy.h"

#ifdef DEV
#include "dev.h"
#endif

/* Note: Tiles could be separated into 2 different arrays one for non-interactable
 and one for interatable tiles*/

const int w_width = 1280;
const int w_height = 720;

World map = {0};

#define PLAYER_SPEED 200
int player;

void update()
{
	if(IsKeyReleased(KEY_F5)) {
		dev_mode = !dev_mode;
	}

	{
		Entity *o_player = &ent[player];
		int updown = 0, leftright = 0;
		if(IsKeyDown(KEY_A)) {leftright -= 1;}
		if(IsKeyDown(KEY_D)) {leftright += 1;}
		if(IsKeyDown(KEY_W)) {updown -= 1;}
		if(IsKeyDown(KEY_S)) {updown += 1;}
		o_player->velocity.x = leftright * PLAYER_SPEED;
		o_player->velocity.y = updown * PLAYER_SPEED;
	}
}

void draw(Camera2D camera)
{

	// Note: Maybe move these around a bit?
	Vector2 mouse_pos = GetMousePosition();
	Vector2 mouse_pos_world = GetScreenToWorld2D(mouse_pos, camera);
	Vector2 tile_pos = (Vector2){(int)mouse_pos_world.x - (int)mouse_pos_world.x % 32, (int)mouse_pos_world.y - (int)mouse_pos_world.y % 32};
	int tile_num = ((int)mouse_pos_world.x - (int)mouse_pos_world.x % 32)/32 + ((int)mouse_pos_world.y - (int)mouse_pos_world.y % 32)/32*64;

	BeginDrawing();

	ClearBackground(RAYWHITE);

	BeginMode2D(camera);

	render_map(&map);
	draw_vegetation(&map);

	if(!(mouse_pos_world.x < 0 || mouse_pos_world.y < 0)){
		DrawRectangleLinesEx((Rectangle){tile_pos.x, tile_pos.y, 32, 32}, 2.0f, BLACK);
	}

	//-------------draw player
	Entity *o_player = &ent[player];
	Rectangle source_rec = {0.0f, 0.0f, (float)player_texture.width, -(float)player_texture.height}; //Note: no need to do this everytime
	Rectangle dest_rec = {o_player->pos.x, o_player->pos.y, player_texture.width, player_texture.height};

	Vector2 origin = {player_texture.width / 2, player_texture.height / 2};

	float rotation = -Vector2LineAngle(o_player->pos, GetScreenToWorld2D(GetMousePosition(), camera)) * RAD2DEG;

	DrawTexturePro(player_texture, source_rec, dest_rec, origin, rotation, WHITE);
	//-----------end draw player
	draw_enemy();

	EndMode2D();

	DrawText(TextFormat("FPS: %d", GetFPS()), 0, 50, 24, GREEN);

#ifdef DEV
	if(dev_mode) {
		draw_dev_tools();
		DrawText(TextFormat("Cursor: %d, %d", (int)mouse_pos.x, (int)mouse_pos.y), 0, 75, 24, BLACK);
		DrawText(TextFormat("Cursor World Space: %d, %d", (int)mouse_pos_world.x, (int)mouse_pos_world.y), 0, 100, 24, BLACK);
		DrawText(TextFormat("Tile Coordinate: %d, %d", (int)mouse_pos_world.x - (int)mouse_pos_world.x % 32, (int)mouse_pos_world.y - (int)mouse_pos_world.y % 32), 0, 125, 24, BLACK);
		DrawText(TextFormat("Tile: %d, %d", ((int)mouse_pos_world.x - (int)mouse_pos_world.x % 32)/32, ((int)mouse_pos_world.y - (int)mouse_pos_world.y % 32)/32), 0, 150, 24, BLACK);
		DrawText(TextFormat("Tile Local Coordinate: %d, %d", (int)mouse_pos_world.x % 32, (int)mouse_pos_world.y % 32), 0, 175, 24, BLACK);
		DrawText(TextFormat("Tile Number: %d", tile_num), 0, 200, 24, BLACK);
	}
#endif

	EndDrawing();
}

int main(void)
{
	InitWindow(w_width, w_height, "Fish 'n' dip"); // Catch and dash ... horrible name ideas

	load_textures();

	//needs a real allocator
	player = alloc_entity(E_player);
	ent[player].pos = (Vector2){200, 200};

	create_enemy(300, 200);

	//World map = {0};
	map.height = map.width = 64;

	//Why are these two separate functions?
	generate_map(&map, 50, 32);
	generate_vegetation(&map);

	SetTargetFPS(60);

	Camera2D camera = {0};
	camera.target = (Vector2){ent[player].pos.x, ent[player].pos.y};
	camera.offset = (Vector2){w_width / 2, w_height / 2};
	camera.rotation = 0.0f;
	camera.zoom = 1.5f;

	//Main loop
	while(!WindowShouldClose()) {
		Entity *o_player = &ent[player];

		//Lots of camera stuff here
		static float camera_min_speed = 30;
		static float min_effect_length = 10;
		static float fraction_speed = 5.0f;

		camera.offset = (Vector2){w_width / 2, w_height / 2};

		Vector2 diff = Vector2Subtract(o_player->pos, camera.target);
		float length = Vector2Length(diff);

		if(length > min_effect_length){
			float speed = fmaxf(fraction_speed * length, camera_min_speed);
			camera.target = Vector2Add(camera.target, Vector2Scale(diff, speed * GetFrameTime() / length));
		}
		//camera stuff ends

		update_enemy();
		update();
		physics();
		draw(camera);
	}

	for(int i = 0; i < MAX_TEX; ++i) {
		UnloadTexture(tile_textures[i]);
		UnloadTexture(vege_textures[i]);
	}
	UnloadTexture(player_texture);
#ifdef DEV
	unload();
#endif
	CloseWindow();

	return 0;
}
