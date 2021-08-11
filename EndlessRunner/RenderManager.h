#pragma once

#include <string>
#include "Screen.h"
#include "Sprite.h"
#include "Text.h"
#include "Transform.h"
#include "SDL_image.h"

struct RenderManager
{
public:
	static RenderManager* Instance() { return m_Instance = (m_Instance != nullptr) ? m_Instance : new RenderManager(); };

	SDL_Renderer* GetRenderer();
	void Init(Screen& screen_in);
	void Render(const Sprite& sprite_in, const Transform& transform_in);
	void Render(Text* text_in);
	void Render(const SDL_Rect* rect_in);
	void Clear(int r, int g, int b, int a);
	void Present();

private:
	SDL_Renderer* m_renderer;
	static RenderManager* m_Instance;
};