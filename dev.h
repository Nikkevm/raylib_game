#ifndef DEV_H
#define DEV_H

#include <stdbool.h>
#include "raylib.h"

extern bool dev_mode;
extern bool perlin_generated;

extern Image* get_noise_image();
void gen_perlin_noise();
void draw_dev_tools();
void unload();

#endif
