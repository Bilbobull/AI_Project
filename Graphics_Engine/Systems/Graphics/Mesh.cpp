#include "Mesh.h"
#include "LoadShader.h"
#include "GraphicsSystem.h"
#include "Light.h"

GLuint SimpleProgram;
GLuint SimpleMatUniform;

#pragma region FragPhong 

GLuint FragPhongModelProgram;
GLuint FragPhongModelModelToWorldUniform;
GLuint FragPhongModelWorldToViewUniform;
GLuint FragPhongModelViewToProjectionUniform;
GLuint FragPhongDiffuseTextureUniform;
GLuint FragPhongNormalTextureUniform;
GLuint FragPhongLightTypeArrayUniform;
GLuint FragPhongLightPositionArrayUniform;
GLuint FragPhongLightDirectionArrayUniform;
GLuint FragPhongLightAmbientArrayUniform;
GLuint FragPhongLightDiffuseArrayUniform;
GLuint FragPhongLightSpecularArrayUniform;
GLuint FragPhongLightInnerUniform;
GLuint FragPhongLightOuterUniform;
GLuint FragPhongLightFalloffUniform;
GLuint FragPhongTexturesUniform;

GLuint FragPhongCamPosUniform;

GLuint FragPhongGlobalAmbientUniform;

GLuint FragPhongMaterialAmbientUniform;
GLuint FragPhongMaterialDiffuseUniform;
GLuint FragPhongMaterialSpecularUniform;
GLuint FragPhongMaterialEmisiveUniform;

GLuint FragPhongShininessUniform;

GLuint FragPhongLightCountUniform;

GLuint FragPhongDistanceAttConstUniform;
GLuint FragPhongDistanceAttBoolUniform;

GLuint FragPhongNearPlaneLocation;
GLuint FragPhongFarPlaneLocation;
GLuint FragPhongAtmosphericAttBoolUniform;
GLuint FragPhongAtmosphericAttIntesityUniform;

#pragma endregion


#pragma region VertPhong

GLuint VertPhongModelProgram;
GLuint VertPhongModelModelToWorldUniform;
GLuint VertPhongModelWorldToViewUniform;
GLuint VertPhongModelViewToProjectionUniform;
GLuint VertPhongDiffuseTextureUniform;
GLuint VertPhongNormalTextureUniform;
GLuint VertPhongLightTypeArrayUniform;
GLuint VertPhongLightPositionArrayUniform;
GLuint VertPhongLightDirectionArrayUniform;
GLuint VertPhongLightAmbientArrayUniform;
GLuint VertPhongLightDiffuseArrayUniform;
GLuint VertPhongLightSpecularArrayUniform;

GLuint VertPhongLightInnerUniform;
GLuint VertPhongLightOuterUniform;
GLuint VertPhongLightFalloffUniform;
GLuint VertPhongTexturesUniform;

GLuint VertPhongCamPosUniform;

GLuint VertPhongGlobalAmbientUniform;

GLuint VertPhongMaterialAmbientUniform;
GLuint VertPhongMaterialDiffuseUniform;
GLuint VertPhongMaterialSpecularUniform;
GLuint VertPhongMaterialEmisiveUniform;

GLuint VertPhongShininessUniform;

GLuint VertPhongLightCountUniform;

GLuint VertPhongDistanceAttConstUniform;
GLuint VertPhongDistanceAttBoolUniform;

GLuint VertPhongNearPlaneLocation;
GLuint VertPhongFarPlaneLocation;
GLuint VertPhongAtmosphericAttBoolUniform;
GLuint VertPhongAtmosphericAttIntesityUniform;

#pragma endregion

#pragma region FragBlinn

GLuint FragBlinnModelProgram;
GLuint FragBlinnModelModelToWorldUniform;
GLuint FragBlinnModelWorldToViewUniform;
GLuint FragBlinnModelViewToProjectionUniform;
GLuint FragBlinnDiffuseTextureUniform;
GLuint FragBlinnNormalTextureUniform;
GLuint FragBlinnLightTypeArrayUniform;
GLuint FragBlinnLightPositionArrayUniform;
GLuint FragBlinnLightDirectionArrayUniform;
GLuint FragBlinnLightAmbientArrayUniform;
GLuint FragBlinnLightDiffuseArrayUniform;
GLuint FragBlinnLightSpecularArrayUniform;

