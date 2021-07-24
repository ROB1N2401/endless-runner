#pragma once

#include <string>
#include <vector>
#include "SDL.h"
#include "SDL_image.h"

struct Sprite
{
public:
	Sprite();
	Sprite(const std::string& id_in);
	Sprite(const std::string& id_in, const std::string& spriteDataFileName_in);

	SDL_Rect GetSource() const { return source; };
	SDL_Texture* GetTexture() const { return texture; };
	void SetTexture(const std::string& id_in);
	void SetSource(int w_in, int h_in);
	void SetSource(int x_in, int y_in, int w_in, int h_in);
	void SetSource(const std::string& spriteDataFileName_in);

private:
	int x, y;
	int w, h;
	SDL_Texture* texture;
	SDL_Rect source;
};