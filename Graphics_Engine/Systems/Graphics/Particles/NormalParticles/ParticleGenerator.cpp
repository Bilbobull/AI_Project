#include "ParticleGenerator.h"
#include "ParticleSystem.h"

#define M_PI 3.1415f

CircleGenerator::CircleGenerator(glm::vec3 _center, glm::vec3 _radius /*= Default_Value()*/)
{
  center = _center;
  radius = _radius;
}

void CircleGenerator::Generate(int start, int end, ParticleArray* p_array)
{
  double ang = glm::linearRand(0.0, 2.0 * M_PI);

  // Check Z value, might be incorrect
  for (int i = start; i < end; ++i)
    p_array->position[i] = center + glm::vec3(radius.x * sin(ang), radius.y * cos(ang), radius.z * tan(ang));

}

void ColorGenerator::Generate(int startIndex, int endIndex, ParticleArray *p)
{
  for (int i = startIndex; i < endIndex; ++i)
  {
    p->startcolor[i] = glm::linearRand(m_minstartcolor, m_maxstartcolor);
    p->endcolor[i] = glm::linearRand(m_minendcolor, m_maxendcolor);
  }
}

void LifeGenerator::Generate(int startIndex, int endIndex, ParticleArray *p)
{
  for (int i = startIndex; i < endIndex; ++i)
  {
    p->timeleft[i] = glm::linearRand(minLife, maxLife);
  }
}

void VelocityGenerator::Generate(int startIndex, int endIndex, ParticleArray *p)
{
  for (int i = startIndex; i < endIndex; ++i)
  {
    p->velocity[i] = glm::linearRand(m_minVel, m_maxVel);
  }
}
