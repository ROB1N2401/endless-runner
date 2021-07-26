#include "Parallax.h"

Parallax::Parallax(float baseSpeed_in) : m_baseSpeed(baseSpeed_in), m_layer_1(0.1f, "layer_1", "Resources/ParallaxLayerData01.txt"),
m_layer_2(0.25f, "layer_2", "Resources/ParallaxLayerData.txt"),
m_layer_3(0.5f, "layer_3", "Resources/ParallaxLayerData.txt"),
m_layer_4(0.75f, "layer_4", "Resources/ParallaxLayerData.txt"),
m_layer_5(1.0f, "layer_5", "Resources/ParallaxLayerData.txt")
{

}

Parallax::~Parallax()
{
}

void Parallax::Update(const float dt)
{
	for (int i = 0; i < m_layersAmount; i++)
		m_layers[i]->Update(m_baseSpeed * dt);
}

void Parallax::Render()
{
	for (int i = 0; i < m_layersAmount; i++)
		m_layers[i]->Render();
}
