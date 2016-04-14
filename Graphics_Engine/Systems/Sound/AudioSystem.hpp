#pragma once

#include "../Systems.h"
#include "FMOD/fmod_studio.hpp"
#include "FMOD/fmod.hpp"
#include <stdio.h>
#include <queue>
#include <unordered_map>
#include <vector>

struct AudioTrack
{
	FMOD::Channel* mChannel;
	FMOD::DSP* mDSP;
	float volume;
	bool IsPlaying;
};

enum Voice_ID {
	Bass,
	Tenor,
	Alto,
	Soprano,
	END_VOICES
};

class AudioSystem : public System
{
public:
	AudioSystem();

	void Init(void);
	void Update(double dt);
	void Free(void);

	static void playFrequency(int ID, float frequency);
	static void pauseChannel(int ID);
	static void unPauseChannel(int ID);
	static void setVolume(int ID, float volume);

	bool IsMusicPlaying(void);

	void ToggleMuteMusic();
	void ToggleMuteAll();

private:

	// Flags for music/audio settings
	bool musicPlaying;
	bool muteMusic;
	bool muteAll;

	// Fmod system stuff
	FMOD::Studio::System* system;
	void *_extraDriverData;
	FMOD::System* _lowLevelSystem;
	FMOD_CREATESOUNDEXINFO exinfo;
	FMOD::Sound* track;
	
};
