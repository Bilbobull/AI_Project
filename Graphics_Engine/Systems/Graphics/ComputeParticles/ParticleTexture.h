#ifndef _PARTICLETEXTURE_
#define _PARTICLETEXTURE_

#include "../Graphics_Headers.h"

#include <stdexcept>
#include <string>

#include "tga.h"

class ParticleTexture{
private:
	GLuint	_textureID;
	GLint	_uniTexture;

	void deleteTexture();

public:

	~ParticleTexture(){
		deleteTexture();
	}

void loadTexture(const std::string& path);
void useTexture(const GLuint shaderProgramID);

};

#endif