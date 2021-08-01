#include "FontManager.h"

FontManager* FontManager::m_Instance = nullptr;

bool FontManager::Load(const std::string& id_in, const std::string& fontFileName_in, const unsigned int size_in)
{
	if (FontMap.count(id_in) > 0)
		return true;

	TTF_Font* font = TTF_OpenFont(fontFileName_in.c_str(), size_in);
	if (font == nullptr)
	{
		SDL_Log("Failed to load font: %s, %s", fontFileName_in.c_str(), TTF_GetError());
		return false;
	}

	FontMap[id_in] = font;
	return true;
}

TTF_Font* FontManager::GetFont(const std::string& id_in)
{
	if (!(FontMap.count(id_in) > 0))
	{
		SDL_Log("Failed to find font with the next id: %s, %s", id_in.c_str(), TTF_GetError());
		return nullptr;
	}
	else
		return FontMap.find(id_in)->second;
}

void FontManager::Clear()
{
	std::map<std::string, TTF_Font*>::iterator it;
	for (it = FontMap.begin(); it != FontMap.end(); it++)
		TTF_CloseFont(it->second);

	FontMap.clear();
}
