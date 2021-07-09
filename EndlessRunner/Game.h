#pragma once
#include "Screen.h"
#include "Sea.h"
#include "Animation.h"
#include "Sprite.h"

class Game
{
	Screen screen;
	Sea* sea;

	void Init();
	void Render();
	void Update(const float dt);
public:
	void Run();
	Game();
	~Game();
};

