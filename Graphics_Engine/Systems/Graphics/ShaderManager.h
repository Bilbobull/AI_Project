#pragma once
#include <map>
#include "Graphics_Headers.h"

class ShaderManager{
public:
  ShaderManager()
  {
    ShaderPath = "Shaders/";
  }
  ~ShaderManager()
  {
    Unload_Shaders();
  }

  void Upload_Shader(char* vertex, char* fragment, char* name);
  void Unload_Shaders(void);
private:
  std::map <std::string, GLuint> ShaderList;
  std::string ShaderPath;
};