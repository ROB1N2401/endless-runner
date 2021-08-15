#pragma once
#include "RenderManager.h"

/* This collider class was initially taken from Jerry's code and slightly modified to suit the needs.
There was a code for collision check and colliders from lab that I could take, but there was too much of irrelevant or
redundant stuff */

class Collider
{
public:
	Collider();
	Collider(int x, int y, int w, int h, int x_offset, int y_offset);

	SDL_Rect rect;

	void Render();
	void SetPosition(int x, int y);

private: 
	int m_offset_x, m_offset_y;
};