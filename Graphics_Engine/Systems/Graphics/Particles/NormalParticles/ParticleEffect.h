#pragma once
#include "ParticleSystem.h"

struct ParticleEffect
{
  ParticleEffect(){}
  
  virtual void Init() {}
  virtual void Update(float dt) {}
  virtual void Draw() {}
  virtual void Free() {}
};

class CircleEffect : public ParticleEffect
{
public:
  CircleEffect(glm::vec3 pos, int ParticleCount = 1000, double maxTime = -1.0,
    glm::vec4 minstartcolor = glm::vec4(1.0f, 0.3f, 0.0f, 0.0f),
    glm::vec4 maxstartcolor = glm::vec4(1.0f, 0.3f, 0.0f, 1.0f),
    glm::vec4 minendcolor = glm::vec4(0.3f, 1.0f, 0.0f, 0.5f),
    glm::vec4 maxendcolor = glm::vec4(0.3f, 1.0f, 0.3f, 0.0f),
    bool OnOrOff = true)
  {
    min_startcol = minstartcolor;
    max_startcol = maxstartcolor;
    min_endcol = minendcolor;
    max_endcol = maxendcolor;
    m_particlecount = ParticleCount;
    m_maxTime = maxTime;
    position = pos;
    YesOrNo = OnOrOff;
  }

  virtual void Init();
  virtual void Update(float dt);
  virtual void Draw();
  virtual bool OnOrOff() { return YesOrNo; }
  virtual void SetBool(bool boolean) { YesOrNo = boolean; }

  ParticleSystem *p_sys;
  int m_particlecount;
  double m_maxTime;
  glm::vec3 position;
  glm::vec4 min_startcol;
  glm::vec4 max_startcol;
  glm::vec4 min_endcol;
  glm::vec4 max_endcol;
  bool YesOrNo;
};