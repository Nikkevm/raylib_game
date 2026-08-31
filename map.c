#include "map.h"
#include "resources.h"

void render_map(World* map)
{
	for (int i = 0; i < map->tile_length; ++i) {
		DrawTexture(tile_textures[map->tile_type[i]], map->tile_x[i], map->tile_y[i], WHITE);
	}
}

void draw_vegetation(World* map)
{
	for(int i = 0; i < map->vege_length; ++i){
		DrawTexture(vege_textures[map->vege_type[i]], map->vege_x[i], map->vege_y[i], WHITE);
	}
}

void generate_map(World* map, int max_height, int cell_size)
{
	int index = 0;

	/* Note: scale could be a function parameter */
	Image noise = GenImagePerlinNoise(map->height, map->width, GetRandomValue(0, 256), GetRandomValue(0, 256), 1);

	for (int y = 0; y < map->height; ++y) {
        for (int x = 0; x < map->width; ++x) {

            unsigned char pixel_value = 0;

			if(!(x < 0 || x >= noise.width || y < 0 || y >= noise.height)){
				int index = 4 * (y * noise.width + x);
				pixel_value = ((unsigned char*)noise.data)[index + 0];
			}

            float normalized = pixel_value / 255.0f;

            float height_value = normalized * max_height;

			enum TileType tile = GRASS;
			if (height_value < max_height * 0.4f) tile = WATER;
			else if(height_value < max_height * 0.6f) tile = GRASS;

			map->tile_type[index] = tile;
			map->tile_x[index] = x * cell_size;
			map->tile_y[index] = y * cell_size;
			++index;
		}
	}
	map->tile_length = sizeof(map->tile_type)/sizeof(map->tile_type[0]);
	UnloadImage(noise);
}


void generate_vegetation(World* map)
{
	int index = 0;
	for(int i = 0 ; i < map->tile_length; ++i){
		if(map->tile_type[i] == GRASS){
			if(10 > GetRandomValue(0, 100)){
				int vege_rng = GetRandomValue(1, 5);
				if(vege_rng == 1) {
					map->vege_type[index] = FLOWER1;
					map->vege_x[index] = map->tile_x[i];
					map->vege_y[index] = map->tile_y[i];
					index++;
				}
				if(vege_rng == 2) {
					map->vege_type[index] = FLOWER2;
					map->vege_x[index] = map->tile_x[i];
					map->vege_y[index] = map->tile_y[i];
					index++;
				}
				if(vege_rng == 3) {
					map->vege_type[index] = STICK;
					map->vege_x[index] = map->tile_x[i];
					map->vege_y[index] = map->tile_y[i];
					index++;
				}
				if(vege_rng == 4) {
					map->vege_type[index] = TRUNK;
					map->vege_x[index] = map->tile_x[i];
					map->vege_y[index] = map->tile_y[i];
					index++;
				}
				if(vege_rng == 5) {
					map->vege_type[index] = BUSH;
					map->vege_x[index] = map->tile_x[i];
					map->vege_y[index] = map->tile_y[i];
					index++;
				}
			}
		}
	}
	map->vege_length = index;
}

Tile get_tile(World map, int index)
{
	return (Tile){ .type = map.tile_type[index], .x = map.tile_x[index], .y = map.tile_y[index]};
}
