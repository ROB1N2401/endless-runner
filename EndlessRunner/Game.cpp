#include "Game.h"
#include "SDL.h"
#include "Screen.h"
#include <iostream>
#include <fstream>
#include "SpriteSheet.h"
#include "SDL_image.h"

Game::Game() : screen(this)
{

}

Game::~Game()
{
	printf("Destroy Game\n");
}

void Game::Init()
{
	screen.Init();
	RenderManager::Instance()->Init(screen);
}

void Game::Run()
{
	Init();

	//SDL_Renderer* renderer_ = SDL_CreateRenderer(screen.window, -1, 0);

	Animation running_ = Animation("RunningAnimation.txt");
	Sprite bg_sea_ = Sprite("SeaSprite.txt");
	Sprite bg_forest_ = Sprite("ForestSprite.txt");
	Uint32 stored_deciseconds_ = 0;

	SDL_Surface* surface2_ = IMG_Load(running_.spritesheet.imageFileName.c_str());
	SDL_Texture* texture2_ = SDL_CreateTextureFromSurface(RenderManager::Instance()->GetRenderer(), surface2_);

	SDL_Surface* surface4_ = IMG_Load(bg_sea_.imageFileName.c_str());
	SDL_Texture* texture4_ = SDL_CreateTextureFromSurface(RenderManager::Instance()->GetRenderer(), surface4_);

	SDL_Surface* surface5_ = IMG_Load(bg_forest_.imageFileName.c_str());
	SDL_Texture* texture5_ = SDL_CreateTextureFromSurface(RenderManager::Instance()->GetRenderer(), surface5_);

	SDL_Rect dstrect_ = SDL_Rect{ 0, 0, 800, 600, };
	SDL_Rect dstrect_forest_ = SDL_Rect{ 0, 216, 176, 368, };
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

		RenderManager::Instance()->Clear();

		SDL_RenderCopy(RenderManager::Instance()->GetRenderer(), texture4_, &bg_sea_.source, &dstrect_);
		SDL_RenderCopy(RenderManager::Instance()->GetRenderer(), texture5_, &bg_forest_.source, &dstrect_forest_);
		SDL_RenderCopy(RenderManager::Instance()->GetRenderer(), texture2_, &running_.frames[running_.currentFrame].source, &dstrect_player_);

		RenderManager::Instance()->Render();
	}
}

