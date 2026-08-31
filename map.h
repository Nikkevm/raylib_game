#ifndef MAP_H
#define MAP_H

#include "raylib.h"

#define MAP_SIZE 4096
#define MAX_VEGE 1024

typedef struct { // Nocheckin this is currently useless
	enum TileType type;
	int x;
	int y;
} Tile;

typedef struct {
	enum TileType tile_type[MAP_SIZE];
	int tile_x[MAP_SIZE];
	int tile_y[MAP_SIZE];
	size_t tile_length;

	enum VegeType vege_type[MAX_VEGE];
	int vege_x[MAX_VEGE];
	int vege_y[MAX_VEGE];
	size_t vege_length;

	int height; // Are these only used when generating the map??? Why are these here???
	int width;
} World;

void render_map(World* map);
void draw_vegetation(World* map);
void generate_map(World* map, int max_height, int cell_size);
void generate_vegetation(World* map);
Tile get_tile(World map, int index);

#endif
