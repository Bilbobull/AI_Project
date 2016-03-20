#version 330

in vec3 Normal;
in vec4 Color;
in vec2 Texcoord;

uniform sampler2D Texture;
uniform sampler2D normalTexture;
uniform int Textures;

layout (location = 0) out vec4 outColor;
layout (location = 1) out vec4 outColorNormal;



void main()
{

	if(Textures == 1)
	  outColor = texture2D (Texture, Texcoord) * Color;  //

	else
	   outColor = Color;

	outColorNormal = texture2D (Texture, Texcoord) * Color; 
}