GLuint FragBlinnLightInnerUniform;
GLuint FragBlinnLightOuterUniform;
GLuint FragBlinnLightFalloffUniform;
GLuint FragBlinnTexturesUniform;

GLuint FragBlinnCamPosUniform;

GLuint FragBlinnGlobalAmbientUniform;

GLuint FragBlinnMaterialAmbientUniform;
GLuint FragBlinnMaterialDiffuseUniform;
GLuint FragBlinnMaterialSpecularUniform;
GLuint FragBlinnMaterialEmisiveUniform;

GLuint FragBlinnShininessUniform;

GLuint FragBlinnLightCountUniform;

GLuint FragBlinnDistanceAttConstUniform;
GLuint FragBlinnDistanceAttBoolUniform;

GLuint FragBlinnNearPlaneLocation;
GLuint FragBlinnFarPlaneLocation;
GLuint FragBlinnAtmosphericAttBoolUniform;
GLuint FragBlinnAtmosphericAttIntesityUniform;

#pragma endregion

void Mesh::Init_Mesh_Shader(void)
{
  SimpleProgram = LoadShaders("SimpleVertexShader.glsl", "SimpleFragmentShader.glsl");
  SimpleMatUniform = glGetUniformLocation(SimpleProgram, "FullTransformMatrix");


#pragma region PerFragment

  FragPhongModelProgram = LoadShaders("ModelVertexShader.glsl", "ModelFragmentShader.glsl");

  FragPhongDiffuseTextureUniform = glGetUniformLocation(FragPhongModelProgram, "Texture");
  FragPhongNormalTextureUniform = glGetUniformLocation(FragPhongModelProgram, "normalTexture");

  FragPhongGlobalAmbientUniform = glGetUniformLocation(FragPhongModelProgram, "globalAmbient");
  FragPhongLightTypeArrayUniform = glGetUniformLocation(FragPhongModelProgram, "lightTypes");
  FragPhongLightPositionArrayUniform = glGetUniformLocation(FragPhongModelProgram, "lightPositions");
  FragPhongLightDirectionArrayUniform = glGetUniformLocation(FragPhongModelProgram, "lightDirections");
  FragPhongLightAmbientArrayUniform = glGetUniformLocation(FragPhongModelProgram, "lightAmbients");
  FragPhongLightDiffuseArrayUniform = glGetUniformLocation(FragPhongModelProgram, "lightDiffuses");
  FragPhongLightSpecularArrayUniform = glGetUniformLocation(FragPhongModelProgram, "lightSpeculars");

  FragPhongLightInnerUniform = glGetUniformLocation(FragPhongModelProgram, "lightInners"); 
  FragPhongLightOuterUniform = glGetUniformLocation(FragPhongModelProgram, "lightOuters");
  FragPhongLightFalloffUniform = glGetUniformLocation(FragPhongModelProgram, "lightFalloffs");
  FragPhongLightCountUniform = glGetUniformLocation(FragPhongModelProgram, "LightCount");
  FragPhongMaterialDiffuseUniform = glGetUniformLocation(FragPhongModelProgram, "MaterialValues.diffuse");
  FragPhongMaterialAmbientUniform = glGetUniformLocation(FragPhongModelProgram, "MaterialValues.ambient");
  FragPhongMaterialSpecularUniform = glGetUniformLocation(FragPhongModelProgram, "MaterialValues.specular");
  FragPhongMaterialEmisiveUniform = glGetUniformLocation(FragPhongModelProgram, "MaterialValues.emisive");
  FragPhongModelModelToWorldUniform = glGetUniformLocation(FragPhongModelProgram, "ModelToWorldMatrix");
  FragPhongModelWorldToViewUniform = glGetUniformLocation(FragPhongModelProgram, "WorldToViewMatrix");
  FragPhongModelViewToProjectionUniform = glGetUniformLocation(FragPhongModelProgram, "ViewToProjectionMatrix");
  FragPhongCamPosUniform = glGetUniformLocation(FragPhongModelProgram, "CameraPosition");
  FragPhongShininessUniform = glGetUniformLocation(FragPhongModelProgram, "Shininess");
  FragPhongDistanceAttConstUniform = glGetUniformLocation(FragPhongModelProgram, "DistanceAttConstants");
  FragPhongDistanceAttBoolUniform = glGetUniformLocation(FragPhongModelProgram, "DistanceAttBool");
  FragPhongNearPlaneLocation = glGetUniformLocation(FragPhongModelProgram, "NearPlane");
  FragPhongFarPlaneLocation = glGetUniformLocation(FragPhongModelProgram, "FarPlane");
  FragPhongAtmosphericAttBoolUniform = glGetUniformLocation(FragPhongModelProgram, "AtmosphericAttBool");
  FragPhongAtmosphericAttIntesityUniform = glGetUniformLocation(FragPhongModelProgram, "AtmosphericIntensity");
  FragPhongTexturesUniform = glGetUniformLocation(FragPhongModelProgram, "Textures");

#pragma endregion

#pragma region PerVertex

  VertPhongModelProgram = LoadShaders("PerVertexPhong.vs.glsl", "PerVertexPhong.fs.glsl");

  VertPhongDiffuseTextureUniform = glGetUniformLocation(VertPhongModelProgram, "Texture");
  VertPhongNormalTextureUniform = glGetUniformLocation(VertPhongModelProgram, "normalTexture");

  VertPhongGlobalAmbientUniform = glGetUniformLocation(VertPhongModelProgram, "globalAmbient");
  VertPhongLightTypeArrayUniform = glGetUniformLocation(VertPhongModelProgram, "lightTypes");
  VertPhongLightPositionArrayUniform = glGetUniformLocation(VertPhongModelProgram, "lightPositions");
  VertPhongLightDirectionArrayUniform = glGetUniformLocation(VertPhongModelProgram, "lightDirections");
  VertPhongLightAmbientArrayUniform = glGetUniformLocation(VertPhongModelProgram, "lightAmbients");
  VertPhongLightDiffuseArrayUniform = glGetUniformLocation(VertPhongModelProgram, "lightDiffuses");
  VertPhongLightSpecularArrayUniform = glGetUniformLocation(VertPhongModelProgram, "lightSpeculars");
  
  VertPhongLightInnerUniform = glGetUniformLocation(VertPhongModelProgram, "lightInners");
  VertPhongLightOuterUniform = glGetUniformLocation(VertPhongModelProgram, "lightOuters");
  VertPhongLightFalloffUniform = glGetUniformLocation(VertPhongModelProgram, "lightFalloffs");
  VertPhongLightCountUniform = glGetUniformLocation(VertPhongModelProgram, "LightCount");
  VertPhongMaterialDiffuseUniform = glGetUniformLocation(VertPhongModelProgram, "MaterialValues.diffuse");
  VertPhongMaterialAmbientUniform = glGetUniformLocation(VertPhongModelProgram, "MaterialValues.ambient");
  VertPhongMaterialSpecularUniform = glGetUniformLocation(VertPhongModelProgram, "MaterialValues.specular");
  VertPhongMaterialEmisiveUniform = glGetUniformLocation(VertPhongModelProgram, "MaterialValues.emisive");

  VertPhongModelModelToWorldUniform = glGetUniformLocation(VertPhongModelProgram, "ModelToWorldMatrix");
  VertPhongModelWorldToViewUniform = glGetUniformLocation(VertPhongModelProgram, "WorldToViewMatrix");
  VertPhongModelViewToProjectionUniform = glGetUniformLocation(VertPhongModelProgram, "ViewToProjectionMatrix");
  VertPhongCamPosUniform = glGetUniformLocation(VertPhongModelProgram, "CameraPosition");
  VertPhongShininessUniform = glGetUniformLocation(VertPhongModelProgram, "Shininess");
  VertPhongDistanceAttConstUniform = glGetUniformLocation(VertPhongModelProgram, "DistanceAttConstants");
  VertPhongDistanceAttBoolUniform = glGetUniformLocation(VertPhongModelProgram, "DistanceAttBool");
  VertPhongNearPlaneLocation = glGetUniformLocation(VertPhongModelProgram, "NearPlane");
  VertPhongFarPlaneLocation = glGetUniformLocation(VertPhongModelProgram, "FarPlane");
  VertPhongAtmosphericAttBoolUniform = glGetUniformLocation(VertPhongModelProgram, "AtmosphericAttBool");
  VertPhongAtmosphericAttIntesityUniform = glGetUniformLocation(VertPhongModelProgram, "AtmosphericIntensity");
  VertPhongTexturesUniform = glGetUniformLocation(VertPhongModelProgram, "Textures");

#pragma endregion


#pragma region FragBlinn

  FragBlinnModelProgram = LoadShaders("PerFragmentBlinn.vs.glsl", "PerFragmentBlinn.fs.glsl");

  FragBlinnDiffuseTextureUniform = glGetUniformLocation(FragBlinnModelProgram, "Texture");
  FragBlinnNormalTextureUniform = glGetUniformLocation(FragBlinnModelProgram, "normalTexture");

  FragBlinnGlobalAmbientUniform = glGetUniformLocation(FragBlinnModelProgram, "globalAmbient");
  FragBlinnLightTypeArrayUniform = glGetUniformLocation(FragBlinnModelProgram, "lightTypes");
  FragBlinnLightPositionArrayUniform = glGetUniformLocation(FragBlinnModelProgram, "lightPositions");
  FragBlinnLightDirectionArrayUniform = glGetUniformLocation(FragBlinnModelProgram, "lightDirections");
  FragBlinnLightAmbientArrayUniform = glGetUniformLocation(FragBlinnModelProgram, "lightAmbients");
  FragBlinnLightDiffuseArrayUniform = glGetUniformLocation(FragBlinnModelProgram, "lightDiffuses");
  FragBlinnLightSpecularArrayUniform = glGetUniformLocation(FragBlinnModelProgram, "lightSpeculars");
  
  FragBlinnLightInnerUniform = glGetUniformLocation(FragBlinnModelProgram, "lightInners");
  FragBlinnLightOuterUniform = glGetUniformLocation(FragBlinnModelProgram, "lightOuters");
  FragBlinnLightFalloffUniform = glGetUniformLocation(FragBlinnModelProgram, "lightFalloffs");
  FragBlinnLightCountUniform = glGetUniformLocation(FragBlinnModelProgram, "LightCount");

  FragBlinnMaterialDiffuseUniform = glGetUniformLocation(FragBlinnModelProgram, "MaterialValues.diffuse");
  FragBlinnMaterialAmbientUniform = glGetUniformLocation(FragBlinnModelProgram, "MaterialValues.ambient");
  FragBlinnMaterialSpecularUniform = glGetUniformLocation(FragBlinnModelProgram, "MaterialValues.specular");
  FragBlinnMaterialEmisiveUniform = glGetUniformLocation(FragBlinnModelProgram, "MaterialValues.emisive");

  FragBlinnModelModelToWorldUniform = glGetUniformLocation(FragBlinnModelProgram, "ModelToWorldMatrix");
  FragBlinnModelWorldToViewUniform = glGetUniformLocation(FragBlinnModelProgram, "WorldToViewMatrix");
  FragBlinnModelViewToProjectionUniform = glGetUniformLocation(FragBlinnModelProgram, "ViewToProjectionMatrix");
  FragBlinnCamPosUniform = glGetUniformLocation(FragBlinnModelProgram, "CameraPosition");
  FragBlinnShininessUniform = glGetUniformLocation(FragBlinnModelProgram, "Shininess");
  FragBlinnDistanceAttConstUniform = glGetUniformLocation(FragBlinnModelProgram, "DistanceAttConstants");
  FragBlinnDistanceAttBoolUniform = glGetUniformLocation(FragBlinnModelProgram, "DistanceAttBool");
  FragBlinnNearPlaneLocation = glGetUniformLocation(FragBlinnModelProgram, "NearPlane");
  FragBlinnFarPlaneLocation = glGetUniformLocation(FragBlinnModelProgram, "FarPlane");
  FragBlinnAtmosphericAttBoolUniform = glGetUniformLocation(FragBlinnModelProgram, "AtmosphericAttBool");
  FragBlinnAtmosphericAttIntesityUniform = glGetUniformLocation(FragBlinnModelProgram, "AtmosphericIntensity");
  FragBlinnTexturesUniform = glGetUniformLocation(FragBlinnModelProgram, "Textures");

#pragma endregion
  
}



