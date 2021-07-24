#include "Player.h"

Player::Player()
{
	m_animation = new Animation("player_run", "Resources/RunningAnimation.txt");
	transform.SetPosition(0, 400);
	transform.SetScale(3, 3);
}

Player::~Player() { delete m_animation; }

void Player::Render()
{
	RenderManager::Instance()->Render(m_animation->frames[m_animation->currentFrame], transform);
}

void Player::Update(float dt)
{
	m_animation->Update();
}
