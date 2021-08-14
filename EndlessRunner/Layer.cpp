#include "Layer.h"
#include "Easing.h"
#include <ctime>
#include "RenderManager.h"

Layer::Layer(const float scrollRatio_in) : m_scrollRatio(scrollRatio_in), m_baseScale(2.0f)
{
	m_trueWidth = 0.f;
}

Layer::Layer(const float scrollRatio_in, const std::string& texture_id_in, const std::string& spriteDataFileName_in)
	: m_scrollRatio(scrollRatio_in), m_baseScale(2.2f)
{
	for (int i = 0; i < m_duplicatesAmount; i++)
	{
		m_images[i].sprite.SetTexture(texture_id_in);
		m_images[i].sprite.SetSource(spriteDataFileName_in);
		m_images[i].transform.pivotPoint = PivotPoint::CENTERED;
		m_images[i].transform.SetScale(m_baseScale);

		m_trueWidth = m_images[i].sprite.GetSource().w * m_images[i].transform.GetScale().x_;

		m_images[i].transform.SetPosition(-m_trueWidth / 2 + (m_trueWidth * i), 256.f);
	}
}

void Layer::Update(float baseSpeed_in)
{
	for (int i = 0; i < m_duplicatesAmount; i++)
	{
		m_images[i].transform.ChangePosition(-(baseSpeed_in * m_scrollRatio), 0.f);

		if (m_images[i].transform.GetPosition().x_ < -m_trueWidth / 2)
			m_images[i].transform.ChangePosition(m_trueWidth * m_duplicatesAmount, 0.f);
	}
}

void Layer::Reset()
{
	for (int i = 0; i < m_duplicatesAmount; i++)
	{
		m_images[i].transform.SetPosition(-m_trueWidth / 2 + (m_trueWidth * i), 256.f);
		m_images[i].transform.SetScale(m_baseScale);
		m_images[i].transform.SetRotation(0.0f);
	}
	
}

void Layer::Render()
{
	for (int i = 0; i < m_duplicatesAmount; i++)
		m_images[i].Render();
}

void Image::Render() { RenderManager::Instance()->Render(sprite, transform); }
