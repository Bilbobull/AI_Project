#include "ObjectManager.h"

Object* ObjectManager::CreateObject(glm::vec3 pos, glm::vec3 sca, float angle, glm::vec3 rot, std::string filename, Meshes meshtype)
{
  Object* object = new Object(pos, sca, angle, rot, filename, meshtype);
  Object_List.push_back(object);

  return object;
}

void ObjectManager::Free(void)
{
  for (auto it : Object_List)
  {
    delete it;
  }
}


std::vector <Object*> ObjectManager::Object_List;

