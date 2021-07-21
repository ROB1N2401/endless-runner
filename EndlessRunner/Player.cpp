#include "Player.h"

Player::Player()
{
	m_animation = new Animation("player_run", "RunningAnimation.txt");
	transform.SetPosition(0, 460);
	transform.SetScale(4, 4);
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
