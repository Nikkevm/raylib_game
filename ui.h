#ifndef UI_H
#define UI_H

#include "raylib.h"
#include <stdbool.h>

typedef struct Panel {
	int width;
	int row_height;
	int at_x;
	int at_y;
} Panel;

typedef struct Button {
	const char* text;
	Color color;
	Color hover_color;
	Color clicked_color;
} Button;

void draw_text(const char* text, int x, int y);
bool draw_button(Button btn, int x, int y);
bool draw_button_ex(const char* text, int x, int y, Color color, Color clicked_color, Color hover_color);

#endif
