#include "ParticleSystem.h"


ParticleArray::ParticleArray(int maxParticles) : max_Particles(maxParticles)
{
  for (int i = 0; i < max_Particles; ++i)
  {
    position.push_back(glm::vec3(0.0f));
    velocity.push_back(glm::vec3(0.0f));
    startcolor.push_back(glm::vec4(0.0f));
    endcolor.push_back(glm::vec4(0.0f));
    color.push_back(glm::vec4(0.0f));
    timeleft.push_back(1);
    alive.push_back(false);
  }
}

void ParticleArray::Wake(int index)
{
  ++alive_Particles;
  alive[index] = true;
}

void ParticleArray::Kill(int index)
{
  // This might fail
  position[index] = position[alive_Particles - 1];
  velocity[index] = velocity[alive_Particles - 1];
  startcolor[index] = startcolor[alive_Particles - 1];
  endcolor[index] = endcolor[alive_Particles - 1];
  color[index] = color[alive_Particles - 1];
  timeleft[index] = timeleft[alive_Particles - 1];
  alive[index] = alive[alive_Particles - 1];
  --alive_Particles;
}

ParticleSystem::ParticleSystem(int maxParticles) : max_Particles(maxParticles)
{
  particle_array = new ParticleArray(maxParticles);
  particle_array->alive_Particles = 0;
}

void ParticleSystem::AddEmitter(ParticleEmitter* emitter)
{
  emitters.push_back(emitter);
}

void ParticleSystem::AddUpdater(ParticleUpdater* updater)
{
  updaters.push_back(updater);
}

void ParticleSystem::AddRenderer(ParticleRenderer* render)
{
  renderer = render;
}

void ParticleSystem::Init(void)
{
  renderer->Init(this);
}

void ParticleSystem::Update(float dt)
{
  for (auto& i : emitters)
  {
    i->Emit(particle_array);
  }

  for (auto& i : updaters)
  {
    i->Update(particle_array, dt);
  }

  if (particle_array->alive_Particles == 0)
    Free();
}


void ParticleSystem::Draw(void)
{
  renderer->Render();
}


void ParticleSystem::Free(void)
{
  emitters.clear();
  updaters.clear();
}
