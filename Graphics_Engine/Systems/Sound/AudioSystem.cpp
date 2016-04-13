//	File name:		AudioSystem.cpp
//	Project name:	Shot In The Dark
//	Author(s):		Connor Drose
//	
//	All content © 2014-2015 DigiPen (USA) Corporation, all rights reserved.


//#include "../../Engine.hpp"
#include "AudioSystem.hpp"
//#include <stdio.h>
#include <iostream>
//#include "Audio.h"
//#include "fmod_errors.h"
#include "FMOD/fmod_errors.h"


#include <assert.h>
#include <vector>
//#include <stdio.h>
#include <cstdio>


const std::string AudioSystem::assetFolder("Audio/");

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
	//: System(sys_AudioSystem, "Audio System"),
	system(0), _extraDriverData(0), _lowLevelSystem(0),
	masterBank(0), stringsBank(0), musicBank(0), SFXBank(0), VOXBank(0),
	musicInstance(0), musicPlaying(false), muteMusic(false),
	muteAll(false), targetParam(0), currentParam(0)
{ }

void AudioSystem::Init()
{

	//REGISTER_COMPONENT(Audio);

	// Create the FMOD systems
	FMOD_CHECK(FMOD::Studio::System::create(&system));
	FMOD_CHECK(system->getLowLevelSystem(&_lowLevelSystem));
	// Set the system to 5.1 sound
	FMOD_CHECK(_lowLevelSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_5POINT1, 0));
	// Initialize the system
	FMOD_CHECK(system->initialize(32, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, _extraDriverData));

	LoadAllBanks();
	LoadAllSFX();
	LoadAllVOX();
	LoadAllMusic();

	// load data into memory
	for (auto f : eventDescriptions)
		FMOD_CHECK(f.second->loadSampleData());

}

void AudioSystem::ToggleMuteAll()
{
	muteAll = !muteAll;


	musicBus->setMute(muteAll || muteMusic);
	sfxBus->setMute(muteAll);
	voxBus->setMute(muteAll);
}

void AudioSystem::ToggleMuteMusic()
{
	muteMusic = !muteMusic;
	musicBus->setMute(muteAll || muteMusic);
}


void AudioSystem::NarrateSound(std::string name)
{
	narratorQueue.push("dialog/" + name);
}

void AudioSystem::PlaySound(std::string name)
{

	FMOD::Studio::EventInstance* eventInstance = NULL;

	// See if we have the sound
	if (eventDescriptions.find(name) == eventDescriptions.end())
	{
		std::cout << "Error playing sound " << std::endl; //name << "!!!\n";
		return;
	}

	FMOD_CHECK(eventDescriptions[name]->createInstance(&eventInstance));

	FMOD_CHECK(eventInstance->start());
	// Release will clean up the instance when it completes
	FMOD_CHECK(eventInstance->release());
}

void AudioSystem::PlaySound(std::string name, FMOD::Studio::EventInstance *&eventInstance)
{

	// See if we have the sound
	if (eventDescriptions.find(name) == eventDescriptions.end())
	{
		std::cout << "Error playing sound " << std::endl;  //<< name << "!!!\n";
		return;
	}

	assert(eventInstance == 0);

	FMOD_CHECK(eventDescriptions[name]->createInstance(&eventInstance));

	FMOD_CHECK(eventInstance->start());
}

void AudioSystem::StopSound(FMOD::Studio::EventInstance *&eventInstance)
{
	assert(eventInstance != 0);

	FMOD_CHECK(eventInstance->stop(FMOD_STUDIO_STOP_IMMEDIATE));

	FMOD_CHECK(eventInstance->release());

	eventInstance = 0;
}

void AudioSystem::PlayMusic(std::string music)
{
	// Stop the existing music
	if (musicInstance)
		StopMusic(true);

	// See if we have the music
	if (musicDescriptions.find(music) == musicDescriptions.end())
	{
		std::cout << "Error playing music " << std::endl;  //<< music << "!!!\n";
		return;
	}

	// Create the instance
	FMOD_CHECK(musicDescriptions[music]->createInstance(&musicInstance));

	// start it
	FMOD_CHECK(musicInstance->start());
}

void AudioSystem::StopMusic( bool fadeOut)
{
	if (fadeOut == true)
		musicInstance->stop(FMOD_STUDIO_STOP_ALLOWFADEOUT);
	else
		musicInstance->stop(FMOD_STUDIO_STOP_IMMEDIATE);

	musicInstance = 0;
}

