#include "ShaderBufferManager.h"

namespace ComputeShaders
{

  ShaderStorageBuffer::ShaderStorageBuffer(GLuint size, GLenum mode /*= GL_STATIC_DRAW*/)
  {
    glGenBuffers(1, &bufferPos);
    BindBuffer();
    BufferData(size, NULL, mode);
  }


  void ShaderStorageBuffer::GenerateBuffer()
  {
    glGenBuffers(1, &bufferPos);
  }


  void ShaderStorageBuffer::BindBuffer(GLenum mode /*= GL_SHADER_STORAGE_BUFFER*/)
  {
    glBindBuffer(mode, bufferPos);
  }


  void ShaderStorageBuffer::BindBufferBase(GLuint index /*= 0*/)
  {
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, index, bufferPos);
  }


  void ShaderStorageBuffer::BufferData(GLuint size, const void* data /*= NULL*/, GLenum mode /*= GL_STATIC_DRAW*/)
  {
    glBufferData(GL_SHADER_STORAGE_BUFFER, size, data, mode);
  }


  void ShaderStorageBuffer::BufferSubData(GLuint size, GLuint offset, const void* data)
  {
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, size, data);
  }


  ShaderStorageBuffer::~ShaderStorageBuffer()
  {
    DeleteBuffer();
  }


  void ShaderStorageBuffer::UnMapBuffer()
  {
    glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
  }

  void ShaderStorageBuffer::UnBindBuffer()
  {
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
  }

  bool ShaderStorageBuffer::IsBuffer()
  {
    if (glIsBuffer(bufferPos))
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  void ShaderStorageBuffer::DeleteBuffer()
  {
    glDeleteBuffers(1, &bufferPos);
  }

}