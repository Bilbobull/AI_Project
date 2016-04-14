#pragma once
#include "CounterPointSystem.h"
#include "KeyScales.h"
#include "AudioSystem.hpp"
#include <cstdlib>

CounterPoint::CounterPoint() :
  mTimeSignature(4, 4)
, mBPM(120)
{

	// Create voices
	for (int i = 0; i < Voice_ID::END_VOICES; ++i) {
		mVoice.push_back(Voice());
	}

	mScale = &Cmajor;
	mDuration.resetDurations(mBPM.getDT());
}

void CounterPoint::Init(void) {

	// Set voice range
	mVoice[Voice_ID::Bass].setLowestNoteRange(F2);
	mVoice[Voice_ID::Bass].setHighestNoteRange(A4);
	mVoice[Voice_ID::Bass].mCurrent = (*mScale)[4];
	mVoice[Voice_ID::Bass].setStaccato(1.0f);

	mVoice[Voice_ID::Tenor].setLowestNoteRange(D3);
	mVoice[Voice_ID::Tenor].setHighestNoteRange(G4);
	mVoice[Voice_ID::Tenor].mCurrent = (*mScale)[8];
	mVoice[Voice_ID::Tenor].setStaccato(1.0f);

	mVoice[Voice_ID::Alto].setLowestNoteRange(B3);
	mVoice[Voice_ID::Alto].setHighestNoteRange(D5);
	mVoice[Voice_ID::Alto].mCurrent = (*mScale)[16];
	mVoice[Voice_ID::Alto].setStaccato(1.0f);

	mVoice[Voice_ID::Soprano].setLowestNoteRange(C4);
	mVoice[Voice_ID::Soprano].setHighestNoteRange(A5);
	mVoice[Voice_ID::Soprano].mCurrent = (*mScale)[22];
	mVoice[Voice_ID::Soprano].setStaccato(1.0f);

	mBPM.Init();
}

void CounterPoint::Update(double dt) {

	// Send amount of passed time to each note
	// Check to see if note duration is <= 0
	// If so, decide on next note
	// Play note
	mBPM.Update(dt);
	updateVoiceDuration(mBPM.timePassed());
	if (mDirty) {
		processNoteMotion(); // Workhorse for note decisions	
		mDirty = false;
	}

	setNotesPlaying();

	//if (mBPM.isBeat()) {
	//	mTimeSignature.incrementBeats();

	//	if (mTimeSignature.isNewMeasure()) {
	//		mTimeSignature.incrementMeasures();
	//	}

	//}

}

void CounterPoint::Free(void) {
}

// Verifies that voice motion adheres to CounterPoint rules
int CounterPoint::evaluateSet(VoiceMotion& v1, VoiceMotion& v2) {

	int weight = 0;

	if (v1.prospectiveNote > v2.prospectiveNote) {
		return 0;
	}
	// Check for similar motion
	int interval = GetDistanceBetweenNotes(*mScale, v1.prospectiveNote, v2.prospectiveNote);

	//if (interval == 0) {
	//	return 0;
	//}

	// If there is motion
	if (v1.motion != Same) {
		// And motion is in the same direction
		if (v1.motion == v2.motion) {
		// Check for distance of a 5th or octave, 5th can be interval 4 below or 5 above - in this case we don't care about direction because it all sounds the same
			if (/*|| (interval == 4) ||*/ (interval == 0) || (interval == 5) || (interval == 8) || /*(interval == 12) ||*/ (interval == 13) || (interval == 16)) {
				return 0;
			}
		}

		// Reward intervals of 3rds or 6ths, we like those
		if ((interval == 3) || (interval == 6) || (interval == 11) || (interval == 14) || (interval == 19) || (interval == 22)) {
			weight += 5;
		}
		// Don't like the 7ths nearly so much
		else if ((interval == 7) || (interval == 14) || (interval == 21)) {
			weight += 1;					
		}
		// 2s, 4s and 5s are ok
		else {
			weight += 3;					
		}

	}

	// Guarantees that this set will be skipped if 0 - prevents accidentally adding weight to the next option when choosing a set
	if (weight < 0){
		weight = 0;
	}

	return weight;
}

// Populates noteList with all possible notes a voice can choose from, good or bad. Checks to make sure it won't cross over past another voice
void CounterPoint::getPossibleNotes(Voice_ID voice, std::deque<Note>& noteList) {

	// Need to take into account end of phrase? Could be pushed to stretch...

	switch (voice) {
	case Voice_ID::Soprano :
		noteList = GetNotesBetweenVoices(*mScale,
			mVoice[Voice_ID::Alto].mCurrent > mVoice[Voice_ID::Soprano].getLowestNoteRange() ? mVoice[Voice_ID::Alto].mCurrent : mVoice[Voice_ID::Soprano].getLowestNoteRange(),
			mVoice[Voice_ID::Soprano].getHighestNoteRange());
		return;
		break;

	case Voice_ID::Alto :
		noteList = GetNotesBetweenVoices(*mScale,
			mVoice[Voice_ID::Tenor].mCurrent > mVoice[Voice_ID::Alto].getLowestNoteRange() ? mVoice[Voice_ID::Tenor].mCurrent : mVoice[Voice_ID::Alto].getLowestNoteRange(),
			mVoice[Voice_ID::Soprano].mCurrent < mVoice[Voice_ID::Alto].getHighestNoteRange() ? mVoice[Voice_ID::Soprano].mCurrent : mVoice[Voice_ID::Alto].getHighestNoteRange());
		return;
		break;

	case Voice_ID::Tenor :
		noteList = GetNotesBetweenVoices(*mScale,
			mVoice[Voice_ID::Bass].mCurrent > mVoice[Voice_ID::Tenor].getLowestNoteRange() ? mVoice[Voice_ID::Bass].mCurrent : mVoice[Voice_ID::Tenor].getLowestNoteRange(),
			mVoice[Voice_ID::Alto].mCurrent < mVoice[Voice_ID::Tenor].getHighestNoteRange() ? mVoice[Voice_ID::Alto].mCurrent : mVoice[Voice_ID::Tenor].getHighestNoteRange());
		return;
		break;

	case Voice_ID::Bass :
		noteList = GetNotesBetweenVoices(*mScale,
			mVoice[Voice_ID::Bass].getLowestNoteRange(),
			mVoice[Voice_ID::Tenor].mCurrent < mVoice[Voice_ID::Bass].getHighestNoteRange() ? mVoice[Voice_ID::Tenor].mCurrent : mVoice[Voice_ID::Bass].getHighestNoteRange());
		return;
		break;

	default:
		break;
	}

	return;
}

