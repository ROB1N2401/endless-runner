#pragma once

#include <map>
#include <string>
#include "SDL_ttf.h"

class FontManager
{
public:
	static FontManager* Instance() { return m_Instance = (m_Instance != nullptr) ? m_Instance : new FontManager(); };

	bool Load(const std::string& id_in, const std::string& fontFileName_in, const unsigned int size_in);
	TTF_Font* GetFont(const std::string& id_in);
	void Clear();

	std::map<std::string, TTF_Font*> FontMap;

private:
	FontManager() {};
	static FontManager* m_Instance;
};