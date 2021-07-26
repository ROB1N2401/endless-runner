#pragma once
#include "Screen.h"
#include "Sprite.h"
#include "Parallax.h"

#include "Player.h"
#include "KeyCode.h"

#define deltaTime 0.16f

class Game
{
	bool quit;
	Screen screen;
	Player* player;
	Parallax* background;

	void OnKeyUp(KeyCode key);
	void OnKeyDown(KeyCode key);
	void Init();
	void Render();
	void Update(const float dt);
public:
	Game();
	~Game();

	void Run();
};

