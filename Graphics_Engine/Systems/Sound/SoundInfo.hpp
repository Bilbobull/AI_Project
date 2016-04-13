#pragma once

#include "AudioTypes.h"

#include <vector>
#include <string>


#define SFX_AMOUNT 2 // make sure I match how many sound effects are in the SFXType 


class SoundInfo
{
  SoundInfo(const std::string name, SFX::SFXType sfxIndex)
  {
    _fileName = "../ShotInTheDark/Audio/" + name;
    _sfxType = sfxIndex;
    _musType = Music::NONE;
  }

  SoundInfo(const std::string name, Music::MusicType musicIndex)
  {
    _fileName = "../ShotInTheDark/Audio/" + name;
    _sfxType = SFX::NONE;
    _musType = musicIndex;
  }


  std::string _fileName;
  SFX::SFXType _sfxType;
  Music::MusicType _musType;

};


std::vector<SoundInfo> soundInfo;
