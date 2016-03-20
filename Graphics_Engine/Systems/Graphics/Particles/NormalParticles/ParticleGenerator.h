#pragma once
#include "../../Math_Headers.h"

struct ParticleArray;

//glm::vec3 Default_Value(float x = 0.2f, float y = 0.2f, float z = 0.2f, float w = 0.0f)
//{
//  return  glm::vec3(x, y, z);
//}

struct ParticleGenerator{
  virtual void Generate(int start, int end, ParticleArray* p_array) = 0;

private:
  glm::vec3 min_pos;
  glm::vec3 max_pos;
};

struct CircleGenerator : ParticleGenerator{
  CircleGenerator(glm::vec3 _center, glm::vec3 _radius = glm::vec3(0.2f, 0.2f, 0.2f));
  virtual void Generate(int start, int end, ParticleArray* p_array);

  glm::vec3 radius;
  glm::vec3 center;
};
// Add different generators for different effects here

struct LifeGenerator : ParticleGenerator
{
  LifeGenerator(float min = 0.1f, float max = 1.0f) : minLife(min), maxLife(max)
  {}
  virtual void Generate(int startIndex, int endIndex, ParticleArray *p);
  float minLife;
  float maxLife;
};

struct ColorGenerator : ParticleGenerator
{
  ColorGenerator(glm::vec4 minstartcolor = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f),
    glm::vec4 maxstartcolor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
    glm::vec4 minendcolor = glm::vec4(0.5f, 0.0f, 0.3f, 0.5f),
    glm::vec4 maxendcolor = glm::vec4(0.5f, 0.0f, 0.3f, 0.0f)
    )
    : m_minstartcolor(minstartcolor), m_maxstartcolor(maxstartcolor),
    m_minendcolor(minendcolor), m_maxendcolor(maxendcolor)
  {}
  virtual void Generate(int startIndex, int endIndex, ParticleArray *p);

  glm::vec4 m_minstartcolor;
  glm::vec4 m_maxstartcolor;
  glm::vec4 m_minendcolor;
  glm::vec4 m_maxendcolor;
};

struct VelocityGenerator : ParticleGenerator
{

  VelocityGenerator(glm::vec3 minVel = glm::vec3(-0.1f, -0.1f, 0.0f), glm::vec3 maxVel = glm::vec3(0.1f, 0.1f, 0.0f)) : m_minVel(minVel), m_maxVel(maxVel)
  {}
  virtual void Generate(int startIndex, int endIndex, ParticleArray *p);
  glm::vec3 m_minVel;
  glm::vec3 m_maxVel;
};
