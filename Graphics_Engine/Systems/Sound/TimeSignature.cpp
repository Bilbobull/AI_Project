#include "TimeSignature.h"
#include "BPM.h"


void TimeSignature::setNewTimeSignature(int beats, int beatsPerMeasure) {
	mBeats = beats;
	mBeatsPerMeasure = beatsPerMeasure;
}

bool TimeSignature::isNewMeasure()
{ 
	if (mBeatsPerMeasure == mBeatsThisMeasure) {
		resetBeats();
		return true;
	}

	return false;
}

bool TimeSignature::isPhraseEnd()
{
	if (mPhraseLength == mMeasureCount) {
		resetPhrase();
		return true;
	}

	return false;
}

void TimeSignature::resetBeats()
{ 
	mBeatsThisMeasure = 0; 
}

void TimeSignature::resetPhrase()
{
	mMeasureCount = 0;
}

void TimeSignature::incrementBeats() {
	++mBeatsThisMeasure; 
}

void TimeSignature::incrementMeasures() {
	++mMeasureCount;
}

