#pragma once

class Timer
{
private:
	bool isHardware;	//���� �ϵ���� ��������
	float timeScale;	//FPS ��
	float timeElapsed;	//Tick Count

	__int64 curTime;			//����ð�
	__int64 lastTime;			//������ �ð�
	__int64 periodFrequency;	//��

	unsigned long frameRate;
	unsigned long FPSframeCount;

	float FPSTimeElapsed;
	float worldTime;

public:
	void Init();
	void Tick(float lockFPS = 0.0f);	

	inline unsigned long GetFrameRate() const { return frameRate; }
	inline float GetElapsedTime() const { return timeElapsed; }
	inline float GetWorldTime() const { return worldTime; }
};