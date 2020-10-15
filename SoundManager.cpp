#include "SoundManager.h"

using namespace::std;

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
}

void SoundManager::LoadMusic(int channel, Mix_Chunk* sound, std::string path, int loop)
{
	sound = Mix_LoadWAV(path.c_str());

	if (sound == NULL)
	{
		cout << "Failed to load background music: " << Mix_GetError() << endl;
	}
	Mix_PlayChannel(channel, sound, loop);
}
