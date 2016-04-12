/******************************************************************************/
/*! @@HEADER@@
  \copyright All content © 2013 DigiPen (USA) Corporation, all rights reserved.
  \file      SoundEffectComponent.hpp
  \author    Eric Johnston
  \brief
    NO_BRIEF_SET
*/
/******************************************************************************/
#pragma once
#include "SoundSystem.h"
#include "../Systems.h"

class ComponentSoundEffect : public System
{
  public:
    ComponentSoundEffect(std::string name);
    ~ComponentSoundEffect();
    void Initialize();
    void Start();
    void Pause();
    void Unpause();
    void SetVolume(int newVolume);
    int GetVolume() const;
    void SetFileName(std::string _filename);
    std::string GetFileName() const;
    void CleanupData();

    bool m_ArchetypeEditorHackFlag;

  private:
    int soundEffectID;
    std::string filename;
      // Must be integer value from 0-100
    int volume;
};