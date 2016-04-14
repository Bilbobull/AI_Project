#pragma once
#include "Graphics\Context.h"
#include "Graphics\GraphicsSystem.h"
#include "Input\InputSystem.h"
#include "Sound\AudioSystem.hpp"
#include "Sound\BPM.h"
#include "Sound\CounterPointSystem.h"
#include "Systems.h"


extern std::vector <System*> Systems;
extern bool Running;


int main(int argc, char* argv[])
{
  Running = true;
	
	//SoundSystem mSoundSystem;
	//mSoundSystem.Init();

  Systems.push_back(new GraphicsSystem());
  Systems.push_back(new InputSystem());
	Systems.push_back(new CounterPoint());
	Systems.push_back(new AudioSystem());

  for (auto it : Systems)
    it->Init();

  while (Running == true)
  {
    for (auto it : Systems)
      it->Update(0);

		/*mSoundSystem.Update();*/
  }

	for (auto it : Systems)
		it->Free();

	/*mSoundSystem.Free();*/

  return 0;
}