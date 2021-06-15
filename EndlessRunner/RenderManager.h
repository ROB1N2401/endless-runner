#pragma once

#include "Screen.h"
#include "SDL_image.h"

struct RenderManager
{
	public:
		static RenderManager* Instance() { return m_Instance = (m_Instance != nullptr) ? m_Instance : new RenderManager(); };

	SDL_Renderer* GetRenderer();
	void Init(Screen& screen_in);
	void Render();
	void Clear();

	private:
		SDL_Renderer* m_renderer;
		static RenderManager* m_Instance;
};