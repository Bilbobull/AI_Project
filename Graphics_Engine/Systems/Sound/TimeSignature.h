#pragma once

class TimeSignature {
  public:
		TimeSignature(){};
		TimeSignature(int beats, int beatsPerMeasure) : mBeats(beats), mBeatsPerMeasure(beatsPerMeasure), mBeatsThisMeasure(0) {};
		TimeSignature(TimeSignature& newSignature) {
			mBeats = newSignature.mBeats; 
			mBeatsPerMeasure = newSignature.mBeatsPerMeasure;
			mBeatsThisMeasure = newSignature.mBeatsThisMeasure;
		};

		bool isNewMeasure();
		bool isPhraseEnd();
		void resetBeats();
		void resetPhrase();		
		void incrementBeats();
		void incrementMeasures();
		void setNewTimeSignature(int beats, int beatsPerMeasure);

	private:
		int mBeats;
		int mBeatsPerMeasure;
		int mBeatsThisMeasure;
		int mPhraseLength;
		int mMeasureCount;
};