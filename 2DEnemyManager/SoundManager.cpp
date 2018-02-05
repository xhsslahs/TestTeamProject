#include "stdafx.h"

void SoundManager::Init()
{
	System_Create(&_system);
	_system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, NULL);

	_sound = new Sound*[TOTALSOUNDBUFFER];
	_channel = new Channel*[TOTALSOUNDBUFFER];

	ZeroMemory(_sound, sizeof(_sound));
	ZeroMemory(_channel, sizeof(_channel));
}

void SoundManager::AddSound(string keyName, string soundName, bool bgm, bool loop)
{
	if (loop)
	{
		if (bgm)
		{
			_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL,
				NULL, &_sound[totalSound.size()]);
		}
		else
		{
			_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL,
				NULL, &_sound[totalSound.size()]);
		}
	}
	else
	{
		if (bgm)
		{
			_system->createStream(soundName.c_str(), FMOD_DEFAULT,
				NULL, &_sound[totalSound.size()]);
		}
		else
		{
			_system->createSound(soundName.c_str(), FMOD_DEFAULT,
				NULL, &_sound[totalSound.size()]);
		}
	}

	totalSound.insert(make_pair(keyName, &_sound[totalSound.size()]));
}

void SoundManager::Play(string keyName, float volue)
{
	map<string, Sound**>::iterator it;
	
	int count = 0;

	for (it = totalSound.begin(); it != totalSound.end(); it++)
	{
		if (keyName == it->first)
		{
			_system->playSound(FMOD_CHANNEL_FREE, _sound[count],
				false, &_channel[count]);
			_channel[count]->setVolume(volue);
			break;
		}
		count++;
	}
	
}

void SoundManager::Stop(string keyName)
{
	map<string, Sound**>::iterator it;

	int count = 0;

	for (it = totalSound.begin(); it != totalSound.end(); it++)
	{
		if (keyName == it->first)
		{
			_channel[count]->stop();
			break;
		}
		count++;
	}
}

void SoundManager::Pause(string keyName)
{
	map<string, Sound**>::iterator it;

	int count = 0;

	for (it = totalSound.begin(); it != totalSound.end(); it++)
	{
		if (keyName == it->first)
		{
			_channel[count]->setPaused(true);
			break;
		}
		count++;
	}
}

void SoundManager::Resume(string keyName)
{
	map<string, Sound**>::iterator it;

	int count = 0;

	for (it = totalSound.begin(); it != totalSound.end(); it++)
	{
		if (keyName == it->first)
		{
			_channel[count]->setPaused(false);
			break;
		}
		count++;
	}
}

bool SoundManager::isPlaySound(string keyName)
{
	bool isPlay;

	map<string, Sound**>::iterator it;

	int count = 0;

	for (it = totalSound.begin(); it != totalSound.end(); it++)
	{
		if (keyName == it->first)
		{
			_channel[count]->isPlaying(&isPlay);
			break;
		}
		count++;
	}

	return isPlay;
}

bool SoundManager::isPauseSound(string keyName)
{
	bool isPlay;

	map<string, Sound**>::iterator it;

	int count = 0;

	for (it = totalSound.begin(); it != totalSound.end(); it++)
	{
		if (keyName == it->first)
		{
			_channel[count]->getPaused(&isPlay);
			break;
		}
		count++;
	}

	return isPlay;
}
