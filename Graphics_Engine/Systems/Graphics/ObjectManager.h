#pragma once
#include "Object.h"

class ObjectManager
{

public:
  static Object* CreateObject(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 sca = glm::vec3(1.0f, 1.0f, 1.0f), float angle = 0.0f, glm::vec3 rot = glm::vec3(1.0f, 0.0f, 0.0f),
                               std::string filename = " ", Meshes meshtype = Meshes::Arrow_Mesh);

  static std::vector <Object*>& GetObjectList(){ return Object_List; }
  static void Free(void);
private:
  static std::vector <Object*> Object_List;
};