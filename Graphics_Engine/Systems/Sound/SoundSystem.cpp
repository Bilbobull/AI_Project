/******************************************************************************/
/*! @@HEADER@@
  \copyright All content © 2013 DigiPen (USA) Corporation, all rights reserved.
  \file      SoundSystem.cpp
  \author    Eric Johnston
  \brief
    NO_BRIEF_SET
*/
/******************************************************************************/
#include "FMOD/fmod.hpp"
#include "FMOD/fmod_errors.h"
#include "FMOD/fmod_dsp.h"
#include "SoundSystem.h"
#include <fstream>
#include "SoundEffectComponent.h"
#include "SoundTrackComponent.h"


// helper function
void RepeatOn(FMOD::Channel* channel)
{
  channel->setMode(FMOD_LOOP_NORMAL);
  channel->setLoopCount(-1);
}

  // Helper to check if a filename is valid
bool FileExists(const char *filename)
{
  std::ifstream ifile(filename);
  return ifile.good();
}

  // Default all AudioTracks set as not playing
AudioTrack::AudioTrack() : IsPlaying(false)
{
  volume = 1.0f; // set default volume to 100%
}

SoundSystem::SoundSystem()
{
  //thisSystem = this;
  MuteAll = false;
  MuteAllTracks = false;
  PauseAllTracks = false;
  HasLostDevice = false;
}

SoundSystem::~SoundSystem()
{

}

  // Error checking
void SoundSystem::FMODErrorCheck(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        //Log::emit<LogLevelError>() << "FMOD error! (" << result << ") " << FMOD_ErrorString(result) << Log::endl;
        _ASSERT(!result);
    }
}

  // Called once when the system is created
void SoundSystem::Init()
{
  
  FMOD_RESULT result;
  unsigned int version;
  int numdrivers;
  char name[256];

    /*
  Create a System object and initialize.
  */
  result = FMOD::System_Create(&system);
  FMODErrorCheck(result);
  result = system->getVersion(&version);
  FMODErrorCheck(result);

  if (version < FMOD_VERSION)
  {
    //Log::emit<LogLevelError>() << "Error! You are using an old version of FMOD " << version <<". This program requires "<< FMOD_VERSION << Log::endl;
    return;
  }

  result = system->getNumDrivers(&numdrivers);
  FMODErrorCheck(result);

  if (numdrivers == 0)
  {
    result = system->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
    FMODErrorCheck(result);
  }
  else
  {
    result = system->getDriverCaps(0, &caps, 0, 0, &speakermode);
    FMODErrorCheck(result);
    /*
    Set the user selected speaker mode.
    */
    result = system->setSpeakerMode(speakermode);
    FMODErrorCheck(result);

    if (caps & FMOD_CAPS_HARDWARE_EMULATED)
    {
      /*
      The user has the 'Acceleration' slider set to off! This is really bad
      for latency! You might want to warn the user about this.
      */
      result = system->setDSPBufferSize(1024, 10);
      FMODErrorCheck(result);
    }

    result = system->getDriverInfo(0, name, 256, 0);
    FMODErrorCheck(result);

    if (strstr(name, "SigmaTel"))
    {
      /*
      Sigmatel sound devices crackle for some reason if the format is PCM 16bit.
      PCM floating point output seems to solve it.
      */
      result = system->setSoftwareFormat(48000, FMOD_SOUND_FORMAT_PCMFLOAT, 0,0, FMOD_DSP_RESAMPLER_LINEAR);
      FMODErrorCheck(result);
    }
  }

  FMODErrorCheck(system->setDSPBufferSize(512,2));

  result = system->init(100, FMOD_INIT_NORMAL, 0);

  if (result == FMOD_ERR_OUTPUT_CREATEBUFFER)
  {
    /*
    Ok, the speaker mode selected isn't supported by this soundcard. Switch it
    back to stereo...
    */
    result = system->setSpeakerMode(FMOD_SPEAKERMODE_STEREO);
    FMODErrorCheck(result);
    /*
    ... and re-init.
    */
    result = system->init(100, FMOD_INIT_NORMAL, 0);
    FMODErrorCheck(result);

    
    FMODErrorCheck(system->createChannelGroup(NULL, &channelMusic));
    FMODErrorCheck(system->createChannelGroup(NULL, &channelEffects));

    //FMOD::Channel* noise = PlaySoundTrack(soundtrack);
  }

	// !!!WAS MESSAGE HANDLING HERE
}

