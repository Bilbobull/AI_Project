#include "NoteDuration.h"
#include "BPM.h"

NoteDuration::NoteDuration(double beat_dt){


}

double NoteDuration::get64thNote() {
	return mBeat_dt / 16.0;
}

double NoteDuration::get32ndNote() {
	return mBeat_dt / 8.0;
}

double NoteDuration::get16thNote() {
	return mBeat_dt / 4.0;
}

double NoteDuration::get8thNote() {
	return mBeat_dt / 2.0;
}

double NoteDuration::getQuarterNote() {
	return mBeat_dt;
}

double NoteDuration::getDottedQuarterNote() {
	return mBeat_dt * 1.5;
}

double NoteDuration::getHalfNote() {
	return mBeat_dt * 2;
}

double NoteDuration::getDottedHalfNote() {
	return mBeat_dt * 3;
}

double NoteDuration::getWholeNote() {
	return mBeat_dt * 4;
}

void NoteDuration::resetDurations(double newBeat_dt) {
	mBeat_dt = newBeat_dt;
}