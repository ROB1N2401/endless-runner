#pragma once
#include "Screen.h"
#include "Sprite.h"
#include "Parallax.h"

#include "Player.h"

#define deltaTime 0.16f

class Game
{
	Screen screen;
	Player* player;
	Parallax* background;

	void Init();
	void Render();
	void Update(const float dt);
public:
	void Run();
	Game();
	~Game();
};

