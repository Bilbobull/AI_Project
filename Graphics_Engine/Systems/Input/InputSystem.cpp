//Author: Gonzalo Rojo

#include "InputSystem.h"
#include "../Graphics/GraphicsSystem.h"
#include "../Editor/Editor.h"

extern bool Running;
InputSystem* g_InputSys;
bool moving;


void InputSystem::Init(void)
{
  moving = false;
  g_InputSys = this;
  glfwSetKeyCallback(g_GraphicsSys->GetCurrentWindow().glfw_GetWindow(), (GLFWkeyfun)Key_Callback);
}

void InputSystem::Update(double dt)
{ 
  glfwPollEvents();
}

void InputSystem::Free(void)
{
  g_InputSys = nullptr;
}

void InputSystem::Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{

    switch (key)
    {
    case GLFW_KEY_ESCAPE:
      g_InputSys->CloseWindow();
      break;

    case GLFW_KEY_W:
      g_GraphicsSys->GetCurrentCamera().MoveForward();
      break;

    case GLFW_KEY_S:
      g_GraphicsSys->GetCurrentCamera().MoveBackWard();
      break;

    case GLFW_KEY_A:
      g_GraphicsSys->GetCurrentCamera().MoveLeft();
      break;

    case GLFW_KEY_D:
      g_GraphicsSys->GetCurrentCamera().MoveRight();
      break;

    case GLFW_KEY_E:
      g_GraphicsSys->GetCurrentCamera().MoveUp();
      break;

    case GLFW_KEY_Q:
      g_GraphicsSys->GetCurrentCamera().MoveDown();
      break;

    case GLFW_KEY_5:
      if (action == GLFW_PRESS)
      {
        g_GraphicsSys->DebugDraw();
        if (!g_GraphicsSys->GetDebugDraw())
        {
          if (g_GraphicsSys->GetFaceNormalDraw())
            g_GraphicsSys->FaceNormalDraw();

          if (g_GraphicsSys->GetVertexNormalDraw())
            g_GraphicsSys->VertexNormalDraw();
        }
      }
    
      break;

    case GLFW_KEY_4:
      if (action == GLFW_PRESS && g_GraphicsSys->GetDebugDraw())
      {
        g_GraphicsSys->VertexNormalDraw();
        if (g_GraphicsSys->GetFaceNormalDraw())
          g_GraphicsSys->FaceNormalDraw();
      }
      
      break;

    case GLFW_KEY_3:
      if (action == GLFW_PRESS && g_GraphicsSys->GetDebugDraw())
      {
        g_GraphicsSys->FaceNormalDraw();
        if (g_GraphicsSys->GetVertexNormalDraw())
          g_GraphicsSys->VertexNormalDraw();
      }
      break;

    }

    if (action == GLFW_RELEASE)
    {
      ImGuiImpl::KeyboardUp(key, (int)_mousePosition.x, (int)_mousePosition.y);
    }
    else
    {
      ImGuiImpl::KeyboardDown(key, (int)_mousePosition.x, (int)_mousePosition.y);
    }
}

void InputSystem::CloseWindow(void)
{
  Running = false;
}

void InputSystem::mouseMoveEvent(GLFWwindow* window, double x, double y)
{
  if (!ImGui::IsMouseHoveringAnyWindow())
  if (moving)
    g_GraphicsSys->GetCurrentCamera().MouseUpdate(glm::vec2(x, y));

  _mousePosition = glm::vec2(x, y);
  ImGuiImpl::Motion(_mousePosition.x, _mousePosition.y);
}

void InputSystem::mousePressEvent(GLFWwindow* window, int button, int action, int mode)
{
  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    moving = true;

  else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    moving = false;

  ImGuiImpl::Mouse(button, action, _mousePosition.x, _mousePosition.y);
}

void InputSystem::windowResizeEvent(GLFWwindow* wnd, int w, int h)
{
  ImGuiImpl::Reshape(w, h);
}

void InputSystem::mouseEnterEvent(GLFWwindow* wnd, int state)
{
  ImGuiImpl::Entry(state);
}

void InputSystem::windowIconifyEvent(GLFWwindow* window, int iconified)
{
  if (iconified)
    g_GraphicsSys->GetCurrentWindow().SetMinimize(true);

  else
    g_GraphicsSys->GetCurrentWindow().SetMinimize(false);
}

glm::vec2 InputSystem::_mousePosition;

