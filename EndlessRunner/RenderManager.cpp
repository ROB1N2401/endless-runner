#include "RenderManager.h"
#include "TextureManager.h"

RenderManager* RenderManager::m_Instance = nullptr;

SDL_Renderer* RenderManager::GetRenderer()
{
	return m_renderer;
}

void RenderManager::Init(Screen& screen_in)
{
	m_renderer = SDL_CreateRenderer(screen_in.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void RenderManager::Render(const Sprite& sprite_in, const Transform& transform_in)
{	
	SDL_Rect srcRect = sprite_in.GetSource();
	auto position = transform_in.GetPosition();
	auto scale = transform_in.GetScale();
	int w = static_cast<int>(sprite_in.GetSource().w * scale.x_);
	int h = static_cast<int>(sprite_in.GetSource().h * scale.y_);
	SDL_Rect dstRect = { static_cast<int>(position.x_), static_cast<int>(position.y_), w, h };
	SDL_RenderCopy(m_renderer, sprite_in.GetTexture(), &srcRect, &dstRect);
}

void RenderManager::Render(const SDL_Rect* rect_in)
{
	SDL_SetRenderDrawColor(m_renderer, 0, 255, 0, 255);
	SDL_RenderDrawRect(m_renderer, rect_in);
}

void RenderManager::Clear(int r, int g, int b, int a)
{
	SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
	SDL_RenderClear(m_renderer);
	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
}

void RenderManager::Present()
{
	SDL_RenderPresent(m_renderer);
}
