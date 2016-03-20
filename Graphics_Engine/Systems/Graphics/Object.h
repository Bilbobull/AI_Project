#pragma once
#include "MeshGenerator.h"
#include <vector>

class Object
{
public:
  ~Object();
  Object(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 sca = glm::vec3(1.0f, 1.0f, 1.0f), float angle = 0.0f, glm::vec3 rot = glm::vec3(1.0f, 0.0f, 0.0f), 
    std::string filename = " ", Meshes meshtype = Meshes::Cube_Mesh);
  void Draw(void);
  
  Mesh* mesh;
  glm::vec3 position;
  float rotAngle;
  glm::vec3 rotation;
  glm::vec3 scale;

};

glm::mat4 RotateEuler(float angle, glm::vec3 v);