void CounterPoint::updateVoiceDuration(double dt) {
	for (int i = 0; i < Voice_ID::END_VOICES; ++i) {
		if (mVoice[i].updateTimer(dt)) {
			mVoice[i].mSetNewNote = true;
			mDirty = true;
		}
	}
}

void CounterPoint::setScale(std::vector<Note>* scale) {
	mScale = scale;
}

void CounterPoint::processNoteMotion() {
	for (int i = 0; i < Voice_ID::END_VOICES; ++i) {
		if (mVoice[i].mSetNewNote) {
			getPossibleNotes((Voice_ID)i, mVoice[i].mPossibleNotes);
		}

		if (mVoice[i].mPossibleNotes.empty()) {
			mVoice[i].mPossibleNotes.push_back(mVoice[i].mCurrent);
		}
	}

	int totalWeight = 0; // for determining random note choice, the higher the weight the more likely it will be chosen
	std::vector<VoiceEvaluationSet> choices; // Sets of voice motion - each vector element will contain a set of changes for each voice and weight

	// Create all possible combinations
	
	for (auto bass : mVoice[Voice_ID::Bass].mPossibleNotes) {
		int weight = 0;
		VoiceMotion bas = createVoiceMotion(mVoice[Voice_ID::Bass].mCurrent, bass);

		for (auto tenor : mVoice[Voice_ID::Tenor].mPossibleNotes) {
			VoiceMotion ten = createVoiceMotion(mVoice[Voice_ID::Tenor].mCurrent, tenor);			
			int tw = evaluateSet(bas, ten);
			if (tw) {
				weight += tw;
			}
			else {
				continue;
			}

			for (auto alto : mVoice[Voice_ID::Alto].mPossibleNotes) {
				VoiceMotion alt = createVoiceMotion(mVoice[Voice_ID::Alto].mCurrent, alto);		
				int aw = evaluateSet(ten, alt);
				if (aw) {
					weight += aw;
				}
				else {
					continue;
				}

				for (auto soprano : mVoice[Voice_ID::Soprano].mPossibleNotes) {
					VoiceMotion sop = createVoiceMotion(mVoice[Voice_ID::Bass].mCurrent, soprano);
					int sw = evaluateSet(alt, sop);
					if (sw) {
						weight += sw;
					}
					else {
						continue;
					}

					std::deque<VoiceMotion> list;
					list.push_back(bas);
					list.push_back(ten);
					list.push_back(alt);
					list.push_back(sop);

					totalWeight += weight;
					choices.push_back(VoiceEvaluationSet(std::move(list), weight));
				}
			}
		}
	}
	

	// Choose one at random - higher weight has better chance!
	int selection = rng.getRandomValue(totalWeight);

	// Iterate until you find selection
	for (auto set : choices) {
		selection -= set.weight;
		
		// Found choice
		if (selection <= 0) {
			for (int i = 0; i < Voice_ID::END_VOICES; ++i) {
				if (mVoice[i].mSetNewNote) {
					mVoice[i].mCurrent = set.mSet[i].prospectiveNote;
					mVoice[i].setNewDuration(mDuration.chooseDuration(mTimeSignature.getRandomNoteDuration()));
					mVoice[i].mSetNewNote = false;
				}
			}
		}
	}

	// Cleanup all the damn possible note lists!
	for (int i = 0; i < Voice_ID::END_VOICES; ++i) {
		mVoice[i].mPossibleNotes.clear();
	}
}


void CounterPoint::setNotesPlaying() {
	for (int i = 0; i < Voice_ID::END_VOICES; ++i) {
		if (mVoice[i].checkNoteDuration()) {
			AudioSystem::playFrequency(i, mVoice[i].mCurrent);
		}
		else{
			AudioSystem::playFrequency(i, Rest);
		}
	}
}



VoiceMotion CounterPoint::createVoiceMotion(Note start, Note prospect) {
	VoiceMotion temp;
	temp.startingNote = start;
	temp.prospectiveNote = prospect;

	if (temp.startingNote > temp.prospectiveNote) {
		temp.motion = Motion::Down;
	}
	else if (temp.startingNote < temp.prospectiveNote) {
		temp.motion = Motion::Up;
	}
	else {
		temp.motion = Motion::Same;
	}

	return temp;
}
