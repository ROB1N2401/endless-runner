#include "Player.h"

Player::Player()
{
	m_state = new RunningState();
	m_animation = m_state->stateAnimation;
	transform.SetPosition(0, defaultPos);
	transform.SetScale(3, 3);
}

Player::~Player()
{
	delete m_state;
	delete m_animation;
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

void Player::Render()
{
	RenderManager::Instance()->Render(m_animation->frames[m_animation->currentFrame], transform);
}

void Player::Update(const float dt)
{
	//m_animation->Update();
	PlayerState* state = m_state->Update(*this, dt);
	if (state != NULL)
	{
		delete m_state;
		m_state = state;

		m_state->Enter(*this);
	}
}

PlayerState::~PlayerState() {}

RunningState::RunningState() 
{
	stateAnimation = new Animation(100, "player_run", "Resources/RunningAnimation.txt");
}

RunningState::~RunningState() {}

void RunningState::Enter(Player& player_in)
{
	player_in.transform.SetPosition(0, Player::defaultPos);
	player_in.SetAnimation(stateAnimation);

}

PlayerState* RunningState::OnKeyUp(Player& player_in, KeyCode key)
{
	if (key == KeyCode::SPACE)
		return new JumpingState();
	return nullptr;

}

PlayerState* RunningState::Update(Player& player_in, const float dt)
{
	player_in.GetAnimation()->Update();
	return nullptr;
}

JumpingState::JumpingState() : m_gravity(0.0f, 9.8f), m_velocity(0.0f, -50.0f)
{
	isFallingDown = false;
	stateAnimation = new Animation(1000, "player_jump", "Resources/JumpingAnimation.txt");
}

JumpingState::~JumpingState() {}

void JumpingState::Enter(Player& player_in)
{
	player_in.SetAnimation(stateAnimation);
}

PlayerState* JumpingState::OnKeyUp(Player& player_in, KeyCode key) { return nullptr; }

PlayerState* JumpingState::Update(Player& player_in, const float dt)
{
	Helium::Vector2 dpos = m_velocity * dt;
	player_in.transform.ChangePosition(dpos);
	
	Helium::Vector2 dvelocity = m_gravity * dt;
	m_velocity = m_velocity + dvelocity;

	if (!isFallingDown && m_velocity.y_ > 0)
	{
		player_in.GetAnimation()->SwitchFrames();
		isFallingDown = true;
	}

	if (player_in.transform.GetPosition().y_ > Player::defaultPos)
		return new RunningState();

	return nullptr;
}
