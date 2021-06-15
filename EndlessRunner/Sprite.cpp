#include "Sprite.h"
#include <fstream>
#include <sstream>

Sprite::Sprite()
{
	x, y, w, h = 0;
	imageFileName = "";
	source = SDL_Rect{ x, y, w, h };
}

Sprite::Sprite(std::string spritesheetName_in)
{
	std::ifstream stream;
	stream.open(spritesheetName_in);
	std::getline(stream, imageFileName);

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

void Sprite::SetImage(std::string spritesheetName_in)
{
	imageFileName = spritesheetName_in;
}

void Sprite::SetSource(int x_in, int y_in, int w_in, int h_in)
{
	source = SDL_Rect{ x_in, y_in, w_in, h_in };
}

