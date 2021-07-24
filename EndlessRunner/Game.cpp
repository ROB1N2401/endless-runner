#include "RenderManager.h"
#include "TextureManager.h"
#include "Game.h"

Game::Game() : screen(this)
{

}

Game::~Game()
{
	printf("Destroy Game\n");
	delete background;
	delete player;

	TextureManager::Instance()->Clear();
}

void Game::Init()
{
	screen.Init();
	RenderManager::Instance()->Init(screen);

	TextureManager::Instance()->Load("player_run", "Assets/Spritesheets/player-run.png");
	TextureManager::Instance()->Load("layer_1", "Assets/Parallax/hills-layer-01.png");
	TextureManager::Instance()->Load("layer_2", "Assets/Parallax/hills-layer-02.png");
	TextureManager::Instance()->Load("layer_3", "Assets/Parallax/hills-layer-03.png");
	TextureManager::Instance()->Load("layer_4", "Assets/Parallax/hills-layer-04.png");
	TextureManager::Instance()->Load("layer_5", "Assets/Parallax/hills-layer-05.png");

	player = new Player();
	background = new Parallax(4.0f);
}

void Game::Update(const float dt)
{
	background->Update();
	player->Update(dt);
}

void Game::Render()
{
	RenderManager::Instance()->Clear(255, 255, 255, 255);

	background->Render();
	player->Render();

	RenderManager::Instance()->Present();
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

