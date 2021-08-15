#pragma once

#include <map>
#include <string>
#include "SDL_ttf.h"

class FontManager
{
public:
	static FontManager* Instance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new FontManager(); };

	std::map<std::string, TTF_Font*> FontMap;

	bool Load(const std::string& id_in, const std::string& fontFileName_in, const unsigned int size_in);
	TTF_Font* GetFont(const std::string& id_in);
	void Clear();

private:
	FontManager() {};

	static FontManager* s_Instance;
};