#pragma once

enum NoteType {
	SixtyFourthNote,
	ThirtySecondNote,
	SixteenthNote,
	EigthNote,
	QuarterNote,
	DottedQuarterNote,
	HalfNote,
	DottedHalfNote,
	WholeNote,
	END_LIST
};

class NoteDuration {
	public:
		NoteDuration(){};
		NoteDuration(double beat_dt);

		void resetDurations(double newBeat_dt);
		double chooseDuration(NoteType duration);

	private:
		double get64thNote();
		double get32ndNote();
		double get16thNote();
		double get8thNote();
		double getQuarterNote();
		double getHalfNote();
		double getWholeNote();
		double getDottedQuarterNote();
		double getDottedHalfNote();

		double mBeat_dt;		
};