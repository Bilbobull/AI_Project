#pragma once

#include "../../Graphics_Headers.h"
#include "../../Math_Headers.h"
#include "ShaderBufferManager.h"
#include "../../Buffer_Manager.h"
#include "ComputeShader.h"
#include "../../Texture.h"
#include <string>

namespace ComputeShaders
{
  class CS_Renderer
  {
  public:

    CS_Renderer();
    CS_Renderer(const CS_Renderer&) = delete;
    CS_Renderer& operator =(const CS_Renderer&) = delete;
    virtual ~CS_Renderer();

    virtual void Initialize();
    virtual void Draw();

    void InitShaders();
    void CreateBuffers();
    void LoadTexture();
    void CreatePos();
    void CreateVel ();
    void CreateAcc();
    void Color_Random();

  private:
    GLuint shader;
    ComputeShader* computeshader;
    SSBO* Posbuffer, *VelBuffer, *AccBuffer;
    VAO* vao;

    Texture* texture;

    float radius;
    float radiusMultiplier;
    float minAlpha;
    int NumParticles;
    float dTime = 0.0f;

    glm::vec3 startcolor;
    glm::vec3 endcolor;
    glm::vec3 colVec;

    glm::vec2 destPos;

  };
}
