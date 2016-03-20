 #include "GraphicsSystem.h"
#include "Buffer_Manager.h"
#include "LoadShader.h"
#include "Math_Headers.h"
#include "../Input/InputSystem.h"
#include "Object.h"
#include "ObjectManager.h"
#include "Particles/NormalParticles/ParticleEffect.h"
#include "../Editor/Editor.h"
#include "Particles/ComputeParticles/ComputeParticleRenderer.h"
#include "Light.h"

ParticleEffect* effect;
GraphicsSystem* g_GraphicsSys;
std::string modelFile;
ComputeShaders::CS_Renderer* c;

Object* ironman;

void GraphicsSystem::Init(void)
{
  Particles = false;

  Current_Window.glfw_Init();
  glfwSetMouseButtonCallback(Current_Window.glfw_GetWindow(), g_InputSys->mousePressEvent);
  glfwSetCursorPosCallback(Current_Window.glfw_GetWindow(), g_InputSys->mouseMoveEvent);
  glfwSetWindowSizeCallback(Current_Window.glfw_GetWindow(), g_InputSys->windowResizeEvent);
  glfwSetWindowIconifyCallback(Current_Window.glfw_GetWindow(), g_InputSys->windowIconifyEvent);
  //glfwSetCursorEnterCallback(Current_Window.glfw_GetWindow(), mouseEnterEvent);

  g_GraphicsSys = this;

  glEnable(GL_DEPTH_TEST);
 
  Mesh::Init_Mesh_Shader();

  //Object* arrow = ObjectManager::CreateObject(glm::vec3(-2.0f, 0.0f, -3.0f), glm::vec3(-2.0f, 0.0f, -3.0f), 50.0f, glm::vec3(1.0f, 0.0f, 0.0f), " ", Arrow_Mesh );
  //Object* cube = ObjectManager::CreateObject(glm::vec3(-2.0f, 0.0f, -10.0f), glm::vec3(-2.0f, 0.0f, -3.0f), 50.0f, glm::vec3(1.0f, 0.0f, 0.0f));
  //modelFile = "Cube";
  ironman = ObjectManager::CreateObject(glm::vec3(0.0f, 0.5f, -3.0f), glm::vec3(10.0f, 10.0f, 10.0f), 0.0f, glm::vec3(1.0f, 0.0f, 0.0f), "ironman");
  //Object* pyro = ObjectManager::CreateObject(glm::vec3(-4.0f, 0.5f, -3.0f), glm::vec3(-2.0f, 0.0f, -3.0f), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f), "Ironman");

 // effect = new CircleEffect(glm::vec3(0, 0, -3), 100);
 // effect->Init();
  //c = new ComputeShaders::CS_Renderer();
  //c->Initialize();

  ImGuiImpl::Initialize(Current_Window.GetWidth(), Current_Window.GetHeight());

  MaterialVal.ambient = glm::vec4(0, 0, 0, 1);
  MaterialVal.diffuse = glm::vec4(0.8, 0.8, 0.8, 1);
  MaterialVal.specular = glm::vec4(1, 1, 1, 1);
  MaterialVal.emisive = glm::vec4(0, 0, 0, 1);
  Lighttype[0] = POINT;
  Lightposition[0] = glm::vec4(-0.3f, 0.5f, -0.5f, 1.0f);
  Lightdirection[0] = glm::vec4(0.3f, -0.5f, 0.5f, 1.0f);
  Lightambient[0] = glm::vec4(0, 0, 0, 1);
  Lightdiffuse[0] = glm::vec4(0.8, 0.8, 0.8, 1);
  Lightspecular[0] = glm::vec4(1, 1, 1, 1);
  Lightinner[0] = 15.0f* 2.0f * PI / 360.0f;
  Lightouter[0] = 30.0f* 2.0f * PI / 360.0f;
  Lightfalloff[0] = 1;
  DistanceAttConstants[0] = 1.0f;
  DistanceAttConstants[1] = 0.1f;
  DistanceAttConstants[2] = 0.0f;
  glm::vec3 temppos = glm::vec3(Lightposition[LightNum - 1].x, Lightposition[LightNum - 1].y, Lightposition[LightNum - 1].z);

  Object* obj = new Object(temppos, glm::vec3(0.25f));
  LightObjects.push_back(obj);


}

void GraphicsSystem::Update(double dt)
{
  if (!(GetCurrentWindow().GetMinimized()))
  {
    ImGui::NewFrame();
    ImGui::Begin("Editor");
    ImGuiImpl::UpdateGuiButtons();
  }


  glClearColor(0.3f, 0.3f, 0.3f, 0.3f);
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

  ////glViewport(0, 0, Current_Window.GetWidth(), Current_Window.GetHeight()); // Still need to do it

  if (glfwGetKey(GetCurrentWindow().glfw_GetWindow(), GLFW_KEY_P) == GLFW_PRESS)
  {
    ironman->rotation = glm::vec3(0.0f, 1.0f, 0.0f);
    ironman->rotAngle += 0.5f;
  }

  auto objectList = ObjectManager::GetObjectList();
  for (auto it : objectList)
  {
    it->Draw();
  }

  //if (LightRotation)
  //{
  //  RotateLights();
  //}

  //for (auto it : LightObjects)
  //{
  //  it->Draw();
  //}


  //ironman->Draw();

  if (Particles)
  {
  //  //effect->Update(0.016f);
  //  //effect->Draw();
    if (ResetParticles)
    {
      ResetParticles = false;
      delete c;
      c = new ComputeShaders::CS_Renderer();
      c->Initialize();
    }
    c->Draw();
  }


  if (!(GetCurrentWindow().GetMinimized()))
  {
    ImGui::End();
    ImGuiImpl::Render();
  }

  glfwSwapBuffers(Current_Window.glfw_GetWindow());
}

void GraphicsSystem::Free(void)
{
  ObjectManager::Free();
}

Window& GraphicsSystem::GetCurrentWindow(void)
{
  return Current_Window;
}

void GraphicsSystem::SetBackgroundColor(float r /*= 1.0f*/, float g /*= 1.0f*/, float b /*= 1.0f*/, float a /*= 1.0f*/)
{
  glClearColor(r, g, b, a);
}

Camera& GraphicsSystem::GetCurrentCamera(void)
{
  return My_Camera;
}

glm::vec3 GraphicsSystem::Random_Color(void)
{
  glm::vec3 color;
  color.x = rand() / (float)RAND_MAX;
  color.y = rand() / (float)RAND_MAX;
  color.z = rand() / (float)RAND_MAX;
  return color;
}




