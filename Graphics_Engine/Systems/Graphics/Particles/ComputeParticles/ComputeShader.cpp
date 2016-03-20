#include "ComputeShader.h"
#include <iostream>

namespace ComputeShaders
{
  ComputeShader::ComputeShader(const char* cs)
  {
    computeShader = Create_Shader(cs, GL_COMPUTE_SHADER);
    Create_Program("", computeShader);
  }


  ComputeShader::~ComputeShader()
  {
    glDetachShader(shaderProgram, computeShader);
    glDeleteShader(computeShader);
    glDeleteProgram(shaderProgram);
  }

  GLuint ComputeShader::Create_Program(std::string name, GLuint _computeShader /*= 0*/)
  {
    GLuint program = glCreateProgram();
    glAttachShader(program, computeShader);
    glLinkProgram(program);

    char log[1000];
    glGetProgramInfoLog(program, 1000, 0, log);
    std::cout << "\n" << name << "\nLink Status...\n" << log << "\n--------------" << std::endl;

    shaderProgram = program;
    computeShader = _computeShader;

    return shaderProgram;
  }

}