#pragma once

#include <string>
#include "Screen.h"
#include "Sprite.h"
#include "Text.h"
#include "Transform.h"
#include "SDL_image.h"

class Camera
{
public:
	static Camera* Instance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Camera(); };

	void Update(const float dt);
	void Reset();
	void SetShakeStrength(float shakeValue_in);

private:
	Camera();

	friend class RenderManager;

	const float m_shakeDuration;
	float m_shakeStrength;
	float m_easingTime;
	float m_shakeTime;
	int m_shakeDirection;
	int m_easingDirection;
	Transform m_transform;
	static Camera* s_Instance;

};

class RenderManager
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