void Mesh::Draw(glm::mat4 ModelToWorld, glm::mat4 WorldToView, glm::mat4 ViewToProjection, glm::mat4 scale)
{



  glm::mat4 fullmatrix = ViewToProjection  * WorldToView * ModelToWorld;

  switch (type)
  {
  case Models:
  {
    if (g_GraphicsSys->GetDebugDraw() == true || texture == nullptr)
    {
      Debug_Draw(fullmatrix);
    }

    else
    {
      glClearColor(0, 0, 0, 0);
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

      if (ShaderType == 0)
      {
#pragma region PerFragent

        glUseProgram(FragPhongModelProgram);

        glActiveTexture(GL_TEXTURE0);
        texture->TexBind();
        glUniform1i(FragPhongDiffuseTextureUniform, 0);

        glActiveTexture(GL_TEXTURE1);
        texture->NorBind();
        glUniform1i(FragPhongNormalTextureUniform, 1);

        glActiveTexture(GL_TEXTURE0);

        vao->Bind();
        glUniform1iv(FragPhongLightTypeArrayUniform, ARRAYSIZE(Lighttype), &Lighttype[0]);
        glUniform4fv(FragPhongLightPositionArrayUniform, ARRAYSIZE(Lightposition), glm::value_ptr(Lightposition[0]));
        glUniform4fv(FragPhongLightDirectionArrayUniform, ARRAYSIZE(Lightdirection), glm::value_ptr(Lightdirection[0]));
        glUniform4fv(FragPhongLightAmbientArrayUniform, ARRAYSIZE(Lightambient), glm::value_ptr(Lightambient[0]));
        glUniform4fv(FragPhongLightDiffuseArrayUniform, ARRAYSIZE(Lightdiffuse), glm::value_ptr(Lightdiffuse[0]));
        glUniform4fv(FragPhongLightSpecularArrayUniform, ARRAYSIZE(Lightspecular), glm::value_ptr(Lightspecular[0]));

        glUniform1fv(FragPhongLightInnerUniform, ARRAYSIZE(Lightinner), &Lightinner[0]);
        glUniform1fv(FragPhongLightOuterUniform, ARRAYSIZE(Lightouter), &Lightouter[0]);
        glUniform1fv(FragPhongLightFalloffUniform, ARRAYSIZE(Lightfalloff), &Lightfalloff[0]);

        glUniform4fv(FragPhongMaterialDiffuseUniform, 1, glm::value_ptr(MaterialVal.diffuse));
        glUniform4fv(FragPhongMaterialAmbientUniform, 1, glm::value_ptr(MaterialVal.ambient));
        glUniform4fv(FragPhongMaterialSpecularUniform, 1, glm::value_ptr(MaterialVal.specular));
        glUniform4fv(FragPhongMaterialEmisiveUniform, 1, glm::value_ptr(MaterialVal.emisive));

        glUniform1i(FragPhongLightCountUniform, LightNum);
        glUniform3fv(FragPhongCamPosUniform, 1, glm::value_ptr(g_GraphicsSys->GetCurrentCamera().GetPosition()));
        glUniform1f(FragPhongShininessUniform, Shininess);
        glUniform1fv(FragPhongDistanceAttConstUniform, ARRAYSIZE(DistanceAttConstants), &DistanceAttConstants[0]);
        glUniform1i(FragPhongDistanceAttBoolUniform, DistanceAtt);
        glUniform1f(FragPhongNearPlaneLocation, NearPlane);
        glUniform1f(FragPhongFarPlaneLocation, FarPlane);
        glUniform1i(FragPhongAtmosphericAttBoolUniform, AtmosphericAtt);
        glUniform4fv(FragPhongAtmosphericAttIntesityUniform, 1, glm::value_ptr(AtmosphericIntensity));

        glUniform4fv(FragPhongGlobalAmbientUniform, 1, glm::value_ptr(GlobalAmbient));

        glUniform1i(FragPhongTexturesUniform, Textures);

        glUniformMatrix4fv(FragPhongModelModelToWorldUniform, 1, GL_FALSE, &ModelToWorld[0][0]);
        glUniformMatrix4fv(FragPhongModelWorldToViewUniform, 1, GL_FALSE, &WorldToView[0][0]);
        glUniformMatrix4fv(FragPhongModelViewToProjectionUniform, 1, GL_FALSE, &ViewToProjection[0][0]);
        glDrawElements(GL_TRIANGLES, triangles.size(), GL_UNSIGNED_SHORT, 0);
        texture->unBind();

#pragma endregion 
      }

      else if (ShaderType == 1)
      {

#pragma region PerVertex
        
        glUseProgram(VertPhongModelProgram);

        glActiveTexture(GL_TEXTURE0);
        texture->TexBind();
        glUniform1i(VertPhongDiffuseTextureUniform, 0);

        glActiveTexture(GL_TEXTURE1);
        texture->NorBind();
        glUniform1i(VertPhongNormalTextureUniform, 1);

        glActiveTexture(GL_TEXTURE0);

        vao->Bind();
        glUniform1iv(VertPhongLightTypeArrayUniform, ARRAYSIZE(Lighttype), &Lighttype[0]);
        glUniform4fv(VertPhongLightPositionArrayUniform, ARRAYSIZE(Lightposition), glm::value_ptr(Lightposition[0]));
        glUniform4fv(VertPhongLightDirectionArrayUniform, ARRAYSIZE(Lightdirection), glm::value_ptr(Lightdirection[0]));
        glUniform4fv(VertPhongLightAmbientArrayUniform, ARRAYSIZE(Lightambient), glm::value_ptr(Lightambient[0]));
        glUniform4fv(VertPhongLightDiffuseArrayUniform, ARRAYSIZE(Lightdiffuse), glm::value_ptr(Lightdiffuse[0]));
        glUniform4fv(VertPhongLightSpecularArrayUniform, ARRAYSIZE(Lightspecular), glm::value_ptr(Lightspecular[0]));

        glUniform1fv(VertPhongLightInnerUniform, ARRAYSIZE(Lightinner), &Lightinner[0]);
        glUniform1fv(VertPhongLightOuterUniform, ARRAYSIZE(Lightouter), &Lightouter[0]);
        glUniform1fv(VertPhongLightFalloffUniform, ARRAYSIZE(Lightfalloff), &Lightfalloff[0]);

        glUniform4fv(VertPhongMaterialDiffuseUniform, 1, glm::value_ptr(MaterialVal.diffuse));
        glUniform4fv(VertPhongMaterialAmbientUniform, 1, glm::value_ptr(MaterialVal.ambient));
        glUniform4fv(VertPhongMaterialSpecularUniform, 1, glm::value_ptr(MaterialVal.specular));
        glUniform4fv(VertPhongMaterialEmisiveUniform, 1, glm::value_ptr(MaterialVal.emisive));

        glUniform1i(VertPhongLightCountUniform, LightNum);
        glUniform3fv(VertPhongCamPosUniform, 1, glm::value_ptr(g_GraphicsSys->GetCurrentCamera().GetPosition()));
        glUniform1f(VertPhongShininessUniform, Shininess);
        glUniform1fv(VertPhongDistanceAttConstUniform, ARRAYSIZE(DistanceAttConstants), &DistanceAttConstants[0]);
        glUniform1i(VertPhongDistanceAttBoolUniform, DistanceAtt);
        glUniform1f(VertPhongNearPlaneLocation, NearPlane);
        glUniform1f(VertPhongFarPlaneLocation, FarPlane);
        glUniform1i(VertPhongAtmosphericAttBoolUniform, AtmosphericAtt);
        glUniform4fv(VertPhongAtmosphericAttIntesityUniform, 1, glm::value_ptr(AtmosphericIntensity));

        glUniform4fv(VertPhongGlobalAmbientUniform, 1, glm::value_ptr(GlobalAmbient));

        glUniform1i(VertPhongTexturesUniform, Textures);

        glUniformMatrix4fv(VertPhongModelModelToWorldUniform, 1, GL_FALSE, &ModelToWorld[0][0]);
        glUniformMatrix4fv(VertPhongModelWorldToViewUniform, 1, GL_FALSE, &WorldToView[0][0]);
        glUniformMatrix4fv(VertPhongModelViewToProjectionUniform, 1, GL_FALSE, &ViewToProjection[0][0]);
        glDrawElements(GL_TRIANGLES, triangles.size(), GL_UNSIGNED_SHORT, 0);
        texture->unBind();

#pragma endregion

      }

      else if (ShaderType == 2)
      {
#pragma region Blinn

        glUseProgram(FragBlinnModelProgram);

        glActiveTexture(GL_TEXTURE0);
        texture->TexBind();
        glUniform1i(FragBlinnDiffuseTextureUniform, 0);

        glActiveTexture(GL_TEXTURE1);
        texture->NorBind();
        glUniform1i(FragBlinnNormalTextureUniform, 1);

        glActiveTexture(GL_TEXTURE0);

        vao->Bind();
        glUniform1iv(FragBlinnLightTypeArrayUniform, ARRAYSIZE(Lighttype), &Lighttype[0]);
        glUniform4fv(FragBlinnLightPositionArrayUniform, ARRAYSIZE(Lightposition), glm::value_ptr(Lightposition[0]));
        glUniform4fv(FragBlinnLightDirectionArrayUniform, ARRAYSIZE(Lightdirection), glm::value_ptr(Lightdirection[0]));
        glUniform4fv(FragBlinnLightAmbientArrayUniform, ARRAYSIZE(Lightambient), glm::value_ptr(Lightambient[0]));
        glUniform4fv(FragBlinnLightDiffuseArrayUniform, ARRAYSIZE(Lightdiffuse), glm::value_ptr(Lightdiffuse[0]));
        glUniform4fv(FragBlinnLightSpecularArrayUniform, ARRAYSIZE(Lightspecular), glm::value_ptr(Lightspecular[0]));

        glUniform1fv(FragBlinnLightInnerUniform, ARRAYSIZE(Lightinner), &Lightinner[0]);
        glUniform1fv(FragBlinnLightOuterUniform, ARRAYSIZE(Lightouter), &Lightouter[0]);
        glUniform1fv(FragBlinnLightFalloffUniform, ARRAYSIZE(Lightfalloff), &Lightfalloff[0]);

        glUniform4fv(FragBlinnMaterialDiffuseUniform, 1, glm::value_ptr(MaterialVal.diffuse));
        glUniform4fv(FragBlinnMaterialAmbientUniform, 1, glm::value_ptr(MaterialVal.ambient));
        glUniform4fv(FragBlinnMaterialSpecularUniform, 1, glm::value_ptr(MaterialVal.specular));
        glUniform4fv(FragBlinnMaterialEmisiveUniform, 1, glm::value_ptr(MaterialVal.emisive));
        glUniform1i(FragBlinnLightCountUniform, LightNum);
        glUniform3fv(FragBlinnCamPosUniform, 1, glm::value_ptr(g_GraphicsSys->GetCurrentCamera().GetPosition()));
        glUniform1f(FragBlinnShininessUniform, Shininess);
        glUniform1fv(FragBlinnDistanceAttConstUniform, ARRAYSIZE(DistanceAttConstants), &DistanceAttConstants[0]);
        glUniform1i(FragBlinnDistanceAttBoolUniform, DistanceAtt);
        glUniform1f(FragBlinnNearPlaneLocation, NearPlane);
        glUniform1f(FragBlinnFarPlaneLocation, FarPlane);
        glUniform1i(FragBlinnAtmosphericAttBoolUniform, AtmosphericAtt);
        glUniform4fv(FragBlinnAtmosphericAttIntesityUniform, 1, glm::value_ptr(AtmosphericIntensity));

        glUniform4fv(FragBlinnGlobalAmbientUniform, 1, glm::value_ptr(GlobalAmbient));

        glUniform1i(FragBlinnTexturesUniform, Textures);

        glUniformMatrix4fv(FragBlinnModelModelToWorldUniform, 1, GL_FALSE, &ModelToWorld[0][0]);
        glUniformMatrix4fv(FragBlinnModelWorldToViewUniform, 1, GL_FALSE, &WorldToView[0][0]);
        glUniformMatrix4fv(FragBlinnModelViewToProjectionUniform, 1, GL_FALSE, &ViewToProjection[0][0]);
        glDrawElements(GL_TRIANGLES, triangles.size(), GL_UNSIGNED_SHORT, 0);
        texture->unBind();

#pragma endregion
      }
    }


    break;
  }
  case Shape:
    if (g_GraphicsSys->GetDebugDraw())
    {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else
    {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    fullmatrix = ViewToProjection  * WorldToView * ModelToWorld * scale;
    glUseProgram(SimpleProgram);
    vao->Bind();
    glUniformMatrix4fv(SimpleMatUniform, 1, GL_FALSE, &fullmatrix[0][0]);
    glDrawElements(GL_TRIANGLES, triangles.size(), GL_UNSIGNED_SHORT, 0);
  }

}

void Mesh::Debug_Draw(glm::mat4 matrix)
{
  glClearColor(0.4f, 0.4f, 0.4f, 0.4f);


  glUseProgram(SimpleProgram);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  vao->Bind();
  glUniformMatrix4fv(SimpleMatUniform, 1, GL_FALSE, &matrix[0][0]);
  glDrawElements(GL_TRIANGLES, triangles.size(), GL_UNSIGNED_SHORT, 0);

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  if (g_GraphicsSys->GetVertexNormalDraw())
  {
    glm::vec3 pos, nor;

    for (unsigned i = 0; i < vertices.size(); ++i){

      pos = glm::vec3(vertices.at(i).position.x, vertices.at(i).position.y, vertices.at(i).position.z);
      nor = glm::vec3(vertices.at(i).normal.x / 5.0f, vertices.at(i).normal.y / 5.0f, vertices.at(i).normal.z / 5.0f);
      glLineWidth(2.5);

      glBegin(GL_LINES);
      glVertex3f(pos.x, pos.y, pos.z);
      glVertex3f(pos.x + nor.x, pos.y + nor.y, pos.z + nor.z);
      glEnd();
    }
  }

  if (g_GraphicsSys->GetFaceNormalDraw())
  {
    for (unsigned i = 0; i < triangles.size(); i += 3)
    {
      glm::vec3 nor = glm::cross((vertices.at(triangles.at(i + 1)).position - vertices.at(triangles.at(i)).position),
                                 (vertices.at(triangles.at(i + 2)).position - vertices.at(triangles.at(i)).position));

      //nor.x *= 10.0f;
      //nor.y *= 10.0f;
      //nor.z *= 10.0f;

      glm::vec3 pos = glm::vec3(vertices.at(triangles.at(i)).position + vertices.at(triangles.at(i + 1)).position + vertices.at(triangles.at(i + 2)).position);
      pos.x /= 3.0f;
      pos.y /= 3.0f;
      pos.z /= 3.0f;

      glBegin(GL_LINES);
      glVertex3f(pos.x, pos.y, pos.z);
      glVertex3f(pos.x + nor.x, pos.y + nor.y, pos.z + nor.z);
      glEnd();
    }
  }
}