#pragma once

#include "Entity.h"

class Layer
{
public:
	Layer(const float scrollRatio_in);
	Layer(const float scrollRatio_in, const std::string& texture_id_in, const std::string& spriteDataFileName_in);

	void Update(float baseSpeed_in);
	void Render();

private:
	static const unsigned int m_duplicatesAmount = 3;
	const float m_scrollRatio;
	float m_trueWidth;
	Entity m_images[m_duplicatesAmount];
};