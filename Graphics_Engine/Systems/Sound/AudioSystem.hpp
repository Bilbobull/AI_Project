#pragma once

#include "../Systems.h"
//#include "AudioTypes.h"
//#include "../../Components/Audio.h"

#include "FMOD/fmod_studio.hpp"
#include "FMOD/fmod.hpp"
#include <stdio.h>
#include <queue>
#include <unordered_map>


class AudioSystem : public System
{
public:
	AudioSystem();

	void Init(void);
	void Update(float dt);
	void Shutdown(void);

	void PlaySound(std::string name);
	void NarrateSound(std::string name);

	void PlayMusic(std::string music);
	void StopMusic(bool fadeOut);
	void SetTargetLevelParam(float target);

	bool IsMusicPlaying(void);

	void ToggleMuteMusic();
	void ToggleMuteAll();

    //void SendMsg(Entity *, Entity*, message);
private:
	void LoadBank(std::string bankName, FMOD::Studio::Bank *&bank);
	void LoadEvent(std::string location);

	void PlaySound(std::string name, FMOD::Studio::EventInstance*& instance);
	void StopSound(FMOD::Studio::EventInstance*& instance);


	void LoadAllBanks();
	void LoadAllMusic();
	void LoadAllSFX();
	void LoadAllVOX();

	void UpdateNarrator();

	// Flags for music/audio settings
	bool musicPlaying;
	bool muteMusic;
	bool muteAll;

	// The location of all audio assets
	static const std::string assetFolder;

	FMOD::Studio::EventInstance *narratorInstance;
	std::queue<std::string> narratorQueue;

	// Fmod system stuff
	FMOD::Studio::System* system;
	void *_extraDriverData;
	FMOD::System* _lowLevelSystem;

	// audio file pointers
	FMOD::Studio::Bank *masterBank, *stringsBank, *musicBank, *SFXBank, *VOXBank;
	FMOD::Studio::Bus *sfxBus;
	FMOD::Studio::Bus *voxBus;

	// all EventDescriptions for sound effects
	std::unordered_map<std::string, FMOD::Studio::EventDescription*> eventDescriptions;

	// music event descriptions
	std::unordered_map<std::string, FMOD::Studio::EventDescription*> musicDescriptions;

	// music event instances
	FMOD::Studio::EventInstance *musicInstance;
	FMOD::Studio::Bus *musicBus;
	float targetParam, currentParam; // For current level tracks
};
