#pragma once
#include "Screen.h"
#include "Animation.h"
#include "Sprite.h"

#include "Player.h"
#include "Forest.h"
#include "Sea.h"

#define deltaTime 0.16f

class Game
{
	Screen screen;
	Sea* sea;
	Forest* forest;
	Player* player;

	void Init();
	void Render();
	void Update(const float dt);
public:
	void Run();
	Game();
	~Game();
};

