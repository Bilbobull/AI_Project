#pragma once
#include "NoteDuration.h"
#include <vector>
#include "../RNG.h"

class TimeSignature {
  public:
		TimeSignature(){};
		TimeSignature(int beats, int beatsPerMeasure) : mBeats(beats), mBeatsPerMeasure(beatsPerMeasure), mBeatsThisMeasure(0) { setupWeights(); };
		TimeSignature(TimeSignature& newSignature) {
			mBeats = newSignature.mBeats; 
			mBeatsPerMeasure = newSignature.mBeatsPerMeasure;
			mBeatsThisMeasure = newSignature.mBeatsThisMeasure;
			ThreeFourWeight = newSignature.ThreeFourWeight;
			FourFourWeight = newSignature.FourFourWeight;
			SixEightWeight = newSignature.SixEightWeight;
		};

		bool isNewMeasure();
		bool isPhraseEnd();
		void resetBeats();
		void resetPhrase();		
		void incrementBeats();
		void incrementMeasures();
		void setNewTimeSignature(int beats, int beatsPerMeasure);
		NoteType getRandomNoteDuration();

	private:
		void setupWeights();

		int mBeats;
		int mBeatsPerMeasure;
		int mBeatsThisMeasure;
		int mPhraseLength;
		int mMeasureCount;
		int mTotalWeight;

		RNG rng;

		std::vector<int> ThreeFourWeight;
		std::vector<int> FourFourWeight;
		std::vector<int> SixEightWeight;
};