void SoundSystem::Update()
{
	system->update();
}

void SoundSystem::Free()
{
	system->release();

	// Delete all AudioTracks
	if (AudioList.size())
	{
		auto it = AudioList.end() - 1;
		int count = AudioList.size();

		// Delete the list starting from the end and working to the beginning
		while (count > 0)
		{
			//(*it)->track->release();  // FMOD free memory
			delete *it;               // AudioTrack free memory
			AudioList.pop_back();
			--count;
			if (count)
				it = AudioList.end() - 1;
		}
	}
}

  // Loop a soundtrack or effect a certain number of times (currently no global message interface - unused)
void SoundSystem::LoopNumberOfTimes(FMOD::Channel* track, int number)
{
  track->setMode(FMOD_LOOP_NORMAL);
  track->setLoopCount(number);
}

  // Settor for volume of a soundtrack by ID
  // Converts a value from 0-100 as a percentage to send to FMOD
void SoundSystem::SetVolume(SoundSystem* sys)
{
	const int ID = 0; //((const SetVolumeMessage*)msg)->SoundID;
	const int value = 0; //((const SetVolumeMessage*)msg)->percent;

  if (sys->AudioList.size() >= ID)
  {
    sys->AudioList[ID]->channel->setVolume((float)value/100.0f);
    sys->AudioList[ID]->volume = (float)value/100.0f;
  }
}

  // Creates an AudioTrack purposed as a streaming sound track
void SoundSystem::CreateSoundTrack(SoundSystem* sys)
{
	std::string filename = ""; //((CreateSoundTrackMessage*)msg)->filename;

  
  if(FileExists(filename.c_str()))
  {
    int id = IsSoundLoaded(filename, sys);

    if(id == NOT_FOUND)
    {
      AudioTrack* audio = new AudioTrack;
      audio->filename = filename;
      audio->track = newAudioStream(sys->system, audio->filename);
      sys->AudioList.push_back(audio);
      audio->id = sys->AudioList.size() - 1;
      // !!! *((const CreateSoundTrackMessage*)msg)->id = audio->id;
      //FMODErrorCheck(sys->system->playSound(FMOD_CHANNEL_FREE, audio->track, START_PAUSED, &(audio->channel)) );
      RepeatOn(audio->channel);
    }
      // If already loaded, return ID of existing track
    //else
    //  *((const CreateSoundEffectMessage*)msg)->id = id;
  }
  //else
    //Log::emit<LogLevelError>() << "Error in CreateSoundTrack(): " << filename << " does not exist! Check the spelling and/or path of the file." << Log::endl;
}

  // Creates an AudioTrack purposed as a sound effect
void SoundSystem::CreateSoundEffect(SoundSystem* sys)
{
	std::string filename = ""; // ((CreateSoundEffectMessage*)msg)->filename;

  if(FileExists(filename.c_str()))
  {
    int id = IsSoundLoaded(filename, sys);

    if(id == NOT_FOUND)
    {
      AudioTrack* audio = new AudioTrack;
      audio->filename = filename;
      audio->track = newSoundEffect(sys->system, audio->filename);
      audio->channel = NULL;
      sys->AudioList.push_back(audio);
      audio->id = sys->AudioList.size() - 1;
      // !!! *((const CreateSoundEffectMessage*)msg)->id = audio->id;
      //FMODErrorCheck(sys->system->playSound(FMOD_CHANNEL_FREE, audio->track, START_PAUSED, &(audio->channel)) );
     }
      // If already loaded, return ID of existing track
    //else
    //  *((const CreateSoundEffectMessage*)msg)->id = id;
  }
  /*else
    Log::emit<LogLevelError>() << "Error in CreateSoundEffect(): " << filename << " does not exist! Check the spelling and/or path of the file." << Log::endl;*/
}

  // Play a single instance of a sound effect
