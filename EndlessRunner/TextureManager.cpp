#include "TextureManager.h"
#include "RenderManager.h"

bool TextureManager::Load(std::string id_in, std::string filename_in)
{
	SDL_Surface* surface = IMG_Load(filename_in.c_str());
	if (surface == nullptr)
	{
		SDL_Log("Failed to create a surface out of sprite: %s, %s", filename_in.c_str(), SDL_GetError());
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(RenderManager::Instance()->GetRenderer(), surface);
	if (texture == nullptr)
	{
		SDL_Log("Failed to create a surface out of sprite: %s", SDL_GetError());
	}

	m_TextureMap[id_in] = texture;
	return false;
}

void TextureManager::Draw(std::string id_in, int x_in, int y_in, int width_in, int height_in)
{
}

void TextureManager::Remove(std::string id_in)
{
}

void TextureManager::Clean()
{
}

