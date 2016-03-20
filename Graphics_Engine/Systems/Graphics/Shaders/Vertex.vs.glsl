#version 430

in vec4 position;
uniform mat4 mvp;

void main ()
{
  gl_Position =  vec4 (position.xyz, 1.0);
}