void SoundSystem::PlaySoundEffect(SoundSystem* sys)
{
  if ((!sys->MuteAll) && (!sys->HasLostDevice))
  {
		int ID = 0; // ((PlaySoundEffectMessage*)msg)->SoundID;

    if(IsSoundLoaded(ID, sys))      
    {  
      //switch (((PlaySoundEffectMessage*)msg)->SType)
      //{
      //    // Do not play if already playing
      //  case DROP :

      //    if(!IsSoundPlaying(ID, sys))
      //    {
      //      FMODErrorCheck(sys->system->playSound(FMOD_CHANNEL_FREE, sys->AudioList[ID]->track, true, &(sys->AudioList[ID]->channel)));
      //      FMODErrorCheck(sys->AudioList[ID]->channel->setVolume(sys->AudioList[ID]->volume));
      //      FMODErrorCheck(sys->AudioList[ID]->channel->setPaused(false));
      //    }

      //    break;

      //    // Play irregardless if already playing
      //  case PLAY :

      //    FMODErrorCheck(sys->system->playSound(FMOD_CHANNEL_FREE, sys->AudioList[ID]->track, true, &(sys->AudioList[ID]->channel)));
      //    FMODErrorCheck(sys->AudioList[ID]->channel->setVolume(sys->AudioList[ID]->volume));
      //    FMODErrorCheck(sys->AudioList[ID]->channel->setPaused(false));

      //    break;

      //     // Stop current instance, then play a new instance
      //  case REPLACE :
      //    FMODErrorCheck(sys->AudioList[ID]->channel->stop());
      //    FMODErrorCheck(sys->system->playSound(FMOD_CHANNEL_FREE, sys->AudioList[ID]->track, true, &(sys->AudioList[ID]->channel)));
      //    FMODErrorCheck(sys->AudioList[ID]->channel->setVolume(sys->AudioList[ID]->volume));
      //    FMODErrorCheck(sys->AudioList[ID]->channel->setPaused(false));

      //    break;
      //}

    }
    /*else
      Log::emit<LogLevelError>() << "Error in PlaySound Effect(), SoundTrack ID: " << ID << " does not exist." << Log::endl;*/
  }
}



  // FMOD call to create sound effect (loads entire file at once)
FMOD::Sound* SoundSystem::newSoundEffect(FMOD::System* system, std::string& filename)
{
  FMOD_RESULT result;
  FMOD::Sound* audio;
  result = system->createSound(filename.c_str(), FMOD_SOFTWARE | FMOD_ACCURATETIME, 0, &audio);
  FMODErrorCheck(result);
  return audio;
}

  // FMOD call to create sound track, streams the file as it plays
FMOD::Sound* SoundSystem::newAudioStream(FMOD::System* system, std::string& filename)
{
  FMOD_RESULT result;
  FMOD::Sound *audioStream;
  result = system->createStream(filename.c_str(), FMOD_SOFTWARE | FMOD_ACCURATETIME | FMOD_CREATESTREAM, 0, &audioStream);
  FMODErrorCheck(result);
  return audioStream;
}

  // FMOD call to start playing soundtrack
FMOD::Channel* SoundSystem::PlaySoundTrack(FMOD::System* system, FMOD::Sound* audio)
{
  FMOD_RESULT result;
  FMOD::Channel *channel;

  if ((MuteAllTracks) || (MuteAll) || (PauseAllTracks))
  {
    result = system->playSound(FMOD_CHANNEL_FREE, audio, true, &channel);
    FMODErrorCheck(result);
  }
  else
  {
    result = system->playSound(FMOD_CHANNEL_FREE, audio, false, &channel);
    FMODErrorCheck(result);
  }

  if (HasLostDevice)
    channel->setPaused(true);

  return channel;
}

  // Infinite loop
void SoundSystem::SetModeToRepeat(SoundSystem* sys)
{
	const int ID = 0; // ((const SetLoopingSoundMessage*)msg)->SoundID;

  if (IsSoundLoaded(ID, sys))
  {
    sys->AudioList[ID]->channel->setMode(FMOD_LOOP_NORMAL);
    sys->AudioList[ID]->channel->setLoopCount(-1);
  }
  /*else
    Log::emit<LogLevelError>() << "Error in SetModeToRepeat: SoundTrack ID " << ID << " does not exist." << Log::endl;*/
}

  // Pause soundtrack - should not be used on sound effect
