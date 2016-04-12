/******************************************************************************/
/*! @@HEADER@@
  \copyright All content © 2013 DigiPen (USA) Corporation, all rights reserved.
  \file      SoundSystem.h
  \author    Eric Johnston
  \brief
    NO_BRIEF_SET
*/
/******************************************************************************/
#pragma once
#include "../Systems.h"
#include "FMOD/fmod.hpp"
#include "FMOD/fmod_errors.h"

  //
#define NOT_FOUND -1
#define START_PAUSED true

  // Data structure for audio
struct AudioTrack
{
  AudioTrack();
  FMOD::Channel* channel;
  FMOD::Sound* track;
  std::string filename;
  bool IsPlaying;
    // Element# in AudioList, also the handle by which user will interface with a created sound
  int id;
  float volume;
};

class SoundSystem //: public System
{
  public:
    SoundSystem();
    ~SoundSystem();
    void Init();
    void Update();
		void Free();
    
      //Need to implement these!
    bool MuteAll;
    bool MuteAllTracks;
    bool PauseAllTracks;
    bool HasLostDevice;
    std::vector<std::string> SoundTrackFiles;
    std::vector<std::string> SoundEffectFiles;

  private:
      // Create new audio sound effect
      // This loads the entire soundbyte before play
      // (good for small files)
    static FMOD::Sound* newSoundEffect(FMOD::System* system, std::string& filename);

      // Create song for playback
      // This will continuously buffer during playback so as to
      // not load the entire song first (if large file)
    static FMOD::Sound* newAudioStream(FMOD::System* system, std::string& filename);
    
      // Return value is a ptr to the controls for the channel the sound was assigned to
    FMOD::Channel* PlaySoundTrack(FMOD::System* system, FMOD::Sound* audio);

    static void PlaySoundEffect(SoundSystem* sys);

      // Continuous loop - you probably only want to do this on a soundtrack
    static void SetModeToRepeat(SoundSystem* sys);

      // Pause or Unpause a channel
    static void Pause(SoundSystem* sys, int ID);
		static void Unpause(SoundSystem* sys, int ID);
		static void LostDevice(SoundSystem* sys);
		static void RegainDevice(SoundSystem* sys);
		static void ToggleMute(SoundSystem* sys);
		static void ToggleMuteSoundTracks(SoundSystem* sys);
		static void PauseTracks(SoundSystem* sys);
		static void UnpauseTracks(SoundSystem* sys);
    static void PauseAllSoundTracks(SoundSystem* sys);
    static void UnpauseAllSoundTracks(SoundSystem* sys);

      // Stop sound
    static void StopPlayback(SoundSystem* sys, int ID);

      // Wrapper around getting FMOD errors
    static void FMODErrorCheck(FMOD_RESULT result);

    static void LoopNumberOfTimes(FMOD::Channel* track, int number);

      // Volume percent must be from 0 to 100
    static void SetVolume(SoundSystem* sys);

      // For continuous play - buffers the song as it plays
    static void CreateSoundTrack(SoundSystem* sys);

      // For short sound effects or small size soundtracks
    static void CreateSoundEffect(SoundSystem* sys);
    
      // Start a soundtrack or soundeffect
		static void StartPlayback(SoundSystem* sys, int ID);

      // Returns the AudioList element position of the soundtrack if it has already been loaded
		static int  IsSoundLoaded(std::string& filename, SoundSystem* sys);

      // Checks to see if the AudioList [ID] is valid
    static bool IsSoundLoaded(int ID, SoundSystem* sys);

    static bool IsSoundPlaying(int ID, SoundSystem* sys);

    FMOD::System *system;
    FMOD::ChannelGroup *channelMusic;
    FMOD::ChannelGroup *channelEffects;
    FMOD_SPEAKERMODE speakermode;
    FMOD_CAPS caps;

      // Vector element position corresponds to the sound ID
    std::vector<AudioTrack*> AudioList;

      // For lost device
    //std::vector<AudioTrack*> PausedList;
    //std::vector<AudioTrack*> UnpausedList;

};

