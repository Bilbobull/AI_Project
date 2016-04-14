#pragma once
#include "BPM.h"

BPM::BPM(int tempo) {
	
	setTempo(tempo);
	mBeat = false;
}


void BPM::Init(void) {	
	mStart = std::chrono::system_clock::now();
}

void BPM::Update(double dt) {
	//std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now() - mStart; //timer for beat
	mTimePassed = std::chrono::system_clock::now() - mCurrentFrame; //timer per frame
	mCurrentFrame = std::chrono::system_clock::now();
	//if (elapsed_seconds.count() >= mDT) {
	//	mBeat = true;
	//}
}

//bool BPM::isBeat() {
//	return mBeat;
//}
//
//void BPM::resetTimer() {
//	mStart = std::chrono::system_clock::now();
//	mBeat = false;
//}

// tempo will be set to 40 if 0 is attempted to be passed in, no divide by zero error possible
void BPM::setTempo(int tempo) {
	mDT = 60.0f / (float)tempo; // how many seconds pass before a "beat" occurs
	mTempo = tempo;
}

int BPM::getTempo() {
	return mTempo;
}

double BPM::getDT() {
	return mDT;
}

double BPM::timePassed() {
	return mTimePassed.count();
}