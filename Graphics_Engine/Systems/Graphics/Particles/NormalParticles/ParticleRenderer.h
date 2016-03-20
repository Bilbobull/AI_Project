#pragma once
#include "../../Buffer_Manager.h"
//#include "ParticleSystem.h" // may not work, in that case comment

class ParticleSystem;  //in case it doenst work, uncomment

class ParticleRenderer{
public:
  ParticleRenderer(){}
  ~ParticleRenderer(){}

  void Init(ParticleSystem* sys);
  void Render();
  void Specify_Attributes();

private:
  ParticleSystem* p_sys;
  VAO vao;
  GLuint vbo_pos;
  GLuint vbo_col;
};