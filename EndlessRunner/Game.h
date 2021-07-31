#pragma once
#include "Screen.h"
#include "Sprite.h"
#include "Parallax.h"

#include "Player.h"
#include "Enemy.h"
#include "KeyCode.h"

#define deltaTime 0.16f

class Game
{
	bool quit;
	Screen screen;
	Opossum* opossum;
	Eagle *eagle;
	Player* player;
	Parallax* background;

	void CheckCollisons();
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

