#include <algorithm>
#include <fstream>
#include <sstream>
#include "AudioManager.h"
#include "TextureManager.h"
#include "FontManager.h"
#include "RenderManager.h"
#include "CollisionManager.h"
#include "Game.h"

#pragma region FSM
GameState::GameState() { m_easingTime = 0.f; }

GameState::~GameState() {}

void GameState::Render(Game& game_in)
{
	game_in.m_background->Render();
	game_in.m_player->Render();
	game_in.m_opossum->Render();
	game_in.m_eagle->Render();
	game_in.m_text->Render();
}

#pragma region MenuState
void MenuState::Enter(Game& game_in)
{
	game_in.m_text->text = "Press SPACE to begin!";
	game_in.m_text->transform.SetPosition(384.f, 256.f);
	game_in.m_text->SetColor(SDL_Color{ 0, 255, 255, 255 });

	game_in.m_score = 0.f;

	game_in.m_background->Reset();
	game_in.m_player->Reset();
	game_in.m_opossum->Reset();
	game_in.m_eagle->Reset();

	Camera::Instance()->Reset();
	AudioManager::Instance()->PlayMusic("bg_music");
}

void MenuState::Render(Game& game_in)
{
	game_in.m_background->Render();
	game_in.m_text->Render();
}

GameState* MenuState::OnKeyUp(Game& game_in, KeyCode key)
{
	if (key == KeyCode::SPACE)
		return new PlayState();

	return nullptr;
}

GameState* MenuState::Update(Game& game_in, const float dt)
{
	m_easingTime += dt;

	game_in.m_background->Update(dt);
	game_in.m_text->Update(dt, m_easingTime, 1.5f, 1.f * game_in.m_uiScaleModifier);

	return nullptr;
}
#pragma endregion

#pragma region PlayState
void PlayState::Enter(Game& game_in)
{
	game_in.m_text->text = "SCORE: ";
	game_in.m_text->transform.SetPosition(76.8f, 37.4f);
	game_in.m_text->SetColor(SDL_Color{ 0, 255, 255, 255 });
}

GameState* PlayState::OnKeyUp(Game& game_in, KeyCode key)
{
	game_in.m_player->OnKeyUp(key);
	if (key == KeyCode::P)
		return new PauseState();

	return nullptr;
}

GameState* PlayState::Update(Game& game_in, const float dt)
{
	m_easingTime += dt;

	game_in.m_score += (dt * 100.f);
	game_in.m_text->text = "Score: " + std::to_string(static_cast<int>(game_in.m_score));
	game_in.m_text->Update(dt, m_easingTime, 0.25f, 0.5f * game_in.m_uiScaleModifier);

	game_in.m_background->Update(dt);
	game_in.m_opossum->Update(dt);
	game_in.m_eagle->Update(dt);
	game_in.m_player->Update(dt);

	if (CollisionManager::CheckCollision(game_in.m_player->collider, game_in.m_opossum->collider)
		|| CollisionManager::CheckCollision(game_in.m_player->collider, game_in.m_eagle->collider))
		return new DeathState();

	return nullptr;
}
#pragma endregion

#pragma region PauseState
void PauseState::Enter(Game& game_in)
{
	game_in.m_text->text = "PAUSED";
	game_in.m_text->transform.SetPosition(384.f, 256.f);
	game_in.m_text->SetColor(SDL_Color{ 0, 255, 255, 255 });
}

GameState* PauseState::OnKeyUp(Game& game_in, KeyCode key)
{
	if (key == KeyCode::P)
		return new PlayState();

	return nullptr;
}
GameState* PauseState::Update(Game& game_in, const float dt)
{
	m_easingTime += dt;

	game_in.m_text->Update(dt, m_easingTime, 1.5f, 1.f * game_in.m_uiScaleModifier);

	return nullptr;
}
#pragma endregion

#pragma region DeathState
void DeathState::Enter(Game& game_in) 
{
	game_in.m_player->SetDeathState();

	std::ostringstream oss;
	oss << "     Game Over! \n     Score: " << static_cast<int>(game_in.m_score) << "\nPress SPACE to restart!";
	game_in.m_text->text = oss.str();
	game_in.m_text->transform.SetPosition(384.0f, 256.0f);
	game_in.m_text->SetColor(SDL_Color{ 255, 55, 0, 255 });
}

