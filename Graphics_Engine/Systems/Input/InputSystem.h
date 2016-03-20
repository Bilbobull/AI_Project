// Author: Gonzalo Rojo

#pragma once

#include "../Graphics/Graphics_Headers.h"
#include "../Graphics/Context.h"
#include "../Systems.h"
#include "../Graphics/Math_Headers.h"

class InputSystem : public System
{
public:
  InputSystem(){}
  ~InputSystem(){}

  void Init(void);
  void Update(double dt);
  void Free(void);

  static void Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mode);
  void CloseWindow(void);
  static void mouseMoveEvent(GLFWwindow* window, double posX, double posY);
  static void mousePressEvent(GLFWwindow* window, int button, int action, int mode);
  static void windowResizeEvent(GLFWwindow* wnd, int w, int h);
  static void mouseEnterEvent(GLFWwindow* wnd, int state);
  static void windowIconifyEvent(GLFWwindow* window, int iconified);

private:
  static glm::vec2 _mousePosition;

};

extern InputSystem* g_InputSys;