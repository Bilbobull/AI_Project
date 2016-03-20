#include "ComputeParticleRenderer.h"
#include "../../GraphicsSystem.h"
#include "../../Camera.h"
#include "../../LoadShader.h"

namespace ComputeShaders
{
  static bool ChangeColors = true;

  static double MousePosX = 0, MousePosY = 0;

  static float timepassed = 1.0f;


  CS_Renderer::CS_Renderer()
  {
    NumParticles = 100000;
    startcolor = glm::linearRand(glm::vec3(1.0f, 0.2f, 0.2f), glm::vec3(0.7f, 0.3f, 0.1f));
    endcolor = glm::linearRand(glm::vec3(0.3f, 0.7f, 0.4f), glm::vec3(0.1f, 0.8f, 0.5f));
  }

  CS_Renderer::~CS_Renderer()
  {
    delete Posbuffer, VelBuffer, vao;
    Posbuffer = nullptr;
    VelBuffer = nullptr;
    vao = nullptr;
  }

  void CS_Renderer::Initialize()
  {
    CreateBuffers();
    if (!shader && !computeshader && !texture)
    {
      InitShaders();
      LoadTexture();
    }
  }

  void CS_Renderer::Draw()
  {

    vao->Bind();
    Posbuffer->BindBufferBase(0);
    VelBuffer->BindBufferBase(1);
    AccBuffer->BindBufferBase(2);

    double StartTime = glfwGetTime();

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);


    int windowWidth, windowHeight;
    glfwGetCursorPos(g_GraphicsSys->GetCurrentWindow().glfw_GetWindow(), &MousePosX, &MousePosY);
    glfwGetWindowSize(g_GraphicsSys->GetCurrentWindow().glfw_GetWindow(), &windowWidth, &windowHeight);

    destPos.x = (float)(MousePosX / (windowWidth)-0.5f) * 2.0f;
    destPos.y = (float)((windowHeight - MousePosY) / windowHeight - 0.5f) * 2.0f;

    computeshader->Use();
    computeshader->uni1f("dTime", 10 * 0.1f);
    computeshader->uni3f("destPos", destPos.x, destPos.y, 0);
    computeshader->uni1f("et", (float)glfwGetTime());

    int workingGroups = NumParticles / 16;

    computeshader->Dispatch_Compute(workingGroups + 2, 1, 1);
    computeshader->Disable();

    glMemoryBarrier(GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT);
    glUseProgram(shader);
    GLuint colLocation = glGetUniformLocation(shader, "Color");
    glUniform4f(colLocation, colVec.x, colVec.y, colVec.z, 1.0f);
    glEnable(GL_PROGRAM_POINT_SIZE);
    texture->TexBind();
    glUniform1i(glGetUniformLocation(shader, "image"), 0);
    GLuint posAttrib = glGetAttribLocation(shader, "position");
    glm::mat4 mvp = g_GraphicsSys->GetCurrentCamera().getProjectionMatrix() * g_GraphicsSys->GetCurrentCamera().getWorldToViewMatrix();
    glUniformMatrix4fv(glGetUniformLocation(shader, "mvp"), 1, GL_FALSE, glm::value_ptr(mvp));
    glBindBuffer(GL_ARRAY_BUFFER, Posbuffer->Get_POS());
    glVertexAttribPointer(posAttrib, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(posAttrib);

    glPointSize(1);
    glDrawArrays(GL_POINTS, 0, NumParticles);

    texture->unBind();
    glUseProgram(0);

    dTime = (float)(glfwGetTime() - StartTime);
    Color_Random();
  }


  void CS_Renderer::InitShaders()
  {
    shader = LoadShaders("Vertex.vs.glsl", "Fragment.frag.glsl");
    computeshader = LoadComputeShader ("Systems/Graphics/Shaders/MouseParticleEffect.cs.glsl");
  }


  void CS_Renderer::CreateBuffers()
  {
    vao = new VAO();

    Posbuffer = new SSBO(NumParticles * sizeof(glm::vec4));
    CreatePos();
    Posbuffer->BindBufferBase(0);

    VelBuffer = new SSBO(NumParticles * sizeof(glm::vec4));
    CreateVel();
    VelBuffer->BindBufferBase(1);

    AccBuffer = new SSBO(NumParticles * sizeof(glm::vec4));
    CreateAcc();
    AccBuffer->BindBufferBase(2);

    vao->unBind();
  }
  void CS_Renderer::LoadTexture()
  {
    texture = new Texture("Particle");
  }

  void CS_Renderer::CreatePos()
  {
    int windowWidth, windowHeight;
    glfwPollEvents();
    glfwGetCursorPos(g_GraphicsSys->GetCurrentWindow().glfw_GetWindow(), &MousePosX, &MousePosY);
    glfwGetWindowSize(g_GraphicsSys->GetCurrentWindow().glfw_GetWindow(), &windowWidth, &windowHeight);

    destPos.x = (float) (MousePosX / (windowWidth) -0.5f) * 2.0f;
    destPos.y = (float) ((windowHeight - MousePosY) / windowHeight - 0.5f) * 2.0f;


    glm::vec4* verticesPos = (glm::vec4*)Posbuffer->MapBufferRange<glm::vec4>(0, NumParticles);
    for (int i = 0; i < NumParticles; i++)
    {
      verticesPos[i] = glm::linearRand(glm::vec4(-0.25f, -0.5f, -0.5f, 1.0f), glm::vec4(0.25f, 0.5f, 0.5f, 1.0f));
    }
    Posbuffer->UnMapBuffer();
  }


  void CS_Renderer::CreateVel()
  {
    glm::vec4* verticesVel = VelBuffer->MapBufferRange<glm::vec4>(0, NumParticles);
    for (int i = 0; i < NumParticles; i++)
    {
      verticesVel[i].x = 0.0f;
      verticesVel[i].y = 0.0f;
      verticesVel[i].z = 0.0f;
      verticesVel[i].w = 1.0f;
    }
    VelBuffer->UnMapBuffer();
  }

  void CS_Renderer::CreateAcc()
  {
    glm::vec4* verticesAcc = AccBuffer->MapBufferRange<glm::vec4>(0, NumParticles);
    for (int i = 0; i < NumParticles; i++)
    {
      verticesAcc[i].x = 0.0f;
      verticesAcc[i].y = 0.0f;
      verticesAcc[i].z = 0.0f;
      verticesAcc[i].w = 1.0f;
    }
    AccBuffer->UnMapBuffer();
  }



  void CS_Renderer::Color_Random()
  {
    timepassed -= 0.016f;
    if (timepassed <= 0)
    {
      startcolor = glm::linearRand(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
      endcolor = glm::linearRand(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.5f));
      timepassed = glm::linearRand(1.0f, 0.0f);

    }

    colVec = glm::mix(startcolor, endcolor, timepassed);
  }

}