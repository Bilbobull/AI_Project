#include "ShaderManager.h"
#include "LoadShader.h"

void ShaderManager::Upload_Shader(char* vertex, char* fragment, char* name)
{
  std::string vertexpath = ShaderPath;
  std::string fragmentpath = ShaderPath;

  vertexpath += vertex;
  fragmentpath += fragment;

  GLuint program = LoadShaders(vertexpath.c_str(), fragmentpath.c_str());
  ShaderList[name] = program;
}