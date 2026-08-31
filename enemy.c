#include "enemy.h"
#include <stdio.h>
#include "raylib.h"
#include "resources.h"
#include "raymath.h"

/*
  Absolutely horrendous enemy entity test.
*/

enum EState{IDLE, LOOKING, MOVING, COUNT};

// Todo: horrible data structure
typedef struct {
	float px[MAX_ENEMY];
	float py[MAX_ENEMY];
	float vx[MAX_ENEMY];
	float vy[MAX_ENEMY];
	int pid[MAX_ENEMY];
	float tx[MAX_ENEMY];
	float ty[MAX_ENEMY];
	float idle_time[MAX_ENEMY];
	int is_idle[MAX_ENEMY];
	enum EState state[MAX_ENEMY];
	int enemies;
} Enemy_table;

Enemy_table enemy_table = {0};

void create_enemy(int px, int py)
{
	if(enemy_table.enemies >= MAX_ENEMY){
		return;
	}

	enemy_table.pid[enemy_table.enemies] = enemy_table.enemies;
	enemy_table.px[enemy_table.enemies] = px;
	enemy_table.py[enemy_table.enemies] = py;
	enemy_table.tx[enemy_table.enemies] = 0;
	enemy_table.ty[enemy_table.enemies] = 0;
	enemy_table.state[enemy_table.enemies] = IDLE;
	enemy_table.idle_time[enemy_table.enemies] = 0.0f;
	enemy_table.is_idle[enemy_table.enemies] = 0;

	enemy_table.enemies++;
}

void draw_enemy()
{
	Rectangle source_rec = {0.0f, 0.0f, (float)enemy_texture.width, -(float)enemy_texture.height};

	for(int i = 0; i < enemy_table.enemies; ++i){
		Rectangle dest_rec = {enemy_table.px[i], enemy_table.py[i], enemy_texture.width, enemy_texture.height};

		Vector2 origin = {enemy_texture.width / 2, enemy_texture.height / 2};

		float rotation = 90.0f;

		DrawTexturePro(enemy_texture, source_rec, dest_rec, origin, rotation, WHITE);
	}
}

enum EState enemy_state_change(enum Estate state)
{
	int roll = 0;
	if(state == MOVING) {
		return MOVING;
	}
	if(state == LOOKING) {
		return LOOKING;
	}
	if(state == IDLE) {
		roll = GetRandomValue(0, 100);
		if(roll > 1) {
			return IDLE;
		}
		else {
			return LOOKING;
		}
	}
}

Vector2 enemy_look(int x, int y, float max_radius)
{
	float theta = ((float)GetRandomValue(0.0f, 100.0f) / 100.0f) * 2.0f * PI;
	float u = GetRandomValue(0.0f, 100.0f) / 100.0f;
	float r = max_radius * sqrtf(u);
	Vector2 p = { x + r * cosf(theta),
				  y + r * sinf(theta) };
	return p;
}

void update_enemy()
{
	for(int i = 0; i < enemy_table.enemies; ++i){
		enemy_table.state[i] = enemy_state_change(enemy_table.state[i]); //might need to just send a pointer and mutate it.
		if(enemy_table.state[i] == IDLE){
			if(!enemy_table.is_idle[i]){
				enemy_table.idle_time[i] = GetRandomValue(3.0f, 8.0f);
			//	printf("state: %d, idle_time: %f\n", enemy_table.state[i], enemy_table.idle_time[i]);
				enemy_table.idle_time[i] = enemy_table.idle_time[i] + GetTime();
				enemy_table.is_idle[i] = 1;
			}
			if(enemy_table.idle_time[i] > GetTime()){
				enemy_table.is_idle[i] = 0;
			}
		}
		if(enemy_table.state[i] == MOVING){
			enemy_table.px[i] = Lerp(enemy_table.px[i], enemy_table.tx[i], 0.1f);
			enemy_table.py[i] = Lerp(enemy_table.py[i], enemy_table.ty[i], 0.1f);
			if(Vector2Distance((Vector2){enemy_table.px[i], enemy_table.py[i]}, (Vector2){enemy_table.tx[i], enemy_table.ty[i]}) < 2.0f) {
			//	printf("target reached\n");
				enemy_table.state[i] = IDLE;
			}
		}
		if(enemy_table.state[i] == LOOKING) {
			Vector2 target = enemy_look(enemy_table.px[i], enemy_table.py[i], 300.0f);
			enemy_table.tx[i] = target.x;
			enemy_table.ty[i] = target.y;
			enemy_table.state[i] = MOVING;
		}
	}
}
