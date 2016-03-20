#include "ParticleUpdater.h"
#include "ParticleSystem.h"

void VelocityUpdater::Update(ParticleArray *p, float dt)
{
  for (int i = 0; i < p->alive_Particles; ++i)
  {
    p->position[i] += p->velocity[i] * dt;
  }
}

void LifeUpdater::Update(ParticleArray *p_array, float dt)
{
  int end = p_array->alive_Particles;

  for (int i = 0; i < end; ++i)
  {
    p_array->timeleft[i] -= dt;
    if (p_array->timeleft[i] < 0.f)
    {
      p_array->Kill(i);
      end = p_array->alive_Particles < p_array->max_Particles ? p_array->alive_Particles : p_array->max_Particles;
    }
  }
}

void ColorUpdater::Update(ParticleArray *p, float dt)
{
  for (int i = 0; i < p->alive_Particles; ++i)
  {
    p->color[i] = glm::mix(p->startcolor[i], p->endcolor[i], p->timeleft[i]);
  }
}

void TimeBombUpdater::Update(ParticleArray *p_array, float dt)
{
  if (m_maxTime != -1.0)
  {
    int endId = p_array->alive_Particles;
    m_timeCounter += dt;
    if (m_maxTime <= m_timeCounter)
    {
      p_array->alive_Particles = 0;
    }
  }
}