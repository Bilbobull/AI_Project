/******************************************************************************/
/*! @@HEADER@@
  \copyright All content © 2013 DigiPen (USA) Corporation, all rights reserved.
  \file      SoundEffectComponent.cpp
  \author    Eric Johnston
  \brief
    NO_BRIEF_SET
*/
/******************************************************************************/

#include "SoundEffectComponent.h"


ComponentSoundEffect::ComponentSoundEffect(std::string name) : volume(100)
{
}

ComponentSoundEffect::~ComponentSoundEffect()
{
}


void ComponentSoundEffect::Initialize()
{
  
}

void ComponentSoundEffect::Start()
{
  
}

void ComponentSoundEffect::Pause()
{
  
}

void ComponentSoundEffect::Unpause()
{
  
}

void ComponentSoundEffect::SetVolume(int newVolume)
{
  volume = newVolume;
}

int ComponentSoundEffect::GetVolume() const
{
  return volume;
}

void ComponentSoundEffect::SetFileName(std::string _filename)
{
  filename = _filename;
  
}

std::string ComponentSoundEffect::GetFileName() const
{
  return filename;
}

void ComponentSoundEffect::CleanupData()
{
  
}