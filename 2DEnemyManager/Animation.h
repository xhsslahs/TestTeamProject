#pragma once
#include <vector>

using namespace std;

class Animation
{
private:
	vector<POINT> frameList;
	vector<int> playList;

	int frameNum;

	int frameWidth;
	int frameHeight;

	bool isLoop;

	float frameUpdateSec;
	float elapseSec;

	DWORD nowPlayIndex;
	bool isPlay;

public:
	Animation();

	void Init(int totalW, int totalH, int frameW, int frameH);

	void SetDefPlayFrame(bool reverse = false, bool loop = false);
	void SetPlayFrame(int* playArr, int arrLen, bool loop = false);
	void SetPlayFrame(int start, int end, bool loop = false);

	void SetFPS(int framePerSec);
	void FrameUpdate(float elapsedTime);

	void Start()
	{
		isPlay = true;
		nowPlayIndex = 0;
	}

	void Stop()
	{
		isPlay = false;
		nowPlayIndex = 0;
	}

	void Resume()
	{
		isPlay = true;
	}

	void Pause()
	{
		isPlay = false;
	}

	inline bool GetIsPlay() { return isPlay; }
	inline int GetFrameWidth() { return frameWidth; }
	inline int GetFrameHeight() { return frameHeight; }
	inline POINT GetFramePos() { return frameList[playList[nowPlayIndex]]; }
};