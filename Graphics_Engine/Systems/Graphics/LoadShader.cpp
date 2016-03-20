//Author: Gonzalo Rojo 

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include "LoadShader.h"
#include "Particles/ComputeParticles/ComputeShader.h"


std::string Read_Shader (std::string shaderSource)
{
  std::string path = "Systems/Graphics/Shaders/";
  std::string file = path + shaderSource;
  
  std::ifstream t (file.c_str());

  if (!t.good ())
  {
    throw std::string("Wrong shader filename");
  }
  else
  {
t.seekg(0, std::ios::end);
size_t size = (size_t)t.tellg();
std::string buffer(size, ' ');
t.seekg(0);
t.read(&buffer[0], size); 

    return buffer;
  }
}

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path, const char* geometry_file_path /* = nullptr*/)
{
  const char* c [1];
  std::string shaderCode;
  shaderCode = Read_Shader (vertex_file_path);
  c [0] = shaderCode.c_str ();
  
  GLuint vs = glCreateShader (GL_VERTEX_SHADER);
  glShaderSource (vs, 1, c, NULL);
  glCompileShader (vs);
  
  char log [1000];
  glGetShaderInfoLog (vs, 1000, NULL, log);
  std::cout << "Compile Status: " << vertex_file_path << log << std::endl;
  
  shaderCode = Read_Shader (fragment_file_path);
  c [0] = shaderCode.c_str ();
  
  GLuint fs = glCreateShader (GL_FRAGMENT_SHADER);
  glShaderSource (fs, 1, c, NULL);
  glCompileShader (fs);

  glGetShaderInfoLog(fs, 1000, NULL, log);
  std::cout << "Compile Status: " << fragment_file_path << log << std::endl;
  
  GLuint gs = 0;
  if (geometry_file_path != nullptr)
  {
    shaderCode = Read_Shader(geometry_file_path);
    c[0] = shaderCode.c_str();
    gs = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(gs, 1, c, NULL);
    glCompileShader(gs);

    glGetShaderInfoLog(gs, 1000, NULL, log);
    std::cout << "Compile Status: " << geometry_file_path << log << std::endl;
  }
  
  GLuint program = glCreateProgram ();
  glAttachShader (program, vs);
  glAttachShader (program, fs);
  if (geometry_file_path != nullptr)
  {
    glAttachShader(program, gs);
  }
  glLinkProgram (program);
  glGetProgramInfoLog(program, 1000, 0, log);
  std::cout << "Link Status: " << log << "\n";
  //glUseProgram (program);
  return program;
}

ComputeShaders::ComputeShader* LoadComputeShader(const char* comp_file_path)
{
  ComputeShaders::ComputeShader* cShader = new ComputeShaders::ComputeShader(comp_file_path);
  return cShader;
}
