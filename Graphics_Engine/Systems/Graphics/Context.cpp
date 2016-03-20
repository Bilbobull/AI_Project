// Author : Gonzalo Rojo 

#include "Context.h"
#include "..\Input\InputSystem.h"
#include <iostream>

//SDL_Event Event;
//
Window::Window(void)
{
  Desktop = nullptr;
  glfw_window = nullptr;

  //sdl_window = 0;
  major_ = 0;
  minor_ = 0;

  name = "Graphics Engine";
}
//
//void Window::sdl_Init(void)
//{
//  SDL_GLContext opengl3_context;
//
//  SDL_Init(SDL_INIT_VIDEO);
//
//  //// set the opengl context version
//  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
//  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
//
//  // create the sdl2 window
//  sdl_window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED,
//                                 SDL_WINDOWPOS_CENTERED, 512, 512,
//                                 SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
//
//  // create the opengl3 context
//  opengl3_context = SDL_GL_CreateContext(sdl_window);
//
//  SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &major_);
//  SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &minor_);
//
//
//  std::cout << "OpenGL Version: " << major_ << "." << minor_ << std::endl;
//
//  GLenum status = glewInit();
//  if (status != GLEW_OK)
//  {
//    std::cerr << "GLEW Error: " << glewGetErrorString(status) << "\n";
//  }
//}
//
//bool Window::sdl_WindowShouldClose()
//{
//  if(SDL_PollEvent(&Event))
//  {
//    if (Event.type == SDL_QUIT)
//      return true;
//  }
//
//  return false;
//}

void Window::glfw_Init()
{
  if (!glfwInit())
  {
    std::cout << "Error initializing GLFW" << std::endl;
    exit(-1);
  }

  glfwWindowHint(GLFW_RESIZABLE, 0);
  glfwWindowHint(GLFW_SAMPLES, 4);
 
  glEnable(GL_MULTISAMPLE);
  
  GLFWmonitor* Monitor = glfwGetPrimaryMonitor();
  Desktop = glfwGetVideoMode(Monitor);


  if (FullScreen)
  {
    Width = Desktop->width;
    Height = Desktop->height;
  }
  else
  {
    Width = Desktop->width;
    Height = Desktop->height - 100;
  }

 // glfw_window = glfwCreateWindow(Width, Height, name.c_str(), Monitor, nullptr);
  glfw_window = glfwCreateWindow(Width, Height, name.c_str(), nullptr, nullptr);

  if (!glfw_window)
    throw std::string("Error Creating Window\n");

  glfwMakeContextCurrent(glfw_window);
  glewExperimental = true;

  if (glewInit() != GLEW_OK)
  {
    std::cout << "Error initializing GLEW" << std::endl;
    exit(-1);
  }

  glViewport(0, 0, Width, Height);
  glfwSetInputMode(glfw_window, GLFW_STICKY_KEYS, GL_TRUE);
  glfwSetWindowCloseCallback(glfw_GetWindow(), (GLFWwindowclosefun) glfw_WindowShouldClose);
}

GLFWwindow* Window::glfw_GetWindow()
{
  return glfw_window;
}

void Window::glfw_WindowShouldClose()
{
  g_InputSys->CloseWindow();
}

Window::~Window()
{
  glfwTerminate();
}
