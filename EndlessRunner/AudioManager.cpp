#include "AudioManager.h"
#include "SDL.h"

AudioManager* AudioManager::m_Instance = nullptr;

AudioManager::AudioManager() 
{
	if (Mix_OpenAudio(FREQ, MIX_DEFAULT_FORMAT, 2, CHUNK_SIZE) < 0)
		SDL_Log("Failed to initialize AudioManager: %s", Mix_GetError());
}

bool AudioManager::LoadMusic(const std::string& id_in, const std::string& musicFileName_in)
{
	if (MusicMap.count(id_in) > 0)
		return true;

	Mix_Music* music = Mix_LoadMUS(musicFileName_in.c_str());
	if (music == nullptr)
	{
		SDL_Log("Failed to load music: %s, %s", musicFileName_in.c_str(), Mix_GetError());
		return false;
	}

	MusicMap[id_in] = music;
	return true;
}

bool AudioManager::LoadSound(const std::string& id_in, const std::string& soundFileName_in)
{
	if (SoundMap.count(id_in) > 0)
		return true;

	Mix_Chunk* sound = Mix_LoadWAV(soundFileName_in.c_str());
	if (sound == nullptr)
	{
		SDL_Log("Failed to load sound: %s, %s", soundFileName_in.c_str(), Mix_GetError());
		return false;
	}

	Mix_VolumeChunk(sound, m_volume);
	SoundMap[id_in] = sound;
	return true;
}

void AudioManager::PlayMusic(const std::string& id_in)
{
	if(Mix_PlayMusic(MusicMap[id_in], -1) == -1)
		SDL_Log("Failed to playback music: %s, %s", id_in.c_str(), Mix_GetError());
}

Mix_Music* AudioManager::GetMusic(const std::string& id_in)
{
	if (!(MusicMap.count(id_in) > 0))
	{
		SDL_Log("Failed to find music associated with the next id: %s, %s", id_in.c_str(), Mix_GetError());
		return nullptr;
	}
	else
		return MusicMap.find(id_in)->second;
}

void AudioManager::PlaySound(const std::string& id_in)
{
	if (Mix_PlayChannel(-1, SoundMap[id_in], 0) == -1)
		SDL_Log("Failed to playback sound: %s, %s", id_in.c_str(), Mix_GetError());
}

Mix_Chunk* AudioManager::GetSound(const std::string& id_in)
{
	if (!(SoundMap.count(id_in) > 0))
	{
		SDL_Log("Failed to find music associated with the next id: %s, %s", id_in.c_str(), Mix_GetError());
		return nullptr;
	}
	else
		return SoundMap.find(id_in)->second;
}

void AudioManager::SetVolume(int volume_in) 
{ 
	Mix_VolumeMusic(volume_in);
	m_volume = volume_in;
}

void AudioManager::Clear()
{
	std::map<std::string, Mix_Music*>::iterator it1;
	for (it1 = MusicMap.begin(); it1 != MusicMap.end(); it1++)
		Mix_FreeMusic(it1->second);

	std::map<std::string, Mix_Chunk*>::iterator it2;
	for (it2 = SoundMap.begin(); it2 != SoundMap.end(); it2++)
		Mix_FreeChunk(it2->second);

	MusicMap.clear();
	SoundMap.clear();
}
