#pragma once
#include <string>
#include <map>
#include "SDL.h"
#include "SDL_image.h"

class TextureManager
{
	public: 
		static TextureManager* Instance() { return m_Instance = (m_Instance != nullptr) ? m_Instance : new TextureManager();};

		bool Load(std::string id_in, std::string filename_in);
		void Remove(std::string id_in);
		void Clean();

		void Draw(std::string id_in, int x_in, int y_in, int width_in, int height_in);

	private:
		TextureManager() {}
		std::map<std::string, SDL_Texture*> m_TextureMap;
		static TextureManager* m_Instance;
};