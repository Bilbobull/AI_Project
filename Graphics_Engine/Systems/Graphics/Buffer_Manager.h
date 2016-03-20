// Author: Gonzalo Rojo

#pragma once

#include "Graphics_Headers.h"
#include <vector>

class VertexArrayObject
{
public:
  VertexArrayObject(void)
  {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
  }

  ~VertexArrayObject(void)
  {
    glDeleteVertexArrays(1, &vao);
    vao = 0;
  }

  void Bind(void)
  {
    glBindVertexArray(vao);
  }

  void unBind(void)
  {
    glBindVertexArray(0);
  }

private:
  GLuint vao;
};


class VertexBufferObject
{
public:
  VertexBufferObject(void)
  {
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 0, 0, GL_STREAM_DRAW);
  }

  ~VertexBufferObject(void)
  {
    glDeleteBuffers(1, &vbo);
    vbo = 0;
  }

  VertexBufferObject(int size, void* data)
  {
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STREAM_DRAW);

    Num_Vertices = (size / 2) / sizeof(float);
  }

  void Bind(void)
  {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
  }

  void unBind(void)
  {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  void Add_Data(float* data, GLuint size)
  {
    Data.insert(Data.end(), data, data + size);
  }

  void Upload_Data(GLenum mode)
  {
    this->Bind();
    glBufferData(GL_ARRAY_BUFFER, Data.size() * sizeof(float), Data.data(), mode);
    Data.clear();
    this->unBind();
  }

  void Add_Buffer_Data(int size, void* data)
  {
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STREAM_DRAW);
  }

  int Get_Data_Size(void)
  {
    return Data.size();
  }

  int Get_Vertice_Count(void)
  {
    return Num_Vertices;
  }

private:
  GLuint vbo;
  int Num_Vertices;
  std::vector <float> Data;
};


class ElementBufferObject
{
public:
  ElementBufferObject(int size, GLushort* data)
  {
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, (const void*)data, GL_STATIC_DRAW);
  }

  ~ElementBufferObject()
  {
    glDeleteBuffers(1, &ebo);
    ebo = 0;
  }

  void Bind(void)
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  }

  void unBind(void)
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }


private:
  GLuint ebo;
};

class FrameBufferObject
{
public:
  FrameBufferObject(void)
  {
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
  }

  ~FrameBufferObject()
  {
    glDeleteFramebuffers(1, &fbo);
    fbo = 0;
  }

  void Bind(void)
  {
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
  }

  void unBind(void)
  {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }

  void Texture2D(GLuint texture)
  {
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
  }

private:
  GLuint fbo;
};

typedef VertexArrayObject VAO;
typedef VertexBufferObject VBO;
typedef ElementBufferObject EBO;
typedef FrameBufferObject FBO;