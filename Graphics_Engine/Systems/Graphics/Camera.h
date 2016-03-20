#pragma once
#include "Math_Headers.h"

class Camera
{
public:
  Camera();
  ~Camera(){}
  glm::mat4 Perspective(float const & fovy, float const & aspect, float const & zNear, float const & zFar);
  glm::mat4 LookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up);

  glm::mat4 getWorldToViewMatrix(void);
  glm::mat4 getProjectionMatrix(void);
  glm::vec3 GetPosition(void){ return position; }

  void MouseUpdate(const glm::vec2& newMousePos);
  void MoveForward();
  void MoveBackWard();
  void MoveLeft();
  void MoveRight();
  void MoveUp();
  void MoveDown();

  glm::vec3 position;
  glm::vec3 viewDirection; //always one unit long
  const glm::vec3 up;
  const float near;
  const float far;
  glm::vec2 oldMousePos;
  glm::mat4 projectionMatrix;
};
 