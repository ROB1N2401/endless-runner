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
}

void Game::Init()
{
	screen.Init();
	RenderManager::Instance()->Init(screen);
	TextureManager::Instance()->Load("forest", "ForestSprite.txt");
	//TextureManager::Instance()->Load("sea", "SeaSprite.txt");
	sea = new Sea();
}

void Game::Render()
{

}

void Game::Update(const float dt)
{

}

void Game::Run()
{
	Init();

	//SDL_Renderer* renderer_ = SDL_CreateRenderer(screen.window, -1, 0);

	Uint32 stored_deciseconds_ = 0;

	Animation running_("RunningAnimation.txt");
	SDL_Surface* surface2_ = IMG_Load(running_.spritesheet.imageFileName.c_str());
	SDL_Texture* texture2_ = SDL_CreateTextureFromSurface(RenderManager::Instance()->GetRenderer(), surface2_);
	SDL_Rect dstrect_player_ = SDL_Rect{ 0, 500, 100, 100, };

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

		Uint32 ticks_ = SDL_GetTicks();
		Uint32 deciseconds_ = ticks_ / 100;

		if (deciseconds_ > stored_deciseconds_)
		{
			running_ = UpdateSprite(running_);

			stored_deciseconds_ = deciseconds_;
		}

		RenderManager::Instance()->Clear(255, 255, 255, 255);

		//TextureManager::Instance()->Draw("sea", 0, 0, 176, 368);
		sea->Render();
		TextureManager::Instance()->Draw("forest", 0, 0, 384, 240);
		SDL_RenderCopy(RenderManager::Instance()->GetRenderer(), texture2_, &running_.frames[running_.currentFrame].source, &dstrect_player_);

		RenderManager::Instance()->Present();
	}
}

