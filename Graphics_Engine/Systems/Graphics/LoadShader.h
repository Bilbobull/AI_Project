// Author: Gonzalo Rojo
#pragma once

#include "Graphics_Headers.h"

template <class T> const T& max (const T& a, const T& b) {
  return (a<b)?b:a;     // or: return comp(a,b)?b:a; for version (2)
}

namespace ComputeShaders
{
  class ComputeShader;
}

GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path, const char* geom_file_path = 0);
ComputeShaders::ComputeShader* LoadComputeShader(const char* comp_file_path);
