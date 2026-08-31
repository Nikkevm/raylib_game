#include "resources.h"

Texture textures[MAX_TEX] = {0}; /* This is currently not in use */
Texture tile_textures[MAX_TEX];
Texture vege_textures[MAX_TEX];

Texture player_texture;
Texture enemy_texture;

void load_textures()
{
	tile_textures[AIR] = LoadTexture("textures/air.png");
	tile_textures[GRASS] = LoadTexture("textures/grass.png");
	tile_textures[WATER] = LoadTexture("textures/water.png");

	vege_textures[FLOWER1] = LoadTexture("textures/flower1.png");
	vege_textures[FLOWER2] = LoadTexture("textures/flower2.png");
	vege_textures[STICK] = LoadTexture("textures/Twig.png");
	vege_textures[TRUNK] = LoadTexture("textures/Trunk.png");
	vege_textures[BUSH] = LoadTexture("textures/Bush.png");

	player_texture = LoadTexture("textures/char.png");
	enemy_texture = LoadTexture("textures/enemy.png");
}