// Check objects and play sounds depending on active flags on the objects
void AudioSystem::Update(float dt)
{
	FMOD_CHECK(this->system->update()); // obligatory call to update Fmod


	//// loop through objects
	//for (auto i = _entities.begin(); i != _entities.end(); i++)
	//{
	//	// play sound if audio component says so
	//	//Audio *aud = (*i)->GET_COMPONENT(Audio);

	//	bool paused;
	//	FMOD_STUDIO_PLAYBACK_STATE state;

	//	switch (aud->type)
	//	{
	//	case Audio::AT_NARRATE:
	//		NarrateSound(aud->audioMap[aud->currentEvent]);
	//		aud->type = Audio::AT_NONE;
	//		break;

	//	case Audio::AT_PLAY:
	//		// Do we have the sound?
	//		if (aud->audioMap.find(aud->currentEvent) == aud->audioMap.end())
	//		{
	//			aud->type = Audio::AT_NONE;
	//			break;
	//		}

	//		// Check clipping
	//		if ((*i)->HasComponent(EC_Drawable))
	//		{
	//			aud->eventInstance->getPaused(&paused);
	//			if ((*i)->GET(Drawable)->clipped != paused)
	//				aud->eventInstance->setPaused((*i)->GET(Drawable)->clipped);
	//		}
	//		
	//		// Play the sound if it isn't already
	//		if (aud->eventInstance == 0)
	//			PlaySound(aud->audioMap[aud->currentEvent], aud->eventInstance);
	//		else
	//		{

	//		// Stop the sound if it's done
	//			FMOD_CHECK(aud->eventInstance->getPlaybackState(&state));
	//			if (state == FMOD_STUDIO_PLAYBACK_STOPPED)
	//				aud->type = Audio::AT_NONE;
	//		}

	//		break;

	//	default:
	//	case Audio::AT_NONE:
	//		// If we we're playing something, stop
	//		if (aud->eventInstance != 0)
	//			StopSound(aud->eventInstance);

	//		break;
	//	}
	//}

	//// Update our narrator
	//UpdateNarrator();

	//// Update the current music's parameter
	//if (musicInstance)
	//{
	//	const float lerp_speed = 0.5f;
	//	currentParam = currentParam + (targetParam - currentParam) * dt * lerp_speed;
	//	musicInstance->setParameterValue("Level", currentParam);
	//}
	
}

void AudioSystem::Shutdown()
{
	FMOD_CHECK(SFXBank->unload());
	FMOD_CHECK(VOXBank->unload());
	FMOD_CHECK(musicBank->unload());
	FMOD_CHECK(stringsBank->unload());
	FMOD_CHECK(masterBank->unload());
	FMOD_CHECK(system->release());
}

bool AudioSystem::IsMusicPlaying(void)
{
	return musicPlaying;
}

void AudioSystem::LoadBank(std::string bankName, FMOD::Studio::Bank *&bank)
{
	FMOD_CHECK(
		system->loadBankFile((assetFolder + bankName).c_str(),
		FMOD_STUDIO_LOAD_BANK_NORMAL,
		&bank));
}

//void AudioSystem::SendMsg(Entity *, Entity*, message msg)
//{
//  
//  if (msg == MSG_LoseFocus)
//  {
//	  if (!muteAll || !muteMusic)
//			ToggleMuteAll();
//  }
//
//  if (msg == MSG_GainFocus)
//  {
//	  if (!muteAll || !muteMusic)
//		  ToggleMuteAll();
//
//  }
//}

void AudioSystem::LoadAllBanks()
{
	// LOAD THE SOUND EFFECTS INTO BANK POINTERS
	LoadBank("Master Bank.bank", masterBank);
	LoadBank("Master Bank.strings.bank", stringsBank);
	LoadBank("MUS.bank", musicBank);
	LoadBank("SFX.bank", SFXBank);
	LoadBank("VOX.bank", VOXBank);
}

void AudioSystem::LoadAllMusic()
{
	FMOD_CHECK(system->getEvent("event:/music/levelMusic", &musicDescriptions["Level"]));
	FMOD_CHECK(system->getEvent("event:/music/menuMusic", &musicDescriptions["Menu"]));

	//FMOD_CHECK(musicDescription->createInstance(&musicInstance));

	// musicInstance->setParameterValue("level", 0.0f);

	// Load the bus
	system->getBus("bus:/MUS", &musicBus);
}

