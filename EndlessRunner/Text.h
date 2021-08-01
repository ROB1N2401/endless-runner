#pragma once

#include "SDL_ttf.h"
#include "Transform.h"
#include <string>

class Text
{
public:
	Text();
	Text(const std::string& id_in);
	Text(const std::string& id_in, SDL_Color color_in);

	void Render();
	void SetColor(SDL_Color& color_in);
	SDL_Color GetColor();
	TTF_Font* GetFont();

	std::string text;
	Transform transform;

private:
	SDL_Color m_color;
	TTF_Font* m_font;
};
