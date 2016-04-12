#pragma once

class NoteDuration {
	public:
		NoteDuration(){};
		NoteDuration(double beat_dt);
		double get64thNote();
		double get32ndNote();
		double get16thNote();
		double get8thNote();
		double getQuarterNote();
		double getHalfNote();
		double getWholeNote();
		double getDottedQuarterNote();
		double getDottedHalfNote();


		void resetDurations(double newBeat_dt);

	private:
		double mBeat_dt;		
};