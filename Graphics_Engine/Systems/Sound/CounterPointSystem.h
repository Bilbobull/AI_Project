#pragma once
#include "../Systems.h"
#include "NoteFrequency.h"
#include "Voices.h"
#include "TimeSignature.h"
#include "NoteDuration.h"
#include "BPM.h"


class CounterPoint : public System {
public:
	CounterPoint();

  void Init(void);
  void Update(double dt);
  void Free(void);

  Note getPitch(Voice);

private:
  Voice mSoprano;
  Voice mAlto;
  Voice mTenor;
  Voice mBass;

	TimeSignature mTimeSignature;
	NoteDuration mNoteDuration;
	BPM mBPM;
};