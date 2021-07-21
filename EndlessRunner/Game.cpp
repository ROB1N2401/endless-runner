#include <iostream>
#include <fstream>
#include "SDL.h"
#include "SDL_image.h"
#include "RenderManager.h"
#include "TextureManager.h"
#include "SpriteSheet.h"
#include "Screen.h"
#include "Game.h"

Game::Game() : screen(this)
{

}

Game::~Game()
{
	printf("Destroy Game\n");
	delete sea;
	delete forest;
	delete player;
}

void Game::Init()
{
	screen.Init();
	RenderManager::Instance()->Init(screen);

	TextureManager::Instance()->Load("forest", "assets/sunny-land/environment/middle.png");
	TextureManager::Instance()->Load("sea", "assets/sunny-land/environment/back.png");
	TextureManager::Instance()->Load("player_run", "assets/sunny-land/player-run.png");


	player = new Player();
	sea = new Sea();
	forest = new Forest();
}

void Game::Render()
{
	RenderManager::Instance()->Clear(255, 255, 255, 255);

	sea->Render();
	forest->Render();
	player->Render();

	RenderManager::Instance()->Present();
}

void Game::Update(const float dt)
{
	player->Update(dt);
}

void Game::Run()
{
	Init();

	SDL_SetRenderDrawColor(RenderManager::Instance()->GetRenderer(), 255, 255, 255, 255);
	SDL_RenderClear(RenderManager::Instance()->GetRenderer());

	bool quit = false;
	SDL_Event event;
	while (!quit)
	{
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}

		Update(deltaTime);
		Render();
	}
}

