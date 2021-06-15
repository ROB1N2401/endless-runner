#pragma once

#include <string>
#include <vector>
#include "SDL.h"

struct Sprite
{
	Sprite();
	Sprite(std::string spritesheetName_in);
	int x, y;
	int w, h;
	std::string imageFileName;
	SDL_Rect source;

	void SetImage(std::string spritesheetName_in);
	void SetSource(int x_in, int y_in, int w_in, int h_in);
};