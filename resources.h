#ifndef RESOURCES_H
#define RESOURCES_H

#include "raylib.h"

#define MAX_TEX 64

enum TileType{AIR, GRASS, WATER};

enum VegeType{FLOWER1, FLOWER2, STICK, TRUNK, BUSH};

extern Texture textures[MAX_TEX]; // Is this even used???
extern Texture tile_textures[MAX_TEX];
extern Texture vege_textures[MAX_TEX];
extern Texture player_texture;
extern Texture enemy_texture;

void load_textures();

#endif
