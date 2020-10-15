#pragma once
#include <iostream>
#include <SDL_mixer.h>

class SoundManager
{
public:
	SoundManager();
	~SoundManager();
	void LoadMusic(int channel, Mix_Chunk* sound, std::string path, int loop);
};