#pragma once

#include <map>
#include <string>
#include "SDL_mixer.h"

#define FREQ 44100
#define CHUNK_SIZE 2048

class AudioManager
{
public:
	static AudioManager* Instance() { return m_Instance = (m_Instance != nullptr) ? m_Instance : new AudioManager(); };

	bool LoadMusic(const std::string& id_in, const std::string& musicFileName_in);
	void PlayMusic(const std::string& id_in);
	Mix_Music* GetMusic(const std::string& id_in);
	
	bool LoadSound(const std::string& id_in, const std::string& soundFileName_in);
	void PlaySound(const std::string& id_in);
	Mix_Chunk* GetSound(const std::string& id_in);

	void Clear();

	std::map<std::string, Mix_Chunk*> SoundMap;
	std::map<std::string, Mix_Music*> MusicMap;

private:
	AudioManager();
	static AudioManager* m_Instance;
};