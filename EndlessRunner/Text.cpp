#include "Text.h"
#include "FontManager.h"
#include "RenderManager.h"

Text::Text() : transform(), text(""), m_color(SDL_Color{0, 0, 0, 0}), m_font(nullptr) {}

Text::Text(const std::string& id_in) : transform(), text(""), m_color(SDL_Color{ 255, 255, 255, 255 }) 
{
	m_font = FontManager::Instance()->GetFont(id_in);
}

Text::Text(const std::string& id_in, SDL_Color color_in) : transform(), text("")
{
	m_font = FontManager::Instance()->GetFont(id_in);
	m_color = color_in;
}

void Text::Render() { RenderManager::Instance()->Render(this); }

void Text::SetColor(SDL_Color color_in) { m_color = color_in; }

SDL_Color Text::GetColor() { return m_color; }

TTF_Font* Text::GetFont() { return m_font; }
