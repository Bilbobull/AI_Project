#include"Math_Headers.h"
#include "ObjectManager.h"
#include <vector>
#define MAX_LIGHTS 8
#define  DIRECTIONAL 0
#define  SPOT 1
#define  POINT 2

struct Material
{
  glm::vec4 ambient; // ambient color of the surface/how much ambient light to absorb
  glm::vec4 diffuse; // diffuse color of the surface/how much diffuse light to absorb
  glm::vec4 specular;
  glm::vec4 emisive;
};

void RotateLights(void);

extern int ShaderType;
extern std::vector<Object*> LightObjects;
extern int Lighttype[MAX_LIGHTS];
extern glm::vec4 Lightposition[MAX_LIGHTS];
extern glm::vec4 Lightdirection[MAX_LIGHTS];
extern glm::vec4 Lightambient[MAX_LIGHTS];
extern glm::vec4 Lightdiffuse[MAX_LIGHTS];
extern glm::vec4 Lightspecular[MAX_LIGHTS];
extern float Lightinner[MAX_LIGHTS];
extern float Lightouter[MAX_LIGHTS];
extern float Lightfalloff[MAX_LIGHTS];
extern Material MaterialVal;
extern int LightNum;
extern float Shininess;
extern float DistanceAttConstants[3];
extern int DistanceAtt;
extern int AtmosphericAtt;
extern float NearPlane;
extern float FarPlane;
extern glm::vec4 AtmosphericIntensity;
extern int Textures;
extern glm::vec4 GlobalAmbient;