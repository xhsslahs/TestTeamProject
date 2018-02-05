#pragma once
#include "SingletonBase.h"

#include "inc/fmod.hpp"
#pragma comment(lib, "lib/fmodex_vc.lib")

using namespace FMOD;

#define SOUNDBUFFER 10
#define EXTRACHANNELBUFFER 5

#define TOTALSOUNDBUFFER SOUNDBUFFER + EXTRACHANNELBUFFER

class SoundManager : public SingletoneBase<SoundManager>
{
private:
	System* _system;
	Sound** _sound;
	Channel** _channel;

	map<string, Sound**> totalSound;

public:
	void Init();
	void AddSound(string keyName, string soundName, bool bgm, bool loop);

	void Play(string keyName, float volue = 1.0f);
	void Stop(string keyName);
	void Pause(string keyName);
	void Resume(string keyName);

	bool isPlaySound(string keyName);
	bool isPauseSound(string keyName);
};