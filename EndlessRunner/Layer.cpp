#include "Layer.h"
#include "RenderManager.h"

Layer::Layer(const float scrollRatio_in) : m_scrollRatio(scrollRatio_in)
{
	m_trueWidth = 0.f;
}

Layer::Layer(const float scrollRatio_in, const std::string& texture_id_in, const std::string& spriteDataFileName_in) : m_scrollRatio(scrollRatio_in)
{
	for (int i = 0; i < m_duplicatesAmount; i++)
	{
		m_images[i].sprite.SetTexture(texture_id_in);
		m_images[i].sprite.SetSource(spriteDataFileName_in);
		m_images[i].transform.SetScale(2.f, 2.f);

		m_trueWidth = m_images[i].sprite.GetSource().w * m_images[i].transform.GetScale().x_;

		m_images[i].transform.SetPosition(-m_trueWidth + (m_trueWidth * i), 0.f);
	}
}

void Layer::Update(float baseSpeed_in)
{
	for (int i = 0; i < m_duplicatesAmount; i++)
	{
		m_images[i].transform.ChangePosition(-(baseSpeed_in * m_scrollRatio), 0.f);

		if (m_images[i].transform.GetPosition().x_ < -m_trueWidth)
			m_images[i].transform.ChangePosition(m_trueWidth * m_duplicatesAmount, 0.f);
	}
}

void Layer::Render()
{
	for (int i = 0; i < m_duplicatesAmount; i++)
		m_images[i].Render();
}

void Image::Render()
{
	RenderManager::Instance()->Render(sprite, transform);
}
