#pragma once

#include "../Systems.h"
#include "NoteFrequency.h"
#include "Voices.h"

class CounterPoint : public System {
public:
  void Init(void);
  void Update(double dt);
  void Free(void);

  Note getPitch(Voice);

private:
  Voice mSoprano;
  Voice mAlto;
  Voice mTenor;
  Voice mBass;

};