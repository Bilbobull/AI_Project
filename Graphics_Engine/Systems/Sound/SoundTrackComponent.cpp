/******************************************************************************/
/*! @@HEADER@@
  \copyright All content © 2013 DigiPen (USA) Corporation, all rights reserved.
  \file      SoundTrackComponent.cpp
  \author    Eric Johnston
  \brief
    NO_BRIEF_SET
*/
/******************************************************************************/

#include "SoundTrackComponent.h"


ComponentSoundTrack::ComponentSoundTrack() : volume(100)
{
  soundTrackID = -1;
}

ComponentSoundTrack::~ComponentSoundTrack()
{
}


void ComponentSoundTrack::Init()
{
  
}

void ComponentSoundTrack::Start()
{

}

void ComponentSoundTrack::Pause()
{
  
}

void ComponentSoundTrack::Unpause()
{
  
}

void ComponentSoundTrack::SetVolume(int newVolume)
{
  volume = newVolume;
  
}

int ComponentSoundTrack::GetVolume() const
{
  return volume;
}

void ComponentSoundTrack::SetFileName(std::string _filename)
{
  // Need to cleanup old soundtrack first!!!!!
  if(soundTrackID != -1)
  {
    
  }

  filename = _filename;

}

std::string ComponentSoundTrack::GetFileName() const
{
  return filename;
}

void ComponentSoundTrack::CleanupData()
{

}