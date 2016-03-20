#include "Texture.h"
#include <iostream>

Texture::Texture(std::string filename)
{
  TexFile = filename + "_Diffuse.png";
  std::string path = "Textures\\" + TexFile;
  
  Texpixels = stbi_load(path.c_str(), &TexWidth, &TexHeight, &TexnumChannels, 0);
  if (Texpixels)
  {
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    createGLTexture();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, 0);
  }

  else
  {
    std::cout << "Wrong Texture filename: " << TexFile << std::endl;
  }



  NorFile = filename + "_Normal.png";
  path = "Textures\\" + NorFile;
  Norpixels = stbi_load(path.c_str(), &NorWidth, &NorHeight, &NornumChannels, 0);

  if (Norpixels)
  {
    glGenTextures(1, &normaltexture);
    glBindTexture(GL_TEXTURE_2D, normaltexture);
    createGLNormalTexture();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, 0);
  }

  else
  {
    std::cout << "Wrong Texture filename: " << NorFile << std::endl;
  }
}

void Texture::TexBind(void)
{
  glBindTexture(GL_TEXTURE_2D, texture);
}

void Texture::NorBind(void)
{
  glBindTexture(GL_TEXTURE_2D, normaltexture);
}

void Texture::unBind(void)
{
  glBindTexture(GL_TEXTURE_2D, 0);
}


void Texture::createGLTexture()
{
  Texformat = TexnumChannels == 4 ? GL_RGBA : GL_RGB;
  glTexImage2D(GL_TEXTURE_2D, 0, Texformat, TexWidth, TexHeight, 0, Texformat, GL_UNSIGNED_BYTE, Texpixels);
}

void Texture::createGLNormalTexture()
{
  Norformat = NornumChannels == 4 ? GL_RGBA : GL_RGB;
  glTexImage2D(GL_TEXTURE_2D, 0, Norformat, NorWidth, NorHeight, 0, Norformat, GL_UNSIGNED_BYTE, Norpixels);
}