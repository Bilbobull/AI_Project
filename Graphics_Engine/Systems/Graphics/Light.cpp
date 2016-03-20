#include "Light.h"
#include "GraphicsSystem.h"
#include "Object.h"

//Light::Light(glm::vec4 const &_direction, glm::vec4 const &_ambient = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
//  glm::vec4 const &_diffuse = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)) : direction(_direction), ambient(_ambient), diffuse(_diffuse)
//{}

int ShaderType = 0;
std::vector<Object*> LightObjects;
int Lighttype[MAX_LIGHTS];
glm::vec4 Lightposition[MAX_LIGHTS];
glm::vec4 Lightdirection[MAX_LIGHTS];
glm::vec4 Lightambient[MAX_LIGHTS];
glm::vec4 Lightdiffuse[MAX_LIGHTS];
glm::vec4 Lightspecular[MAX_LIGHTS];
float Lightinner[MAX_LIGHTS];
float Lightouter[MAX_LIGHTS];
float Lightfalloff[MAX_LIGHTS];
Material MaterialVal;

int LightNum = 1;
float Shininess = 0.8f;
float DistanceAttConstants[3];
int DistanceAtt = 1;
int AtmosphericAtt = 1;
glm::vec4 AtmosphericIntensity = glm::vec4(0.3f, 0.3f, 0.3f, 1.0f);
float NearPlane = 10;
float FarPlane = 20;
int Textures = 1;
glm::vec4 GlobalAmbient = glm::vec4(0.2f, 0.2f, 0.2f, 1);

void RotateLights(void)
{
  unsigned i = 0;
  float rotation_rads = 0.0436332f;
  for (int i = 0; i < LightNum; ++i)
  {
    glm::mat4 Translate (1.0f), Rotation(1.0f);

    glm::vec4 old_pos = Lightposition[i];
    glm::vec4 center = glm::vec4(ObjectManager::GetObjectList().at(0)->position.x, ObjectManager::GetObjectList().at(0)->position.y, ObjectManager::GetObjectList().at(0)->position.z, 1);
    glm::vec4 rotation_around = center;
    glm::vec4 old_min_rotate_a = old_pos - rotation_around;

    glm::vec4 new_pos = glm::vec4(old_min_rotate_a.x * cos(rotation_rads) - old_min_rotate_a.z * sin(rotation_rads),
      old_min_rotate_a.y,
      old_min_rotate_a.z * cos(rotation_rads) + old_min_rotate_a.x * sin(rotation_rads),
      1);
   
    Lightposition[i] = new_pos + rotation_around;
    Lightdirection[i] = Lightposition[i] - center;

    if (Lighttype[i] != DIRECTIONAL)
    {
      LightObjects[i]->position = glm::vec3(Lightposition[i].x, Lightposition[i].y, Lightposition[i].z);
    }

    else
    {
      glm::vec4 center = glm::vec4(ObjectManager::GetObjectList().at(0)->position.x, ObjectManager::GetObjectList().at(0)->position.y, ObjectManager::GetObjectList().at(0)->position.z, 1);
      glm::vec4 temp = center - Lightdirection[i];
      LightObjects[i]->position = glm::vec3(temp.x, temp.y, temp.z);
    }
  }
}