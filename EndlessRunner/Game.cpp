#include "AudioManager.h"
#include "TextureManager.h"
#include "FontManager.h"
#include "RenderManager.h"
#include "CollisionManager.h"
#include "Game.h"

Game::Game() : screen(this), quit(false)
{
}

Game::~Game()
{
	printf("Destroy Game\n");

	delete background;
	delete player;
	delete opossum;
	delete eagle;

	AudioManager::Instance()->Clear();
	TextureManager::Instance()->Clear();
	SDL_DestroyRenderer(RenderManager::Instance()->GetRenderer());
	SDL_DestroyWindow(screen.window);
	IMG_Quit();
	SDL_Quit();
}

void Game::CheckCollisons()
{
	if (CollisionManager::CheckCollision(player->collider, opossum->collider) 
		|| CollisionManager::CheckCollision(player->collider, eagle->collider))
		player->Die();
}

void Game::UpdateScore()
{
	int currentScore = SDL_GetTicks() / 10;
	score->text = "Score: " + std::to_string(currentScore);
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

	AudioManager::Instance()->LoadMusic("bg_music", "Assets/Audio/bgmusic.wav");
	AudioManager::Instance()->LoadSound("jump_sound", "Assets/Audio/jump.wav");
	AudioManager::Instance()->LoadSound("death_sound", "Assets/Audio/death.wav");
	AudioManager::Instance()->LoadSound("pickup_sound", "Assets/Audio/pickup.wav");

	TextureManager::Instance()->Load("player_run", "Assets/Spritesheets/player-run.png");
	TextureManager::Instance()->Load("player_die", "Assets/Spritesheets/player-die.png");
	TextureManager::Instance()->Load("player_jump", "Assets/Spritesheets/player-jump.png");
	TextureManager::Instance()->Load("opossum", "Assets/Spritesheets/opossum.png");
	TextureManager::Instance()->Load("eagle", "Assets/Spritesheets/eagle.png");
	TextureManager::Instance()->Load("layer_1", "Assets/Parallax/hills-layer-01.png");
	TextureManager::Instance()->Load("layer_2", "Assets/Parallax/hills-layer-02.png");
	TextureManager::Instance()->Load("layer_3", "Assets/Parallax/hills-layer-03.png");
	TextureManager::Instance()->Load("layer_4", "Assets/Parallax/hills-layer-04.png");
	TextureManager::Instance()->Load("layer_5", "Assets/Parallax/hills-layer-05.png");

	FontManager::Instance()->Load("font_main", "Assets/Fonts/quite_magical.ttf", 64);

	background = new Parallax(35.0f);
	player = new Player();
	opossum = new Opossum();
	eagle = new Eagle();

	score = new Text("font_main", SDL_Color{255, 255, 255, 255});
	score->transform.SetPosition(10, 10);

	AudioManager::Instance()->PlayMusic("bg_music");
}

void Game::Update(const float dt)
{
	if (player->isAlive)
	{
		CheckCollisons();
		UpdateScore();

		background->Update(dt);
		opossum->Update(dt);
		eagle->Update(dt);
	}

	player->Update(dt);
}

void Game::Render()
{
	RenderManager::Instance()->Clear(255, 255, 255, 255);

	background->Render();
	player->Render();
	opossum->Render();
	eagle->Render();

	score->Render();

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

