#pragma once
#include "Layer.h"
#include <string>

class Parallax
{
public:
	Parallax(float baseSpeed_in);
	~Parallax();

	void Update(const float dt);
	void Reset();
	void Render();

private:
	const float m_baseSpeed;
	static const unsigned int m_layersAmount = 5;
	Layer m_layer_1;
	Layer m_layer_2;
	Layer m_layer_3;
	Layer m_layer_4;
	Layer m_layer_5;
	Layer* m_layers[5] = {&m_layer_1, &m_layer_2, &m_layer_3, &m_layer_4, &m_layer_5, };
};