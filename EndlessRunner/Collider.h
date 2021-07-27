/*This collider class was initially taken from Jerry's code and slightly expanded upon. 
There was a code for collision check and colliders from lab, but there was too much of irrelevant or 
redundant stuff*/
#pragma once

#include "RenderManager.h"

class Collider
{
public:
	Collider();
	Collider(const Collider& rhs);
	Collider(int x, int y, int w, int h);
	Collider(int x, int y, int w, int h, int x_offset, int y_offset);

	void Render();
	void SetPosition(int x, int y);
	void SetOffsets(int x, int y);
	void SetSize(int w, int h);

	SDL_Rect rect;
private: 
	int m_offset_x, m_offset_y;
};