void AudioSystem::LoadEvent(std::string location)
{
	// Truncate the name
	std::string name = location.substr(location.find_first_of('/') + 1);


	FMOD_CHECK(system->getEvent(
		location.c_str(), 
		&eventDescriptions[name]
	));


}

void AudioSystem::SetTargetLevelParam(float target)
{
	targetParam = target;
}

void AudioSystem::LoadAllSFX()
{
	//LoadEvent("event:/bacon/death");
	//LoadEvent("event:/bacon/idle");
	//LoadEvent("event:/muffin/death");
	//LoadEvent("event:/muffin/pain");
	//LoadEvent("event:/muffin/attack");
	//LoadEvent("event:/chest/open");
	//LoadEvent("event:/powerup/collect");
	//LoadEvent("event:/menu/select");
	//LoadEvent("event:/menu/move");
	//LoadEvent("event:/strawberry/death");
	//LoadEvent("event:/strawberry/pain");
	//LoadEvent("event:/bigStrawberry/death");
	//LoadEvent("event:/bigStrawberry/pain");
	//LoadEvent("event:/axeHit");
	//LoadEvent("event:/axeMiss");
	//LoadEvent("event:/genericHit");
	//LoadEvent("event:/magicCastTeal");
	//LoadEvent("event:/magicCastOrange");
	//LoadEvent("event:/magicCastPink");
	//LoadEvent("event:/magicCastPurple");
	//LoadEvent("event:/magicHit");
	//LoadEvent("event:/staffHit");
	//LoadEvent("event:/staffMiss");
	//LoadEvent("event:/stoneHit");
	//LoadEvent("event:/stoneShatter");
	//LoadEvent("event:/torchExtinguish");
	//LoadEvent("event:/torchIgnite");
	//LoadEvent("event:/wizardPainOrange");
	//LoadEvent("event:/wizardPainPink");
	//LoadEvent("event:/wizardPainPurple");
	//LoadEvent("event:/wizardPainTeal");


	//// Load the bus
	//system->getBus("bus:/SFX", &sfxBus);
}

void AudioSystem::LoadAllVOX()
{
	//LoadEvent("event:/dialog/beginGame");
	//LoadEvent("event:/dialog/endDefeat");
	//LoadEvent("event:/dialog/endVictory");
	//LoadEvent("event:/dialog/fight");
	//LoadEvent("event:/dialog/one");
	//LoadEvent("event:/dialog/orangeDie");
	//LoadEvent("event:/dialog/orangeJoin");
	//LoadEvent("event:/dialog/orangeLeave");
	//LoadEvent("event:/dialog/orangeWin");
	//LoadEvent("event:/dialog/pinkDie");
	//LoadEvent("event:/dialog/pinkJoin");
	//LoadEvent("event:/dialog/pinkLeave");
	//LoadEvent("event:/dialog/pinkWin");
	//LoadEvent("event:/dialog/purpleDie");
	//LoadEvent("event:/dialog/purpleJoin");
	//LoadEvent("event:/dialog/purpleLeave");
	//LoadEvent("event:/dialog/purpleWin");
	//LoadEvent("event:/dialog/pvpEnd");
	//LoadEvent("event:/dialog/pvpStart");
	//LoadEvent("event:/dialog/tealDie");
	//LoadEvent("event:/dialog/tealJoin");
	//LoadEvent("event:/dialog/tealLeave");
	//LoadEvent("event:/dialog/tealWin");
	//LoadEvent("event:/dialog/two");
	//LoadEvent("event:/dialog/three");

	//narratorInstance = 0;

	//// Load the bus
	//system->getBus("bus:/VOX", &voxBus);
}

void AudioSystem::UpdateNarrator()
{
	if (narratorInstance != NULL)
	{
		FMOD_STUDIO_PLAYBACK_STATE state;

		FMOD_CHECK(narratorInstance->getPlaybackState(&state));

		if (state == FMOD_STUDIO_PLAYBACK_STOPPED)
		{
			narratorInstance->release();
			narratorInstance = NULL;
		}
	}

	if (narratorInstance == NULL && !narratorQueue.empty())
	{
		PlaySound(narratorQueue.front(), narratorInstance);
		narratorQueue.pop();
	}
}

