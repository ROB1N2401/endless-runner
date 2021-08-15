#include "Collider.h"

Collider::Collider() : rect(SDL_Rect{ 0, 0, 0, 0 })
{
	m_offset_x = 0;
	m_offset_y = 0;
}

Collider::Collider(int x, int y, int w, int h, int x_offset, int y_offset) : rect(SDL_Rect{ x, y, w, h })
{
	m_offset_x = x_offset;
	m_offset_y = y_offset;
	SetPosition(x, y);
}

void Collider::Render() { RenderManager::Instance()->Render(&rect); }

void Collider::SetPosition(int x, int y)
{
	rect.x = x + m_offset_x;
	rect.y = y + m_offset_y;
}
