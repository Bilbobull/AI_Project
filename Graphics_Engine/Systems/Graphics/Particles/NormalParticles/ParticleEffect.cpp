#include "ParticleEffect.h"

void CircleEffect::Init()
{
  p_sys = new ParticleSystem(m_particlecount);
  ParticleEmitter* emitter = new ParticleEmitter();

  LifeUpdater* l_updater = new LifeUpdater();
  ColorUpdater* c_updater = new ColorUpdater();
  TimeBombUpdater* tb_updater = new TimeBombUpdater(m_maxTime);
  VelocityUpdater* v_updater = new VelocityUpdater();

  ParticleRenderer* renderer = new ParticleRenderer();

  glm::vec3 maxOff = glm::vec3(0.5f, 0.5f, 0.5f);
  glm::vec3 radius = glm::vec3(1.f, 1.f, 1.0f);
  CircleGenerator *rpg = new CircleGenerator(position, radius);
  VelocityGenerator* vg = new VelocityGenerator(glm::vec3(-0.4f, -0.4f, -0.2f), glm::vec3(0.4f, 0.4f, 0.2f));
  ColorGenerator* cg = new ColorGenerator(min_startcol, max_startcol, min_endcol, max_endcol);
  LifeGenerator* lg = new LifeGenerator(0.75f, 3.0f);

  emitter->min_Particles = p_sys->GetMaxParticles() / 2;
  emitter->AddGenerator(rpg);
  emitter->AddGenerator(lg);
  emitter->AddGenerator(cg);
  emitter->AddGenerator(vg);

  p_sys->AddEmitter(emitter);

  p_sys->AddUpdater(l_updater);
  p_sys->AddUpdater(c_updater);
  p_sys->AddUpdater(tb_updater);
  p_sys->AddUpdater(v_updater);

  p_sys->AddRenderer(renderer);


  p_sys->Init();
}

void CircleEffect::Update(float dt)
{
  p_sys->Update(dt);
}

void CircleEffect::Draw()
{
  p_sys->Draw();
}
