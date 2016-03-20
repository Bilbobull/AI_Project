#ifndef _PARTICLEMANAGER_
#define _PARTICLEMANAGER_

#ifndef _GLEW_
#define _GLEW_
	#include <GL\glew.h>
	#include <GLFW\glfw3.h>
#endif

#include <random>
#include <stdexcept>
#include <iostream>
#include <utility>
#include "BufferBaseModel.h"
#include "ComputeParticle.h"

#ifndef _MSC_VER
#define NOEXCEPT noexcept
#else
#define NOEXCEPT
#endif

namespace ComputeParticles
{
  class ParticleManager
  {
  private:
    BufferBaseModel		_bufferData;

    void setParticles(ComputeParticle* particles, int numParticles, int iniRadius);
    void deleteParticleManager();

  public:
    ~ParticleManager()
    {
      deleteParticleManager();
    }

    void loadParticleBuffer(int numParticles, int iniRadius);

    void loadUintUniform(GLuint shaderProgramID, const std::string& name, GLuint value);
    void loadFloatUniform(GLuint shaderProgramID, const std::string& name, GLfloat value);
    void loadVec4Uniform(GLuint shaderProgramID, const std::string& name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    void loadMatrix4Uniform(GLuint shaderProgramID, const std::string& name, const GLfloat* value);

    GLuint getParticleBufferID() const;
  };
}

#endif