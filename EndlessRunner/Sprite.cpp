#include "Sprite.h"
#include "TextureManager.h"
#include <fstream>
#include <sstream>

Sprite::Sprite()
{
	x = 0; y = 0; w = 0; h = 0;
	texture = nullptr;
	source = SDL_Rect{ x, y, w, h };
}

Sprite::Sprite(const std::string& id_in, const std::string& spritesheetName_in)
{
	std::ifstream stream;
	stream.open(spritesheetName_in);

	std::string fileName;
	std::getline(stream, fileName);

	texture = TextureManager::Instance()->GetTexture(id_in);

	std::string line;
	std::getline(stream, line);
	std::stringstream ss(line);
	std::vector<std::string> words;
	std::string word;
	while (ss >> word) words.push_back(word);
	x = std::stoi(words[0]);
	y = std::stoi(words[1]);
	w = std::stoi(words[2]);
	h = std::stoi(words[3]);
	source = SDL_Rect{ x, y, w, h };
}

void Sprite::SetTexture(const std::string& id_in)
{
	texture = TextureManager::Instance()->GetTexture(id_in);
}

void Sprite::SetSource(int w_in, int h_in)
{
	source = SDL_Rect{ x, y, w_in, h_in };
}

void Sprite::SetSource(int x_in, int y_in, int w_in, int h_in)
{
	source = SDL_Rect{ x_in, y_in, w_in, h_in };
}

