#pragma once
#include <string>
#include <map>
#include "SDL.h"
#include "SDL_image.h"

class TextureManager
{
public: 
	static TextureManager* Instance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new TextureManager();};

	std::map<std::string, SDL_Texture*> TextureMap;

	bool Load(const std::string& id_in, const std::string& imageFileName_in);
	void Remove(const std::string& id_in);
	void Clear();
	SDL_Texture* GetTexture(const std::string& id_in);
	void Draw(const std::string& id_in, const int x_in, const int y_in, const int width_in, const int height_in);

private:
	TextureManager() {}

	static TextureManager* s_Instance;
};