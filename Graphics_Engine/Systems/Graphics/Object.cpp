#include "Object.h"
#include "GraphicsSystem.h"

glm::mat4 RotateEuler(float angle, glm::vec3 v)
{
  glm::mat4 const m(1);

  float ang = (float)angle * PI / 180.0f;
  float a = ang;
  float c = cos(a);
  float s = sin(a);

  glm::vec3 axis = glm::normalize(v);

  glm::vec3 temp = ((1) - c) * axis;

  glm::mat4 Rotate(glm::mat4::null);
  Rotate[0][0] = c + temp[0] * axis[0];
  Rotate[0][1] = 0 + temp[0] * axis[1] + s * axis[2];
  Rotate[0][2] = 0 + temp[0] * axis[2] - s * axis[1];

  Rotate[1][0] = 0 + temp[1] * axis[0] - s * axis[2];
  Rotate[1][1] = c + temp[1] * axis[1];
  Rotate[1][2] = 0 + temp[1] * axis[2] + s * axis[0];

  Rotate[2][0] = 0 + temp[2] * axis[0] + s * axis[1];
  Rotate[2][1] = 0 + temp[2] * axis[1] - s * axis[0];
  Rotate[2][2] = c + temp[2] * axis[2];

  glm::mat4 Result(glm::mat4::null);
  Result[0] = m[0] * Rotate[0][0] + m[1] * Rotate[0][1] + m[2] * Rotate[0][2];
  Result[1] = m[0] * Rotate[1][0] + m[1] * Rotate[1][1] + m[2] * Rotate[1][2];
  Result[2] = m[0] * Rotate[2][0] + m[1] * Rotate[2][1] + m[2] * Rotate[2][2];
  Result[3] = m[3];
  return Result;
}

Object::Object(glm::vec3 pos, glm::vec3 sca, float angle, glm::vec3 rot, std::string filename, Meshes meshtype)
{
  mesh = MeshGenerator::Create_Shape(filename, meshtype);
  position = pos;
  rotation = rot;
  rotAngle = angle;
  scale = sca;
}

void Object::Draw(void)
{
  // If u do translation before rotation then it rotates around the center of the world
  // instead of around the center of the object

  // projection * translation * rotation
  glm::mat4 Scale = glm::scale(scale);
  glm::mat4 ModelToWorld =  glm::translate(position) * RotateEuler(rotAngle, rotation); 
  glm::mat4 WorldToView = g_GraphicsSys->GetCurrentCamera().getWorldToViewMatrix();
  glm::mat4  ViewToProjection = g_GraphicsSys->GetCurrentCamera().getProjectionMatrix();
  mesh->Draw(ModelToWorld, WorldToView, ViewToProjection, Scale);
}

Object::~Object()
{
  delete mesh;
}