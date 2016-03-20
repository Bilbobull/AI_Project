#pragma once
#include "Graphics_Headers.h"
#include "Math_Headers.h"
#include "Buffer_Manager.h"
#include "Texture.h"



enum Draw_Mode{
  Models,
  Shape
};

struct Vertex
{
  Vertex(){}
  Vertex(glm::vec3 pos, glm::vec3 col = glm::vec3(1.0f)) :
    position(pos),
    normal(glm::vec3(1.0f)),
    tex_coord(glm::vec2(1.0f)),
    color(col)
  {}

  bool operator<(const Vertex& rhs) const;

  glm::vec3 position;
  glm::vec3 color;
  glm::vec3 normal;
  glm::vec2 tex_coord;
};

class Mesh
{
public:

  Mesh(){}
  ~Mesh(){}
  void Draw(glm::mat4 ModelToWorld, glm::mat4 WorldToView, glm::mat4 ViewToProjection, glm::mat4 scale);
  void Debug_Draw(glm::mat4 matrix);
  static void Init_Mesh_Shader(void);

  std::vector <Vertex> vertices;
  std::vector <GLushort> triangles;
  //std::vector <GLushort> normalIndices;

  VAO* vao;
  VBO* vbo;
  EBO* ebo;
  Draw_Mode type;
  Texture* texture;
  
};

