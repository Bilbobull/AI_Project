#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 vertexColor;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec2 texcoord;

uniform mat4 ModelToWorldMatrix;
uniform mat4 WorldToViewMatrix;
uniform mat4 ViewToProjectionMatrix;

out vec3 Color;
out vec3 Normal;
out vec2 Texcoord;
out vec3 Position;

void main ()
{
  vec4 v = vec4(position, 1.0);

  gl_Position = ViewToProjectionMatrix * WorldToViewMatrix * ModelToWorldMatrix * v;
  Normal = normal;
  Position = position;
  Color = vertexColor;
  Texcoord = texcoord;
}

