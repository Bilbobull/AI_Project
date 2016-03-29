#pragma once
#include "../Systems.h"

class BPM : public System{
  public:
    BPM(int tempo) {};

    void Init(void);
    void Update(double dt);
    void Free(void);

    bool isOnBeat();

  private:
    int mTempo;
    double dt;
};