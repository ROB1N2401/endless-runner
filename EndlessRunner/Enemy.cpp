#include "Enemy.h"
#include "Player.h"
#include <time.h>

Enemy::Enemy() : m_velocity(0.f, 0.f), m_minRange(0), m_maxRange(0) {}

Enemy::~Enemy() 
{
	delete animation;
	delete collider;
}

int Enemy::Randomize()
{
	const int addition = m_maxRange - m_minRange;
	
	srand(time(NULL));

	int num = m_minRange + rand() % addition;

	return num;
}

void Enemy::Update(const float dt)
{
	collider->SetPosition(this->transform.GetPosition().x_, this->transform.GetPosition().y_);
	animation->Update();

	Helium::Vector2 dpos = m_velocity * dt;
	transform.ChangePosition(dpos);

	if (transform.GetPosition().x_ < -100.f)
		transform.ChangePosition(Randomize(), 0.f);
}

Opossum::Opossum()
{
	m_velocity = Helium::Vector2(-50.0f, 0.f);
	m_minRange = 800.f;
	m_maxRange = 3200.f;

	animation = new Animation(150, "opossum", "Resources/OpossumAnimation.txt");

	transform.SetPosition(Randomize(), Player::defaultPos + 12);
	transform.SetScale(3.0f, 3.0f);

	int x = transform.GetPosition().x_;
	int y = transform.GetPosition().y_;
	int w = 28 * transform.GetScale().x_;
	int h = 18 * transform.GetScale().y_;
	int x_offset = -1 * transform.GetScale().x_;
	int y_offset = 8 * transform.GetScale().y_;
	collider = new Collider(x, y, w, h, x_offset, y_offset);
}

Eagle::Eagle()
{
	m_velocity = Helium::Vector2(-75.0f, 0.f);
	m_minRange = 1500.f;
	m_maxRange = 6000.f;

	animation = new Animation(100, "eagle", "Resources/EagleAnimation.txt");

	transform.SetPosition(Randomize(), Player::defaultPos - 250);
	transform.SetScale(3.0f, 3.0f);

	int x = transform.GetPosition().x_;
	int y = transform.GetPosition().y_;
	int w = 33 * transform.GetScale().x_;
	int h = 28 * transform.GetScale().y_;
	int x_offset = -1 * transform.GetScale().x_;
	int y_offset = 10 * transform.GetScale().y_;
	collider = new Collider(x, y, w, h, x_offset, y_offset);
}
