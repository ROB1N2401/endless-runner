#include "RenderManager.h"

RenderManager* RenderManager::m_Instance = nullptr;

SDL_Renderer* RenderManager::GetRenderer()
{
	return m_renderer;
}

void RenderManager::Init(Screen& screen_in)
{
	m_renderer = SDL_CreateRenderer(screen_in.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void RenderManager::Render()
{
	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
	SDL_RenderPresent(m_renderer);
}

void RenderManager::Clear()
{
	SDL_RenderClear(m_renderer);
}
