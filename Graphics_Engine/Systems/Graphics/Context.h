// Author : Gonzalo Rojo 

#pragma once

#include "Graphics_Headers.h"
#include <string>

class Window
{
public:
  Window();
  ~Window();

  Window(Window&) = delete;
  void operator= (Window&) = delete;

  void sdl_Init();
  bool sdl_WindowShouldClose();

  void glfw_Init();
  GLFWwindow* glfw_GetWindow();
  int GetWidth(){ return Width; }
  int GetHeight(){ return Height; }
  static void glfw_WindowShouldClose();

  void Minimize(void){ Minimized = !Minimized; }
  void SetMinimize(bool yesorno){ Minimized = yesorno; }
  bool GetMinimized(void){ return Minimized; }

  void SetName(std::string title = "Graphics Engine");
 
private:
  //SDL_Window  *sdl_window;
  int major_;
  int minor_;

  const GLFWvidmode* Desktop;
  GLFWwindow* glfw_window;

  std::string name;
  int Width;
  int Height;
  bool FullScreen = false;
  bool Minimized = false;
};
