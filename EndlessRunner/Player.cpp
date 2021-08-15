#include "Player.h"
#include "AudioManager.h"

Player::Player()
{
	m_state = new RunningState();

	animation = m_state->stateAnimation;

	transform.SetPosition(0, defaultPos);
	transform.SetScale(3.f, 3.f);
	
	int x = static_cast<int>(transform.GetPosition().x_);
	int y = static_cast<int>(transform.GetPosition().y_);
	int w = static_cast<int>(18.f * transform.GetScale().x_);
	int h = static_cast<int>(22.f * transform.GetScale().y_);
	int x_offset = static_cast<int>(6.f * transform.GetScale().x_);
	int y_offset = static_cast<int>(10.f * transform.GetScale().y_);
	collider = new Collider(x, y, w, h, x_offset, y_offset);

	isAlive = true;
}

Player::~Player()
{
	delete m_state;
	delete animation;
	delete collider;
}

void Player::OnKeyUp(KeyCode key)
{
	PlayerState* state = m_state->OnKeyUp(*this, key);
	if (state != NULL)
	{
		delete m_state;

		m_state = state;
		m_state->Enter(*this);
	}
}

void Player::Reset()
{
	delete m_state;

	m_state = new RunningState();
	m_state->Enter(*this);
}

void Player::Update(const float dt)
{
	collider->SetPosition(static_cast<int>(this->transform.GetPosition().x_), static_cast<int>(this->transform.GetPosition().y_));
	PlayerState* state = m_state->Update(*this, dt);
	if (state != NULL)
	{
 		delete m_state;
		m_state = state;

		m_state->Enter(*this);
	}
}

void Player::SetDeathState()
{
	delete m_state;
	m_state = new DyingState();

	m_state->Enter(*this);
}

PlayerState::PlayerState() { stateAnimation = nullptr; }

PlayerState::~PlayerState() {}

#pragma region RunningState
RunningState::RunningState() 
{ 
	stateAnimation = new Animation(100, "player_run", "Resources/RunningAnimation.txt"); 
}

void RunningState::Enter(Player& player_in)
{
	player_in.transform.SetPosition(0, Player::defaultPos);
	player_in.animation = stateAnimation;
}

PlayerState* RunningState::OnKeyUp(Player& player_in, KeyCode key)
{
	if (key == KeyCode::SPACE)
		return new JumpingState();

	return nullptr;
}

PlayerState* RunningState::Update(Player& player_in, const float dt)
{
	player_in.animation->Update();

	return nullptr;
}
#pragma endregion

#pragma region JumpingState
JumpingState::JumpingState() : m_gravity(0.0f, 9.8f), m_velocity(0.0f, -80.0f)
{
	m_isFallingDown = false;
	stateAnimation = new Animation(1000, "player_jump", "Resources/JumpingAnimation.txt");
}

void JumpingState::Enter(Player& player_in)
{
	AudioManager::Instance()->PlaySound("jump_sound");
	player_in.animation = stateAnimation;
}

PlayerState* JumpingState::OnKeyUp(Player& player_in, KeyCode key) { return nullptr; }

PlayerState* JumpingState::Update(Player& player_in, const float dt)
{
	Helium::Vector2 dpos = m_velocity * dt * 10.f;
	player_in.transform.ChangePosition(dpos);
	
	Helium::Vector2 dvelocity = m_gravity * dt * 10.f;
	m_velocity = m_velocity + dvelocity;

	if (!m_isFallingDown && m_velocity.y_ > 0)
	{
		player_in.animation->SwitchFrames();
		m_isFallingDown = true;
	}

	if (player_in.transform.GetPosition().y_ > Player::defaultPos)
		return new RunningState();

	return nullptr;
}
#pragma endregion

#pragma region DyingState
DyingState::DyingState() : m_gravity(0.0f, 9.8f), m_velocity(0.0f, -50.0f)
{
	stateAnimation = new Animation(400, "player_die", "Resources/DyingAnimation.txt");
}

void DyingState::Enter(Player& player_in)
{
	AudioManager::Instance()->PlaySound("death_sound");
	player_in.isAlive = false;
	player_in.animation = stateAnimation;
}

PlayerState* DyingState::OnKeyUp(Player& player_in, KeyCode key) { return nullptr; }

PlayerState* DyingState::Update(Player& player_in, const float dt)
{
	Helium::Vector2 dpos = m_velocity * dt * 10.0f;
	player_in.transform.ChangePosition(dpos);

	Helium::Vector2 dvelocity = m_gravity * dt * 10.0f;
	m_velocity = m_velocity + dvelocity;

	player_in.animation->Update();

	return nullptr;
}
#pragma endregion
