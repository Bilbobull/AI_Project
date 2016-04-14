#pragma once
#include "../Systems.h"
#include "NoteFrequency.h"
#include "Voices.h"
#include "TimeSignature.h"
#include "NoteDuration.h"
#include "BPM.h"
#include <deque>
#include "AudioSystem.hpp"
#include "../RNG.h"

enum Motion {
	Same,
	Up,
	Down
	
};

struct VoiceMotion {
	Note startingNote;
	Note prospectiveNote;
	Motion motion;
};

struct VoiceEvaluationSet {
	VoiceEvaluationSet(std::deque<VoiceMotion>& set, int w) : mSet(set), weight(w) {};
	std::deque<VoiceMotion> mSet;
	int weight = 0;
};

class CounterPoint : public System {
public:
	CounterPoint();

  void Init(void);
  void Update(double dt);
  void Free(void);

	void setScale(std::vector<Note>* scale);

private:
	int evaluateSet(VoiceMotion& v1, VoiceMotion& v2);
	void getPossibleNotes(Voice_ID voice, std::deque<Note>& noteList);
	void updateVoiceDuration(double dt);
	void processNoteMotion();
	void setNotesPlaying();
	int getRandomValue(int max);
	VoiceMotion& chooseMotionSet();
	VoiceMotion CounterPoint::createVoiceMotion(Note start, Note prospect);
	bool mDirty = false;

	std::vector<Voice> mVoice;
	std::vector<Note>* mScale;
	TimeSignature mTimeSignature;
	NoteDuration mDuration;
	BPM mBPM;
	RNG rng;
};