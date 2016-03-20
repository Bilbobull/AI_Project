#include "Camera.h"
#include "GraphicsSystem.h"
#define MOVEMENT_SPEED 0.1f

glm::mat4 Camera::LookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up)
{
  glm::vec3 f = glm::normalize(center - eye);
  glm::vec3 u = glm::normalize(up);
  glm::vec3 s = glm::normalize(glm::cross(f, u));
  u = glm::cross(s, f);

  glm::mat4 Result(1);
  Result[0][0] = s.x;
  Result[1][0] = s.y;
  Result[2][0] = s.z;
  Result[0][1] = u.x;
  Result[1][1] = u.y;
  Result[2][1] = u.z;
  Result[0][2] = -f.x;
  Result[1][2] = -f.y;
  Result[2][2] = -f.z;
  Result[3][0] = -glm::dot(s, eye);
  Result[3][1] = -glm::dot(u, eye);
  Result[3][2] = glm::dot(f, eye);
  return Result;
}

Camera::Camera() : position(0.0f,3.0f,3.0f), viewDirection(0.0f, 0.0f, -1.0f), up(0.0f, 1.0f, 0.0f), near(0.1f), far(20.0f)
{
}

void Camera::MouseUpdate(const glm::vec2& newMousePos)
{
  glm::vec2 Movement = newMousePos - oldMousePos;

  //rotate X
  if (glm::length(Movement) > 50.0f)
  {
    oldMousePos = newMousePos;
    return;
  }

  const float Rotate_speed = 0.001f;

  glm::vec3 RotateArround = glm::cross(viewDirection, up);

  glm::mat4 rotator = glm::rotate(-Movement.x * Rotate_speed, up) * 
                      glm::rotate(-Movement.y * Rotate_speed, RotateArround);

  viewDirection = glm::mat3(rotator) * viewDirection;

  oldMousePos = newMousePos;
}

void Camera::MoveForward()
{
  position += MOVEMENT_SPEED * viewDirection;
}

void Camera::MoveBackWard()
{
  position -= MOVEMENT_SPEED * viewDirection;
}

void Camera::MoveLeft()
{
  glm::vec3 direction = glm::cross(viewDirection, up);
  position += -MOVEMENT_SPEED * direction;
}

void Camera::MoveRight()
{
  glm::vec3 direction = glm::cross(viewDirection, up);
  position += MOVEMENT_SPEED * direction;
}

void Camera::MoveUp()
{
  position += MOVEMENT_SPEED * up;
}

void Camera::MoveDown()
{
  position += -MOVEMENT_SPEED * up;
}

glm::mat4 Camera::getWorldToViewMatrix(void) 
{
  glm::vec3 sum = position + viewDirection;
  return LookAt(position, sum, up);
}

glm::mat4 Camera::getProjectionMatrix(void) 
{
  projectionMatrix = Perspective(90.0f, ((float)g_GraphicsSys->GetCurrentWindow().GetWidth()) / g_GraphicsSys->GetCurrentWindow().GetHeight(), near, far);
  return projectionMatrix; 
}


glm::mat4 Camera::Perspective(float const & fovy, float const & aspect, float const & zNear, float const & zFar)
{
  float range = glm::tan(glm::radians(fovy / 2.0f)) * zNear;
  float left = -range * aspect;
  float right = range * aspect;
  float bottom = -range;
  float top = range;

  glm::mat4 Result(0.0f);
  Result[0][0] = (2.0f * zNear) / (right - left);
  Result[1][1] = (2.0f * zNear) / (top - bottom);
  Result[2][2] = -(zFar + zNear) / (zFar - zNear);
  Result[2][3] = -1.0f;
  Result[3][2] = -(2.0f * zFar * zNear) / (zFar - zNear);
  return Result;
}

