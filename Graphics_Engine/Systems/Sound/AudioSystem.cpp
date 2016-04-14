//	File name:		AudioSystem.cpp
//	Project name:	Shot In The Dark
//	Author(s):		Connor Drose
//	
//	All content © 2014-2015 DigiPen (USA) Corporation, all rights reserved.

#pragma once
#include "AudioSystem.hpp"
#include <iostream>
#include "FMOD/fmod_errors.h"
#include <assert.h>
#include <vector>
#include <cstdio>


//const std::string AudioSystem::assetFolder("Audio/");
static std::vector<AudioTrack> mAudio;

// FMOD error checking
#define FMOD_CHECK(_result) FMOD_CHECK_fn(_result, __FILE__, __LINE__)
void FMOD_CHECK_fn(FMOD_RESULT result, const char *file, int line)
{
	if (result != FMOD_OK)
	{
		printf("\"%s  (%d): FMOD error %d - %s\n", file, line, result, FMOD_ErrorString(result));
		// abort();
	}
}

AudioSystem::AudioSystem() :
	system(0), 
	_extraDriverData(0), 
	_lowLevelSystem(0),
	musicPlaying(false), 
	muteMusic(false),
	muteAll(false) 
{ }

void AudioSystem::Init()
{

	// Create the FMOD systems
	FMOD_CHECK(FMOD::Studio::System::create(&system));
	FMOD_CHECK(system->getLowLevelSystem(&_lowLevelSystem));
	// Set the system to 5.1 sound
	FMOD_CHECK(_lowLevelSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_5POINT1, 0));
	// Initialize the system
	FMOD_CHECK(system->initialize(32, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, _extraDriverData));

	exinfo.numchannels = 4;
	exinfo.defaultfrequency = 0;
	exinfo.format = FMOD_SOUND_FORMAT_NONE;

	FMOD_CHECK(_lowLevelSystem->createStream("", FMOD_OPENUSER, &exinfo, &track));

	for (int i = 0; i < 4; ++i) {
		mAudio.push_back(AudioTrack());	
		_lowLevelSystem->createDSPByType(FMOD_DSP_TYPE_OSCILLATOR, &mAudio[i].mDSP);
		_lowLevelSystem->playDSP(mAudio[i].mDSP, 0, true, &mAudio[i].mChannel);
		FMOD_CHECK(mAudio[i].mChannel->setVolume(0.3f));
		mAudio[i].IsPlaying = false;		
	}
	//FMOD_CHECK(mAudio.soprano->setPaused(true));
}

void AudioSystem::ToggleMuteAll()
{
	muteAll = !muteAll;
}

void AudioSystem::ToggleMuteMusic()
{
	muteMusic = !muteMusic;
}


// Check objects and play sounds depending on active flags on the objects
void AudioSystem::Update(double dt)
{
	FMOD_CHECK(this->system->update()); // obligatory call to update Fmod
	
	for (int i = 0; i < 4; ++i) {
		
		if (mAudio[i].IsPlaying) {
			FMOD_CHECK(mAudio[i].mChannel->setPaused(false));
		}
		else {
			FMOD_CHECK(mAudio[i].mChannel->setPaused(true));
		}
	}	
}

void AudioSystem::Free()
{
	FMOD_CHECK(system->release());
}

void AudioSystem::playFrequency(int ID, float frequency) {
	mAudio[ID].mDSP->setParameterFloat(FMOD_DSP_OSCILLATOR_RATE, frequency);
	mAudio[ID].IsPlaying = true;
}

void AudioSystem::pauseChannel(int ID) {
	mAudio[ID].IsPlaying = false;
}

void AudioSystem::unPauseChannel(int ID) {
	mAudio[ID].IsPlaying = true;
}



