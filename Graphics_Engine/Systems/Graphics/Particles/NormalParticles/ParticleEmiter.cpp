#include "ParticleEmiter.h"
#include "ParticleSystem.h"
#include <algorithm>

ParticleEmitter::ParticleEmitter()
{
  min_Particles = 100;
}

void ParticleEmitter::AddGenerator(ParticleGenerator* generator)
{
  generators.push_back(generator);
}

void ParticleEmitter::Emit(ParticleArray* p_array)
{
  unsigned start = p_array->alive_Particles;
  unsigned end = std::min(p_array->alive_Particles + int(min_Particles), p_array->max_Particles - 1);

  for (auto& it : generators)
    it->Generate(start, end, p_array);

  for (unsigned i = start; i < end; ++i)
    p_array->Wake(i);
}
