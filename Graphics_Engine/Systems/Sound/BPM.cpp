#include "BPM.h"

BPM::BPM(int tempo) {
	
	setTempo(tempo);
	mBeat = false;
}


void BPM::Init(void) {

	
	mStart = std::chrono::system_clock::now();
}

void BPM::Update(double dt) {
	std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now() - mStart;
	if (elapsed_seconds.count() >= mDT) {
		mBeat = true;
	}
}

void BPM::Free(void) {


}

bool BPM::isBeat() {
	return mBeat;
}

void BPM::resetTimer() {
	mStart = std::chrono::system_clock::now();
	mBeat = false;
}

void BPM::setTempo(int tempo) {
	_ASSERT(tempo); // tempo can't be 0, otherwise divide by 0 error
	mDT = 60.0f / (float)tempo; // how many seconds pass before a "beat" occurs
	mTempo = tempo;
}

int BPM::getTempo() {
	return mTempo;
}

double BPM::getDT() {
	return mDT;
}