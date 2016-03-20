#pragma once
#include "../../Math_Headers.h"
//#include "ParticleSystem.h" // If it doesnt work comment

struct ParticleArray;  //If it doesnt work uncomment

struct ParticleUpdater
{
  virtual void Update(ParticleArray* p_array, float dt) = 0;
};

struct VelocityUpdater : ParticleUpdater
{
  virtual void Update(ParticleArray *p_array, float dt);
};

struct LifeUpdater : ParticleUpdater
{
  virtual void Update(ParticleArray *p_array, float dt);
  float m_minTime;
  float m_maxTime;
};

struct ColorUpdater : ParticleUpdater
{
  virtual void Update(ParticleArray *p_array, float dt);
};

struct TimeBombUpdater : ParticleUpdater
{
  TimeBombUpdater(double maxTime)
  {
    m_maxTime = maxTime;
    m_timeCounter = 0.0;
  }
  virtual void Update(ParticleArray *p_array, float dt);
  double m_maxTime;
  double m_timeCounter;
};
