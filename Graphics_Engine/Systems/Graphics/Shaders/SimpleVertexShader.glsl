#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 vertexColor;

uniform mat4 FullTransformMatrix;
 
out vec4 Color;

void main ()
{
  vec4 v = vec4(position, 1.0);

  gl_Position = FullTransformMatrix * v;
  Color = vec4(vertexColor.rbg, 1.0);
}
