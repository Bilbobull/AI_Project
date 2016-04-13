#include "CounterPointSystem.h"
#include "KeyScales.h"
#include "AudioSystem.hpp"

CounterPoint::CounterPoint() {

}

void CounterPoint::Init(void) {
  mBass.setLowestNoteRange(F2);
  mBass.setHighestNoteRange(D4);

  mTenor.setLowestNoteRange(B2b);
  mTenor.setHighestNoteRange(G4);

  mAlto.setLowestNoteRange(A3);
  mAlto.setHighestNoteRange(F5);

  mSoprano.setLowestNoteRange(C4);
  mSoprano.setHighestNoteRange(A5);

}

void CounterPoint::Update(double dt) {
	if (mBPM.isBeat()) {
		mTimeSignature.incrementBeats();

		if (mTimeSignature.isNewMeasure()) {
			mTimeSignature.incrementMeasures();
		}

	}

}

void CounterPoint::Free(void) {


}