void SoundSystem::Pause(SoundSystem* sys, int ID)
{
	if (IsSoundLoaded(ID, sys))
  {
    _ASSERT(sys->AudioList[ID]->channel);
    sys->AudioList[ID]->channel->setPaused(true);
    sys->AudioList[ID]->IsPlaying = false;
  }
  /*else
    Log::emit<LogLevelError>() << "Error in PauseUnpause: SoundTrack ID " << ID << " does not exist." << Log::endl;*/
}

  // Unpause soundtrack, should not be used on sound effect. See PlaySoundEffect if you want to play sound effects
void SoundSystem::Unpause(SoundSystem* sys, int ID)
{	
  if (IsSoundLoaded(ID, sys))
  {
    _ASSERT(sys->AudioList[ID]->channel);

    if ((!sys->MuteAll) && (!sys->MuteAllTracks))
      sys->AudioList[ID]->channel->setPaused(false);
    sys->AudioList[ID]->IsPlaying = true;
  }
  /*else
    Log::emit<LogLevelError>() << "Error in PauseUnpause: SoundTrack ID " << ID << " does not exist." << Log::endl;*/
}

  // Stops a soundtrack completely
void SoundSystem::StopPlayback(SoundSystem* sys, int ID)
{	
  if (IsSoundLoaded(ID, sys))
  {
    if (sys->AudioList[ID]->channel)
    {
      sys->AudioList[ID]->channel->stop();
      sys->AudioList[ID]->IsPlaying = false;
    }
  }
  /*else
    Log::emit<LogLevelError>() << "Error in StopPlackback: SoundTrack ID " << ID << " does not exist." << Log::endl;*/
}

  // Start a soundtrack
void SoundSystem::StartPlayback(SoundSystem* sys, int ID)
{	
  //const int value = ((const StartSoundMessage*)msg)->percent;

  if (IsSoundLoaded(ID, sys))
  {
    sys->AudioList[ID]->channel = sys->PlaySoundTrack(sys->system, sys->AudioList[ID]->track);
    sys->AudioList[ID]->IsPlaying = true;
  }
  /*else
    Log::emit<LogLevelError>() << "Error in StartPlayback: SoundTrack ID " << ID << " does not exist." << Log::endl;*/
}

  // Checks to see if a file has already been loaded
  // Returns the handle of the file if already loaded or -1 if not loaded
int SoundSystem::IsSoundLoaded(std::string& filename, SoundSystem* sys)
{
  for (auto it = sys->AudioList.begin(); it != sys->AudioList.end(); ++it)
    if ( !strcmp(filename.c_str(), (*it)->filename.c_str()) )
      return (*it)->id;

  return NOT_FOUND;
}

  // Checks to see if the ID is in the range of audio tracks in the list
bool SoundSystem::IsSoundLoaded(int ID, SoundSystem* sys)
{

  if (sys->AudioList.size())
    if (sys->AudioList.size() > (unsigned)ID)
      return true;

  return false;
}

bool SoundSystem::IsSoundPlaying(int ID, SoundSystem* sys)
{
  bool check;
  sys->AudioList[ID]->channel->isPlaying(&check);

  return check;
}

  // Workhorse function
void SoundSystem::PauseTracks(SoundSystem* sys)
{
  for (auto it = sys->AudioList.begin(); it != sys->AudioList.end(); ++it)
  {
    if ((*it)->IsPlaying)
      if ((*it)->channel)
      {
        bool isPlaying;
        sys->FMODErrorCheck((*it)->channel->isPlaying(&isPlaying));
        if (isPlaying)
          sys->FMODErrorCheck((*it)->channel->setPaused(true));
      }
  }
}

  // Workhorse function
void SoundSystem::UnpauseTracks(SoundSystem* sys)
{
  if ((!sys->MuteAll) && (!sys->MuteAllTracks) && (!sys->PauseAllTracks) && (!sys->HasLostDevice))
    for (auto it = sys->AudioList.begin(); it != sys->AudioList.end(); ++it)
    {
      if ((*it)->IsPlaying)
        if ((*it)->channel)
        {
          bool isPlaying;
          sys->FMODErrorCheck(sys->AudioList[(*it)->id]->channel->isPlaying(&isPlaying));
          if (isPlaying)
            sys->FMODErrorCheck(sys->AudioList[(*it)->id]->channel->setPaused(false));
        }
    }
}