GameState* DeathState::OnKeyUp(Game& game_in, KeyCode key)
{
	if (key == KeyCode::SPACE)
		return new MenuState();

	return nullptr;
}

GameState* DeathState::Update(Game& game_in, const float dt)
{
	m_easingTime += dt;

	Camera::Instance()->Update(dt);
	game_in.m_text->Update(dt, m_easingTime, 1.5f, 0.7f * game_in.m_uiScaleModifier);
	game_in.m_player->Update(dt);

	return nullptr;
}
#pragma endregion
#pragma endregion


Game::Game() : m_screen(this), m_quit(false), m_score(0.0f), m_uiScaleModifier(1.0f)
{
	m_state = nullptr;
	m_background = nullptr;
	m_player = nullptr;
	m_opossum = nullptr;
	m_eagle = nullptr;
	m_text = nullptr;
}

Game::~Game()
{
	printf("Destroy Game\n");

	delete m_state;
	delete m_background;
	delete m_player;
	delete m_opossum;
	delete m_eagle;
	delete m_text;

	AudioManager::Instance()->Clear();
	TextureManager::Instance()->Clear();
	SDL_DestroyRenderer(RenderManager::Instance()->GetRenderer());
	SDL_DestroyWindow(m_screen.window);
	IMG_Quit();
	SDL_Quit();
}

void Game::ReadConfig()
{
	std::ifstream stream_;
	stream_.open("Resources/Config.ini");
	std::string line_;
	std::vector<std::string> values;
	while (std::getline(stream_, line_))
	{
		std::stringstream ss(line_);
		std::string value;
		for (int i = 0; i < 3; i++)
			ss >> value;
		values.push_back(value);
	}
	stream_.close();

	float uiScale = std::stof(values[0]) / 100.f;
	uiScale = std::clamp(uiScale, 0.f, 2.f);
	m_uiScaleModifier = uiScale;

	int volume = std::stoi(values[1]);
	volume = std::clamp(volume, 0, 128);
	AudioManager::Instance()->SetVolume(volume);

	float screenShakeStrength = std::stof(values[2]);
	screenShakeStrength = std::clamp(screenShakeStrength, 0.f, 10.f);
	Camera::Instance()->SetShakeStrength(screenShakeStrength);
}

void Game::Init()
{
	ReadConfig();

	m_screen.Init();
	RenderManager::Instance()->Init(m_screen);

	AudioManager::Instance()->LoadMusic("bg_music", "Assets/Audio/bgmusic.wav");
	AudioManager::Instance()->LoadSound("jump_sound", "Assets/Audio/jump.wav");
	AudioManager::Instance()->LoadSound("death_sound", "Assets/Audio/death.wav");

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

	m_background = new Parallax(350.0f);
	m_player = new Player();
	m_opossum = new Opossum();
	m_eagle = new Eagle();
	m_text = new Text("font_main", SDL_Color{255, 255, 255, 255});

	m_state = new MenuState();
	m_state->Enter(*this);
}

void Game::OnKeyUp(KeyCode key)
{
	GameState* state = m_state->OnKeyUp(*this, key);
	if (state != NULL)
	{
		delete m_state;

		m_state = state;
		m_state->Enter(*this);
	}
}

void Game::OnKeyDown(KeyCode key)
{
	if (key == KeyCode::ESCAPE)
		m_quit = true;
}

void Game::Update(const float dt)
{
	GameState* state = m_state->Update(*this, dt);
	if (state != NULL)
	{
		delete m_state;

		m_state = state;
		m_state->Enter(*this);
	}
}

void Game::Render()
{
	RenderManager::Instance()->Clear(255, 255, 255, 255);

	m_state->Render(*this);

	RenderManager::Instance()->Present();
}

void Game::Run()
{
	Init();

	Uint32 start = SDL_GetTicks();
	Uint32 current = start;
	Uint32 previous = start;

	SDL_Event event;
	while (!m_quit)
	{
		while (SDL_PollEvent(&event)) {
			switch (event.type)
			{
			case SDL_QUIT: m_quit = true; break;
			case SDL_KEYDOWN: OnKeyDown(TranslateKeyCode(event.key.keysym.sym)); break;
			case SDL_KEYUP: OnKeyUp(TranslateKeyCode(event.key.keysym.sym)); break;
			}
		}

		previous = current;
		current = SDL_GetTicks();
		Uint32 dticks = current - previous;
		float dtime = dticks / 1000.f;

		Update(dtime);
		Render();
	}
}
