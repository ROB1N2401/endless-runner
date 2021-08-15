#include "Enemy.h"
#include "Player.h"
#include <time.h>

Enemy::Enemy() : m_velocity(0.f, 0.f), m_minRange(0), m_maxRange(0) {}

Enemy::~Enemy() 
{
	delete animation;
	delete collider;
}

const float Enemy::Randomize()
{
	srand(static_cast<unsigned int>(time(NULL)));
	const int addition = m_maxRange - m_minRange;
	int num = m_minRange + rand() % addition;

	return static_cast<const float>(num);
}

void Enemy::Update(const float dt)
{
	collider->SetPosition(static_cast<int>(this->transform.GetPosition().x_), static_cast<int>(this->transform.GetPosition().y_));
	animation->Update();

	Helium::Vector2 dpos = m_velocity * dt * 10.0f;
	transform.ChangePosition(dpos);

	if (transform.GetPosition().x_ < -100.f)
		transform.ChangePosition(Randomize(), 0.f);
}

Opossum::Opossum()
{
	m_velocity = Helium::Vector2(-50.0f, 0.f);
	m_minRange = 800;
	m_maxRange = 3200;

	animation = new Animation(150, "opossum", "Resources/OpossumAnimation.txt");

	transform.SetPosition(Randomize(), Player::defaultPos + 12);
	transform.SetScale(3.f);

	int x = static_cast<int>(transform.GetPosition().x_);
	int y = static_cast<int>(transform.GetPosition().y_);
	int w = static_cast<int>(28.f * transform.GetScale().x_);
	int h = static_cast<int>(18.f * transform.GetScale().y_);
	int x_offset = static_cast<int>(-1.f * transform.GetScale().x_);
	int y_offset = static_cast<int>(8.f * transform.GetScale().y_);
	collider = new Collider(x, y, w, h, x_offset, y_offset);
}

void Opossum::Reset() 
{ 
	transform.SetPosition(static_cast<const float>(Randomize()), Player::defaultPos + 12);
}

Eagle::Eagle()
{
	m_velocity = Helium::Vector2(-75.0f, 0.f);
	m_minRange = 1500;
	m_maxRange = 6000;

	animation = new Animation(100, "eagle", "Resources/EagleAnimation.txt");

	transform.SetPosition(Randomize(), Player::defaultPos - 250);
	transform.SetScale(3.0f, 3.0f);

	int x = static_cast<int>(transform.GetPosition().x_);
	int y = static_cast<int>(transform.GetPosition().y_);
	int w = static_cast<int>(33.f * transform.GetScale().x_);
	int h = static_cast<int>(28.f * transform.GetScale().y_);
	int x_offset = static_cast<int>(-1.f * transform.GetScale().x_);
	int y_offset = static_cast<int>(10.f * transform.GetScale().y_);
	collider = new Collider(x, y, w, h, x_offset, y_offset);
}

void Eagle::Reset() 
{ 
	transform.SetPosition(Randomize(), Player::defaultPos - 250); 
}
