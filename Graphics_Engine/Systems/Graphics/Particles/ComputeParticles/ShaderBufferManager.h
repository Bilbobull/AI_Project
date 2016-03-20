#pragma once

#include "../../Graphics_Headers.h"

namespace ComputeShaders
{

  class ShaderStorageBuffer
  {
  public:
    ShaderStorageBuffer::ShaderStorageBuffer() : bufferPos(0) {}
    ShaderStorageBuffer(GLuint size, GLenum mode = GL_STATIC_DRAW);
    ~ShaderStorageBuffer();

    void GenerateBuffer();
    void BindBuffer(GLenum mode = GL_SHADER_STORAGE_BUFFER);
    void BindBufferBase(GLuint index = 0);
    void BufferData(GLuint size, const void* data = NULL, GLenum mode = GL_STATIC_DRAW);
    void BufferSubData(GLuint size, GLuint offset, const void* data);

    template <typename T>
    T* MapBufferRange(int offset, int size)
    {
      return (T*)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, offset * sizeof(T), size * sizeof(T), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
    }
    void UnMapBuffer();
    void UnBindBuffer();
    void DeleteBuffer();

    inline GLuint Get_POS()
    {
      return bufferPos;
    }
    bool IsBuffer();
  private:
    GLuint bufferPos;
  };

  typedef ShaderStorageBuffer SSBO;

}