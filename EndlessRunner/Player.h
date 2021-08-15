#pragma once
#include "Entity.h"
#include "KeyCode.h"

class PlayerState;

class Player : public Entity
{
public:
	Player();
	~Player();

	bool isAlive;
    static const int defaultPos = 405;

	void OnKeyUp(KeyCode key);
	virtual void Reset() override;
	virtual void Update(const float dt) override;
	void SetDeathState();

private:
	PlayerState* m_state;
};


#pragma region FSM
class PlayerState
{
public:
	PlayerState();
	virtual ~PlayerState() = 0;

	Animation* stateAnimation;

	virtual void Enter(Player& player_in) = 0;
	virtual PlayerState* OnKeyUp(Player& player_in, KeyCode key) = 0;
	virtual PlayerState* Update(Player& player_in, const float dt) = 0;
};

class RunningState : public PlayerState
{
public:
	RunningState();

	void Enter(Player& player_in) override;
	PlayerState* OnKeyUp(Player& player_in, KeyCode key) override;
	PlayerState* Update(Player& player_in, const float dt) override;
};

class JumpingState : public PlayerState
{
public:
	JumpingState();

	void Enter(Player& player_in) override;
	PlayerState* OnKeyUp(Player& player_in, KeyCode key) override;
	PlayerState* Update(Player& player_in, const float dt) override;

private:
	bool m_isFallingDown;
	Helium::Vector2 m_velocity;
	const Helium::Vector2 m_gravity;
};

class DyingState : public PlayerState
{
public:
	DyingState();

	void Enter(Player& player_in) override;
	PlayerState* OnKeyUp(Player& player_in, KeyCode key) override;
	PlayerState* Update(Player& player_in, const float dt) override;

private:
	Helium::Vector2 m_velocity;
	const Helium::Vector2 m_gravity;
};
#pragma endregion
