#include "TextureManager.h"
#include "RenderManager.h"
#include <fstream>
#include <sstream>

TextureManager* TextureManager::s_Instance = nullptr;

bool TextureManager::Load(const std::string& id_in, const std::string& imageFileName_in)
{
	if (TextureMap.count(id_in) > 0)
		return true;

	SDL_Surface* surface = IMG_Load(imageFileName_in.c_str());
	if (surface == nullptr)
	{
		SDL_Log("Failed to create a surface out of sprite: %s, %s", imageFileName_in.c_str(), SDL_GetError());
		return false;
	}

	SDL_Texture* m_texture = SDL_CreateTextureFromSurface(RenderManager::Instance()->GetRenderer(), surface);
	SDL_FreeSurface(surface);
	if (m_texture == nullptr)
	{
		SDL_Log("Failed to create a surface out of sprite: %s", SDL_GetError());
		return false;
	}

	TextureMap[id_in] = m_texture;
	return true;
}

void TextureManager::Draw(const std::string& id_in, const int x_in, const int y_in, const int width_in, const int height_in)
{
	SDL_Rect srcRect = { 0, 0, width_in, height_in };
	SDL_Rect dstRect = { x_in, y_in, width_in, height_in };
	SDL_RenderCopy(RenderManager::Instance()->GetRenderer(), TextureMap[id_in], &srcRect, &dstRect);
}

void TextureManager::Remove(const std::string& id_in)
{
	SDL_DestroyTexture(TextureMap[id_in]);
	TextureMap.erase(id_in);
}

void TextureManager::Clear()
{
	std::map<std::string, SDL_Texture*>::iterator it;
	for (it = TextureMap.begin(); it != TextureMap.end(); it++)
		SDL_DestroyTexture(it->second);

	TextureMap.clear();
}

SDL_Texture* TextureManager::GetTexture(const std::string& id_in)
{
	if (!(TextureMap.count(id_in) > 0))
	{
		SDL_Log("Failed to find a texture with the next id: %s, %s", id_in.c_str(), SDL_GetError());
		return nullptr;
	}
	else
		return TextureMap.find(id_in)->second;
}

