#pragma once

#include "Screen.h"
#include "RenderManager.h"
#include "Animation.h"
#include "Sprite.h"

class Game
{
	Screen screen;

	void Init();
public:
	void Run();
	Game();
	~Game();
};

