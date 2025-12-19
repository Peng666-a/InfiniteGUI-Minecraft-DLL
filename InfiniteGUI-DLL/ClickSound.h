#pragma once
#include "AudioManager.h"

class ClickSound
{
public:

	static ClickSound& Instance()
	{
		static ClickSound instance;
		return instance;
	}

	void Init(bool isEnabled, float volume)
	{
		this->isEnabled = isEnabled;
		this->volume = volume;
	}
	void PlayClickSound()
	{
		if (isEnabled) AudioManager::Instance().playSound("pop.wav", volume);
	}
	void SetEnabled(bool isEnabled) { this->isEnabled = isEnabled; }
	void SetVolume(float volume) { this->volume = volume; }
private:
	bool isEnabled = true;
	float volume = 1.0f;
};
