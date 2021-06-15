#pragma once

#include "SDL.h"

class Game;

class Screen
{
	Game* game;

public:
	SDL_Window* window;
	void Init();
	Screen(Game* game);
	~Screen();
};

