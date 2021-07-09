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
	SDL_Rect srcRect = sprite_in.source;
	auto position = transform_in.GetPosition();
	auto scale = transform_in.GetScale();
	float w = sprite_in.source.w * scale.x_;
	float h = sprite_in.source.h * scale.y_;
	SDL_Rect dstRect = { position.x_, position.y_, w, h };
	SDL_RenderCopy(m_renderer, sprite_in.texture, &srcRect, &dstRect);
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
