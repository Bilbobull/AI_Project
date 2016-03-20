#pragma once
#include "Graphics_Headers.h"
#include "Math_Headers.h"
#include "Buffer_Manager.h"
#include "Mesh.h"

void Init(void);

enum Meshes{
  Cube_Mesh,
  Arrow_Mesh,
  Plane_Mesh
};

class MeshGenerator 
{
public:
  static void Init(void);
  static Mesh* makeCube(void);
  static Mesh* makeArrow(void);
  static Mesh* makePlane(unsigned dimensions = 10);
  static void SaveVertices(Mesh& shape, unsigned dimensions);
  static void SaveIndices(Mesh& shape, unsigned dimensions);
  static void Specify_Attributes(void);
  static void Specify_Simple_Attributes(void);
  static Mesh* makeMeshFromObj(std::string filename);;

  static Mesh* Create_Shape(std::string filename = " ", Meshes meshtype = Cube_Mesh);
  
private:
  
};