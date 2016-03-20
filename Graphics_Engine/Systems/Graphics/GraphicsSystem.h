// Author: Gonzalo Rojo

#pragma once

#include "Context.h"
#include "Graphics_Headers.h"
#include "../Systems.h"
#include "Camera.h"

class GraphicsSystem : public System
{
public:
  GraphicsSystem(){}
  ~GraphicsSystem(){}

  void Init(void);
  void Update(double dt);
  void Free(void);

  Window& GetCurrentWindow(void);
  Camera& GetCurrentCamera(void);
  void SetBackgroundColor(float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);
  void DebugDraw(void){ Debug_Draw = !Debug_Draw; }
  void DebugDraw(bool yesorno) { Debug_Draw = yesorno; }
  bool GetDebugDraw(void){ return Debug_Draw; }

  void VertexNormalDraw(void){ Vertex_Normal_Draw = !Vertex_Normal_Draw; }
  void VertexNormalDraw(bool yesorno){ Vertex_Normal_Draw = yesorno; }
  bool GetVertexNormalDraw(void){ return Vertex_Normal_Draw; }

  void FaceNormalDraw(void){ Face_Normal_Draw = !Face_Normal_Draw; }
  void FaceNormalDraw(bool yesorno){ Face_Normal_Draw = yesorno; }
  bool GetFaceNormalDraw(void){ return Face_Normal_Draw; }
  glm::vec3 Random_Color(void);
  void Particle_Draw(void){ 
    ResetParticles = true;
    Particles = !Particles; }

  void Light_Rotation(void){ LightRotation = !LightRotation; }
  bool Get_Light_Rotation(void){ return LightRotation; }

private:
  Window Current_Window;
  Camera My_Camera;
  bool Debug_Draw;
  bool Vertex_Normal_Draw;
  bool Face_Normal_Draw;
  bool Particles;
  bool ResetParticles;
  bool LightRotation;
};

extern GraphicsSystem* g_GraphicsSys;