void SoundSystem::PauseAllSoundTracks(SoundSystem* sys)
{
  sys->PauseAllTracks = true;
  sys->PauseTracks(sys);
}


void SoundSystem::UnpauseAllSoundTracks(SoundSystem* sys)
{
  sys->PauseAllTracks = false;
  sys->UnpauseTracks(sys);
}
  // For all AudioTracks that have the flag IsPlaying set to true, pause those soundtracks
  // This is mainly used for switching between pause menu where you don't want to play in game
  // sounds, but don't want to lose the place in the soundtrack when you switch back
void SoundSystem::LostDevice(SoundSystem* sys)
{
  sys->HasLostDevice = true;
  sys->PauseTracks(sys);
  //for (auto it = sys->AudioList.begin(); it != sys->AudioList.end(); ++it)
  //{
  //  if ((*it)->IsPlaying)
  //    if ((*it)->channel)
  //    {
  //      bool isPlaying;
  //      sys->FMODErrorCheck(sys->AudioList[(*it)->id]->channel->isPlaying(&isPlaying));

  //      if (isPlaying)
  //        sys->FMODErrorCheck(sys->AudioList[(*it)->id]->channel->setMute(true));
  //    }
  //}
}

  // Unpause all AudioTracks that are set to be playing but are paused (IE menu screen)
void SoundSystem::RegainDevice(SoundSystem* sys)
{
  sys->HasLostDevice = false;
  sys->UnpauseTracks(sys);
  //if ((!sys->MuteAll) && (!sys->MuteAllTracks) && (!sys->PauseAllTracks))
  //  for (auto it = sys->AudioList.begin(); it != sys->AudioList.end(); ++it)
  //  {
  //    if ((*it)->IsPlaying)
  //      if ((*it)->channel)
  //      {
  //        bool isPlaying;
  //        sys->FMODErrorCheck(sys->AudioList[(*it)->id]->channel->isPlaying(&isPlaying));

  //        if (isPlaying)
  //          sys->FMODErrorCheck(sys->AudioList[(*it)->id]->channel->setMute(false));
  //      }
  //  }
}

void SoundSystem::ToggleMute(SoundSystem* sys)
{
  sys->MuteAll = !sys->MuteAll;

  if (sys->MuteAll)
  {
    sys->PauseTracks(sys);

      //for (auto it = sys->AudioList.begin(); it != sys->AudioList.end(); ++it)
      //  if ((*it)->channel)
      //    sys->FMODErrorCheck((*it)->channel->setPaused(true));
  }
  else 
  {
    sys->UnpauseTracks(sys);
  }
}


void SoundSystem::ToggleMuteSoundTracks(SoundSystem* sys)
{
  sys->MuteAllTracks = !sys->MuteAllTracks;

  if (sys->MuteAllTracks)
  {
    //for (auto it = sys->AudioList.begin(); it != sys->AudioList.end(); ++it)
    //{
    //  if ((*it)->channel)
    //  {
    //    bool isPlaying;
    //    sys->FMODErrorCheck(sys->AudioList[(*it)->id]->channel->isPlaying(&isPlaying));
    //    if (isPlaying)
    //      sys->FMODErrorCheck(sys->AudioList[(*it)->id]->channel->setPaused(true));
    //  }
    //}
    sys->PauseTracks(sys);
  }
  else
  {
    //for (auto it = sys->AudioList.begin(); it != sys->AudioList.end(); ++it)
    //{
    //  if ((*it)->channel)
    //  {
    //    bool isPlaying;
    //    sys->FMODErrorCheck(sys->AudioList[(*it)->id]->channel->isPlaying(&isPlaying));
    //    if (isPlaying)
    //      sys->FMODErrorCheck(sys->AudioList[(*it)->id]->channel->setPaused(false));
    //  }

    //  
    //}
    sys->UnpauseTracks(sys);
  }
}
