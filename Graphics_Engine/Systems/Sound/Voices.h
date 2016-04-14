#pragma once
#include <deque>
#include "NoteDuration.h"

class Voice {
public:

  Note getHighestRelatedNote() { return mRelatedHighestNote; };
  Note getLowestRelatedNote() { return mRelatedLowestNote; };
  void setHighestRelatedNote(Note note) { mRelatedHighestNote = note; };
  void setLowestRelatedNote(Note note) { mRelatedLowestNote = note; };

  Note getHighestNoteRange() { return mRangeHighestNote; };
  Note getLowestNoteRange() { return mRangeLowestNote; };
  void setHighestNoteRange(Note note) { mRangeHighestNote = note; };
  void setLowestNoteRange(Note note) { mRangeLowestNote = note; };

	void setStaccato(float value) { mStacatto = value; };

	void setNewDuration(double dt) { 
		mDurationUntilNextNote = dt;
		mHoldDuration = mDurationUntilNextNote * mStacatto;
	};

	Note mCurrent;
	bool mSetNewNote;

	std::deque<Note> mPossibleNotes;

	// Returns true if a new note needs to be chosen
	bool updateTimer(double dt) { 
		mDurationUntilNextNote -= dt;
		mHoldDuration -= dt;

		if (mDurationUntilNextNote <= 0) {
			return true;
		}

		return false;
	};

	void setHoldDuration(double dt) {
		mHoldDuration = dt;
	};

	void setHoldDurationUntilNextNote(double dt) {
		mDurationUntilNextNote = dt;
	};

	// Returns true if a note should not be released
	bool checkNoteDuration() {
		return mHoldDuration > 0.0f;
	};

private:
	double mHoldDuration; // Should = Duration until next note * staccato value
	double mDurationUntilNextNote;
	float mStacatto;

  Note mRangeHighestNote;
  Note mRangeLowestNote;
  Note mRelatedHighestNote;
  Note mRelatedLowestNote;
};