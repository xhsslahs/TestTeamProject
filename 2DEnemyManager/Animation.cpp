#include "stdafx.h"

Animation::Animation()
{
	frameNum = 0;
	frameWidth = 0;
	frameHeight = 0;
	isLoop = false;
	frameUpdateSec = 0;
	elapseSec = 0;
	nowPlayIndex = 0;
	isPlay = false;
}

void Animation::Init(int totalW, int totalH, int frameW, int frameH)
{
	frameWidth = frameW;
	int frameNumWidth = totalW / frameWidth;
	frameHeight = frameH;
	int frameNumHeight = totalH / frameHeight;

	frameNum = frameNumWidth * frameNumHeight;

	for (int i = 0; i < frameNumHeight; i++)
	{
		for (int j = 0; j < frameNumWidth; j++)
		{
			POINT framePos;
			framePos.x = j * frameWidth;
			framePos.y = i * frameHeight;

			frameList.push_back(framePos);
		}
	}
}

void Animation::SetDefPlayFrame(bool reverse, bool loop)
{
	isLoop = loop;
	
	playList.clear();

	if (reverse)
	{
		//정재생
		for (int i = 0; i < frameNum; i++)
		{
			playList.push_back(i);
		}
		//역재생
		for (int i = frameNum - 1; i >= 0; i--)
		{
			playList.push_back(i);
		}
	}
	else
	{
		for (int i = 0; i < frameNum; i++)
		{
			playList.push_back(i);
		}
	}
}

void Animation::SetPlayFrame(int * playArr, int arrLen, bool loop)
{
	isLoop = loop;

	playList.clear();

	for (int i = 0; i < arrLen; i++)
	{
		playList.push_back(playArr[i]);
	}
}

void Animation::SetPlayFrame(int start, int end, bool loop)
{
	isLoop = loop;

	playList.clear();

	if (start > end)
	{
		for (int i = start; i >= end; i--)
		{
			playList.push_back(i);
		}
	}
	else
	{
		for (int i = start ; i <= end; i++)
		{
			playList.push_back(i);
		}
	}
}

void Animation::SetFPS(int framePerSec)
{
	frameUpdateSec = 1.0f / framePerSec;
}

void Animation::FrameUpdate(float elapsedTime)
{
	if (isPlay)
	{
		elapseSec += elapsedTime;

		if (elapseSec >= frameUpdateSec)
		{
			elapseSec -= frameUpdateSec;
			nowPlayIndex++;

			if (nowPlayIndex == playList.size())
			{
				if (isLoop)
					nowPlayIndex = 0;
				else
				{
					nowPlayIndex--;
					isPlay = false;
				}
			}
		}
	}
}
