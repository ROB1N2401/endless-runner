#pragma once
#include <string>
#include <map>
#include "SDL.h"
#include "SDL_image.h"

class TextureManager
{
	public: 
		static TextureManager* Instance() { return m_Instance = (m_Instance != nullptr) ? m_Instance : new TextureManager();};

		bool Load(const std::string& id_in, const std::string& spritesheetName_in);
		void Remove(const std::string& id_in);
		void Clear();
		SDL_Texture* GetTexture(const std::string& id_in);

		void Draw(const std::string& id_in, const int x_in, const int y_in, const int width_in, const int height_in);

		std::map<std::string, SDL_Texture*> TextureMap;

	private:
		TextureManager() {}
		static TextureManager* m_Instance;
};