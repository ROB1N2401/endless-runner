#pragma once
#include <map>
#include <string>
#include "SDL_mixer.h"

#define FREQ 44100
#define CHUNK_SIZE 2048

class AudioManager
{
public:
	static AudioManager* Instance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new AudioManager(); };

	std::map<std::string, Mix_Chunk*> SoundMap;
	std::map<std::string, Mix_Music*> MusicMap;

	bool LoadMusic(const std::string& id_in, const std::string& musicFileName_in);
	void PlayMusic(const std::string& id_in);
	
	bool LoadSound(const std::string& id_in, const std::string& soundFileName_in);
	void PlaySound(const std::string& id_in);

	void SetVolume(int volume_in);
	void Clear();

private:
	AudioManager();

	int m_volume;
	static AudioManager* s_Instance;
};