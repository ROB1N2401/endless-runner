#pragma once
#include "Screen.h"
#include "Sprite.h"
#include "Text.h"
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
	Eagle* eagle;
	Player* player;
	Parallax* background;
	Text* score; 

	//Game Loop
	void OnKeyUp(KeyCode key);
	void OnKeyDown(KeyCode key);
	void Init();
	void Render();
	void Update(const float dt);

	//Other
	void CheckCollisons();
	void UpdateScore();

public:
	Game();
	~Game();

	void Run();
};

