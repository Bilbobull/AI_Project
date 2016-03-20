#pragma once


#include "Shader.h"

namespace ComputeShaders
{

  class ComputeShader : public Shader
  {
  public:
    ComputeShader(const char* cs);
    ~ComputeShader();

    GLuint Create_Program(std::string name, GLuint _computeShader);

    inline void Dispatch_Compute(GLuint workGroups_x, GLuint workGroups_y, GLuint workGroups_z)
    {
      glDispatchCompute(workGroups_x, workGroups_y, workGroups_z);
    }

  private:
    GLuint computeShader;
  };
}