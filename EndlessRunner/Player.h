#pragma once

#include "Entity.h"
#include "KeyCode.h"
#include "Animation.h"

class PlayerState;
class RunningState;

class Player : public Entity
{
public:
	Player();
	~Player();

	void OnKeyUp(KeyCode key);
	virtual void Render() final;
	virtual void Update(const float dt) final;

	Animation* GetAnimation() { return m_animation; };
	void SetAnimation(Animation* animation_in) { m_animation = animation_in; };

    static const int defaultPos = 395;

private:
	PlayerState* m_state;
	Animation* m_animation;
};


#pragma region StateMachine
class PlayerState
{
public:
	virtual ~PlayerState() = 0;

	virtual void Enter(Player& player_in) = 0;
	virtual PlayerState* OnKeyUp(Player& player_in, KeyCode key) = 0;
	virtual PlayerState* Update(Player& player_in, const float dt) = 0;

	Animation* stateAnimation;
};

class RunningState : public PlayerState
{
public:
	RunningState();
	~RunningState();

	void Enter(Player& player_in);
	PlayerState* OnKeyUp(Player& player_in, KeyCode key);
	PlayerState* Update(Player& player_in, const float dt);
};

class JumpingState : public PlayerState
{
public:
	JumpingState();
	~JumpingState();

	void Enter(Player& player_in);
	PlayerState* OnKeyUp(Player& player_in, KeyCode key);
	PlayerState* Update(Player& player_in, const float dt);
private:
	bool isFallingDown;
	Helium::Vector2 m_velocity;
	const Helium::Vector2 m_gravity;
};
#pragma endregion
