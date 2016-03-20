#pragma once
#include "Graphics_Headers.h"
#include <string>

class Texture
{
public:
  Texture(std::string filename);
  void TexBind(void);
  void NorBind(void);
  void unBind(void);

  bool TextureYesorNo(void){ if (Texformat != NULL) return true;
                      else return false; }

private:
  std::string TexFile;
  int TexWidth;
  int TexHeight;
  int TexnumChannels;
  GLenum Texformat;
  unsigned char* Texpixels;
  GLuint texture;
  bool TexhasAlpha;


  std::string NorFile;
  int NorWidth;
  int NorHeight;
  int NornumChannels;
  GLenum Norformat;
  unsigned char* Norpixels;
  GLuint normaltexture;
  bool NorhasAlpha;



  void createGLTexture();
  void createGLNormalTexture();
};