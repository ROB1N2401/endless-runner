#include "RenderManager.h"
#include "TextureManager.h"
#include "Game.h"

Game::Game() : screen(this), quit(false)
{
}

Game::~Game()
{
	printf("Destroy Game\n");

	delete background;
	delete player;

	TextureManager::Instance()->Clear();
	SDL_DestroyRenderer(RenderManager::Instance()->GetRenderer());
	SDL_DestroyWindow(screen.window);
	IMG_Quit();
	SDL_Quit();
}

void Game::OnKeyUp(KeyCode key)
{
	player->OnKeyUp(key);
}

void Game::OnKeyDown(KeyCode key)
{
	if (key == KeyCode::ESCAPE)
		quit = true;
}


void Game::Init()
{
	screen.Init();
	RenderManager::Instance()->Init(screen);

	TextureManager::Instance()->Load("player_run", "Assets/Spritesheets/player-run.png");
	TextureManager::Instance()->Load("player_jump", "Assets/Spritesheets/player-jump.png");
	TextureManager::Instance()->Load("layer_1", "Assets/Parallax/hills-layer-01.png");
	TextureManager::Instance()->Load("layer_2", "Assets/Parallax/hills-layer-02.png");
	TextureManager::Instance()->Load("layer_3", "Assets/Parallax/hills-layer-03.png");
	TextureManager::Instance()->Load("layer_4", "Assets/Parallax/hills-layer-04.png");
	TextureManager::Instance()->Load("layer_5", "Assets/Parallax/hills-layer-05.png");

	player = new Player();
	background = new Parallax(35.0f);
}

void Game::Update(const float dt)
{
	background->Update(dt);
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

	SDL_Event event;
	while (!quit)
	{
		while (SDL_PollEvent(&event)) {
			switch (event.type)
			{
			case SDL_QUIT: quit = true; break;
			case SDL_KEYDOWN: OnKeyDown(TranslateKeyCode(event.key.keysym.sym)); break;
			case SDL_KEYUP: OnKeyUp(TranslateKeyCode(event.key.keysym.sym)); break;
			}
		}

		Update(deltaTime);
		Render();
	}
}

