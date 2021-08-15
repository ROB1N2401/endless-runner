#include "RenderManager.h"
#include "TextureManager.h"
#include "FontManager.h"
#include "Easing.h"

#pragma region Camera
Camera* Camera::s_Instance = nullptr;

Camera::Camera() : m_shakeDuration(2.0f), m_shakeStrength(5.0f) { Reset(); }

void Camera::Update(const float dt)
{
	if (m_shakeTime < m_shakeDuration)
	{
		m_easingTime += dt * m_easingDirection * m_shakeStrength;

		auto t = Easing::EaseInOutBounce(m_easingTime, 2.75f, 7.5625f, 0.0f);

		m_transform.ChangePosition(t * m_shakeStrength * m_shakeDirection, t * m_shakeStrength * m_shakeDirection);
		m_transform.SetScale(1.0f + (t / 5.0f * m_shakeStrength));
		m_transform.SetRotation(t * (5.f * m_shakeStrength * -m_shakeDirection));

		if (m_easingTime > 1.0f || m_easingTime < 0.0f)
			m_easingDirection = -m_easingDirection;

		if (m_easingTime <= 0.0f)
			m_shakeDirection = -m_shakeDirection;
	}
	else
	{
		m_transform.SetPosition(0.0f, 0.0f);
		m_transform.SetScale(1.0f);
		m_transform.SetRotation(0.0f);
	}

	m_shakeTime += dt;
}

void Camera::Reset()
{
	m_transform.SetPosition(0.0f, 0.0f);
	m_transform.SetScale(1.0f);
	m_transform.SetRotation(0.0f);

	m_shakeTime = 0.0f;
	m_easingTime = 0.0f;
	m_shakeDirection = 1;
	m_easingDirection = 1;
}

void Camera::SetShakeStrength(float shakeValue_in) { m_shakeStrength = shakeValue_in; }
#pragma endregion

RenderManager* RenderManager::s_Instance = nullptr;

SDL_Renderer* RenderManager::GetRenderer() { return m_renderer; }

void RenderManager::Init(Screen& screen_in)
{
	m_renderer = SDL_CreateRenderer(screen_in.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void RenderManager::Render(const Sprite& sprite_in, const Transform& transform_in)
{	
	SDL_Rect srcRect = sprite_in.GetSource();

	auto scale = transform_in.GetScale();
	int w = static_cast<int>(sprite_in.GetSource().w * scale.x_ * Camera::Instance()->m_transform.GetScale().x_);
	int h = static_cast<int>(sprite_in.GetSource().h * scale.y_ * Camera::Instance()->m_transform.GetScale().y_);

	Helium::Vector2 position;
	position.x_ = transform_in.GetPosition().x_ - Camera::Instance()->m_transform.GetPosition().x_;
	position.y_ = transform_in.GetPosition().y_ - Camera::Instance()->m_transform.GetPosition().y_;
	if (transform_in.pivotPoint == PivotPoint::CENTERED)
	{
		position.x_ -= w / 2;
		position.y_ -= h / 2;
	}

	SDL_Rect dstRect = { static_cast<int>(position.x_), static_cast<int>(position.y_), w, h };

	float angle = Camera::Instance()->m_transform.GetRotation();
	SDL_RenderCopyEx(m_renderer, sprite_in.GetTexture(), &srcRect, &dstRect, angle, nullptr, SDL_FLIP_NONE);
}

void RenderManager::Render(Text* text_in)
{
	SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(text_in->GetFont(), text_in->text.c_str(), text_in->GetColor(), 512);

	if (textSurface == nullptr)
	{
		SDL_Log("Unable to render text surface: %s", TTF_GetError());
		return;
	}
	else
	{
		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
		SDL_Rect srcRect = { 0, 0, textSurface->w, textSurface->h };
		auto scale = text_in->transform.GetScale();
		int w = static_cast<int>(textSurface->w * scale.x_);
		int h = static_cast<int>(textSurface->h * scale.y_);
		Helium::Vector2 position;
		position.x_ = text_in->transform.GetPosition().x_ - w / 2;
		position.y_ = text_in->transform.GetPosition().y_ - h / 2;
		SDL_Rect dstRect = { static_cast<int>(position.x_), static_cast<int>(position.y_), w, h };
		SDL_RenderCopy(m_renderer, textTexture, &srcRect, &dstRect);
		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(textTexture);
	}
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

void RenderManager::Present() {	SDL_RenderPresent(m_renderer); }

