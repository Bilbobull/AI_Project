#pragma once
#include "../Systems.h"
#include <chrono>

class BPM{
  public:
    BPM(int tempo = 40);

    void Init(void);
    void Update(double dt);

  //  bool isBeat();
		//void resetTimer();
		void setTempo(int tempo = 40);
		int getTempo();
		double getDT();
		double timePassed();

  private:
    int mTempo;
    double mDT;
		std::chrono::time_point<std::chrono::system_clock> mStart;
		std::chrono::time_point<std::chrono::system_clock> mCurrentFrame;
		bool mBeat;
		std::chrono::duration<double> mTimePassed;
};