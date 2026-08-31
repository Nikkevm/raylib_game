#include "dev.h"
#include "ui.h"

bool dev_mode = false;

bool perlin_generated = false;

Texture noise_tex;
Image noise_img;

Image* get_noise_image()
{
	return (&noise_img);
}

void gen_perlin_noise()
{
	int offset_x = GetRandomValue(0, 256);
	int offset_y = GetRandomValue(0, 256);
	noise_img = GenImagePerlinNoise(64, 64, offset_x, offset_y, 1);
	noise_tex = LoadTextureFromImage(noise_img);
}

void draw_dev_tools()
{
	DrawText("Dev Tools", 0, 0, 16, RED);

	Button gen_noise_btn = {"Generate perlin noise", ORANGE, GREEN, BLACK};

	{
		if(draw_button(gen_noise_btn, 0, 600)){
			gen_perlin_noise();
			if(!perlin_generated) perlin_generated = true;
		}
	}

	if(perlin_generated){
		DrawTexture(noise_tex, 0, 300, WHITE);
	}
}

void unload()
{
	UnloadImage(noise_img);
	UnloadTexture(noise_tex);
}
