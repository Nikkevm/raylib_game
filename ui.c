#include "ui.h"
#include "raymath.h"
#include <stdio.h>

Color c_lerp(Color start, Color end, float amount) // probably not gonna even use this also doesn't even work
{
	Vector3 start_f = {(float)start.r / 255, (float)start.g / 255, (float)start.b / 255};
	Vector3 end_f = {(float)end.r / 255, (float)end.g / 255, (float)end.b / 255};
	Vector3 mul = {255, 255, 255};
	Vector3 temp = Vector3Multiply(Vector3Lerp(start_f, end_f, amount), mul);
	Color result = {temp.x, temp.y, temp.z, 255};
	return result;
}

void draw_text(const char* text, int x, int y) /*  Kinda useless */
{
	DrawText(text, x, y, 20, BLACK);
}

bool draw_button(Button btn, int x, int y)
{
	return draw_button_ex(btn.text, x, y, btn.color, btn.clicked_color, btn.hover_color);
}

bool draw_button_ex(const char* text, int x, int y, Color color, Color clicked_color, Color hover_color)
{
	Font font = GetFontDefault();
	int padding = 8;
	int font_size = font.baseSize*2;
	int text_width = MeasureText(text, font_size);
	int text_height = font_size;

	Color font_color = BLACK;

	Rectangle rect = {
		x,
		y,
		text_width + padding * 2,
		text_height + padding * 2
	};

	bool btn_action = false;
	Vector2 mouse_pnt = GetMousePosition();

	if(CheckCollisionPointRec(mouse_pnt, rect)){
		color = hover_color;

		if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
			color = clicked_color;
			font_color = WHITE;
		}

		if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
			btn_action = true;
		}
	}

	DrawRectangleRec(rect, color);
	DrawText(text, rect.x + padding, rect.y + padding, font_size, font_color);

	return btn_action;
}
