#pragma once
#include "TimeSignature.h"
#include "BPM.h"


void TimeSignature::setNewTimeSignature(int beats, int beatsPerMeasure) {
	mBeats = beats;
	mBeatsPerMeasure = beatsPerMeasure;
	setupWeights();
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

NoteType TimeSignature::getRandomNoteDuration() {
	int randNum = rng.getRandomValue(mTotalWeight);

	if (mBeats == 3) {
		for (int i = NoteType::SixtyFourthNote; i < NoteType::END_LIST; ++i) {
			randNum -= ThreeFourWeight[i];

			if (randNum <= 0) {
				return (NoteType)i;
			}
		}
	}
	else if (mBeats == 4) {
		for (int i = NoteType::SixtyFourthNote; i < NoteType::END_LIST; ++i) {
			randNum -= FourFourWeight[i];

			if (randNum <= 0) {
				return (NoteType)i;
			}
		}
	}
	else {
		for (int i = NoteType::SixtyFourthNote; i < NoteType::END_LIST; ++i) {
			randNum -= SixEightWeight[i];

			if (randNum <= 0) {
				return (NoteType)i;
			}
		}
	}

	// Should never reach here
	return NoteType::END_LIST;
}

void TimeSignature::setupWeights() {	

	if (mBeats == 3) {
		ThreeFourWeight.push_back(1);  // 64th
		ThreeFourWeight.push_back(2);  // 32nd
		ThreeFourWeight.push_back(3);  // 16th
		ThreeFourWeight.push_back(8);  // 8th
		ThreeFourWeight.push_back(16); // Quarter
		ThreeFourWeight.push_back(5);  // Dotted Quarter
		ThreeFourWeight.push_back(3);  // Half
		ThreeFourWeight.push_back(2);  // Dotted Half
		ThreeFourWeight.push_back(1);  // Whole
		mTotalWeight = 41;
	}
	else if (mBeats == 4) {
		FourFourWeight.push_back(1);	 // 64th
		FourFourWeight.push_back(2);	 // 32nd
		FourFourWeight.push_back(4);	 // 16th
		FourFourWeight.push_back(14);	 // 8th
		FourFourWeight.push_back(20);	 // Quarter
		FourFourWeight.push_back(8);	 // Dotted Quarter
		FourFourWeight.push_back(10);	 // Half
		FourFourWeight.push_back(6);	 // Dotted Half
		FourFourWeight.push_back(4);	 // Whole
		mTotalWeight = 69;
	}
	else {
		SixEightWeight.push_back(2);	 // 64th
		SixEightWeight.push_back(4);	 // 32nd
		SixEightWeight.push_back(10);	 // 16th
		SixEightWeight.push_back(16);	 // 8th
		SixEightWeight.push_back(10);	 // Quarter
		SixEightWeight.push_back(6);	 // Dotted Quarter
		SixEightWeight.push_back(1);	 // Half
		SixEightWeight.push_back(3);	 // Dotted Half
		SixEightWeight.push_back(1);	 // Whole
		mTotalWeight = 53;
	}
}