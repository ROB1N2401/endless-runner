#pragma once

#include <string>
#include <vector>
#include "SDL.h"
#include "SDL_image.h"

struct Sprite
{
	Sprite();
	Sprite(const std::string& id_in, const std::string& spritesheetName_in);
	int x, y;
	int w, h;
	SDL_Texture* texture;
	SDL_Rect source;

	void SetTexture(const std::string& id_in);
	void SetSource(int w_in, int h_in);
	void SetSource(int x_in, int y_in, int w_in, int h_in);
};