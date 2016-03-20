#pragma once
#include <vector>

struct ParticleGenerator;
struct ParticleArray;

class ParticleEmitter{
public:
  ParticleEmitter();
  void AddGenerator(ParticleGenerator* generator);
  void Emit(ParticleArray* p_array);
  int min_Particles;

private:
  std::vector <ParticleGenerator*> generators;
};