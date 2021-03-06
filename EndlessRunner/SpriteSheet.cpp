#include "SpriteSheet.h"
#include <fstream>
#include <sstream>

SpriteSheet ReadSpritesheet(const std::string& texture_id_in, const std::string& spritesheetName_in)
{
	std::ifstream stream_;
	stream_.open(spritesheetName_in);
	SpriteSheet spritesheet_;
	std::string line_;
	while (std::getline(stream_, line_))
	{
		std::stringstream ss(line_);
		std::vector<std::string> words;
		std::string word;
		while (ss >> word) words.push_back(word);
		if (words.size() != 4) continue;
		Sprite sprite = Sprite(texture_id_in);
		sprite.SetSource(std::stoi(words[0]), std::stoi(words[1]), std::stoi(words[2]), std::stoi(words[3]));
		spritesheet_.sprites.push_back(sprite);
	}
	stream_.close();
	return spritesheet_;
}
