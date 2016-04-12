#pragma once
#include "../Systems.h"
#include <chrono>

class BPM : public System{
  public:
    BPM(int tempo = 40);

    void Init(void);
    void Update(double dt);
    void Free(void);

    bool isBeat();
		void resetTimer();
		void setTempo(int tempo = 40);
		int getTempo();
		double getDT();

  private:
    int mTempo;
    double mDT;
		std::chrono::time_point<std::chrono::system_clock> mStart;
		bool mBeat;
};