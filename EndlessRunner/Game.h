#pragma once
#include "Screen.h"
#include "Text.h"
#include "Parallax.h"
#include "Player.h"
#include "Enemy.h"

#pragma region FSM
class GameState
{
public:
	GameState();
	~GameState();

	virtual void Enter(Game& game_in) = 0;
	virtual void Render(Game& game_in);
	virtual GameState* OnKeyUp(Game& game_in, KeyCode key) = 0;
	virtual GameState* Update(Game& game_in, const float dt) = 0;
protected:
	float m_easingTime;
};

class MenuState : public GameState
{
public:
	void Enter(Game& game_in) override;
	void Render(Game& game_in) override;
	GameState* OnKeyUp(Game& game_in, KeyCode key) override;
	GameState* Update(Game& game_in, const float dt) override;
};

class PlayState : public GameState
{
public:
	void Enter(Game& game_in) override;
	GameState* OnKeyUp(Game& game_in, KeyCode key) override;
	GameState* Update(Game& game_in, const float dt) override;
};

class PauseState : public GameState
{
public:
	void Enter(Game& game_in) override;
	GameState* OnKeyUp(Game& game_in, KeyCode key) override;
	GameState* Update(Game& game_in, const float dt) override;
};

class DeathState : public GameState
{
public:
	void Enter(Game& game_in) override;
	GameState* OnKeyUp(Game& game_in, KeyCode key) override;
	GameState* Update(Game& game_in, const float dt) override;
};
#pragma endregion

class Game
{
public:
	Game();
	~Game();

	void Run();

private:
	friend class GameState;
	friend class MenuState;
	friend class PlayState;
	friend class PauseState;
	friend class DeathState;

	bool m_quit;
	float m_uiScaleModifier;
	float m_score;
	Screen m_screen;
	GameState* m_state;

	Opossum* m_opossum;
	Eagle* m_eagle;
	Player* m_player;
	Parallax* m_background;
	Text* m_text; 

	//Game Loop
	void ReadConfig();
	void Init();
	void OnKeyUp(KeyCode key);
	void OnKeyDown(KeyCode key);
	void Update(const float dt);
	void Render();
};
