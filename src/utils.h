#pragma once
#include <string>
#include <SDL.h>
#include "SDL_SimpleApp.h"
#include "Vector2D.h"
/* Get the resource path for resources located in res/subDir */
//std::string getResourcePath(const std::string &subDir = "");

/* draw utilities */
void set_pixel(SDL_Renderer *rend, int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
void draw_circle(SDL_Renderer *surface, int n_cx, int n_cy, int rad, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

inline static Vector2D cell2pix(Vector2D cell) {
	int offset = CELL_SIZE / 2;
	return Vector2D(cell.x * CELL_SIZE + offset, cell.y * CELL_SIZE + offset);
}

static Vector2D pix2cell(Vector2D pix) {
	return Vector2D((float)((int)pix.x / CELL_SIZE), (float)((int)pix.y / CELL_SIZE));
}

