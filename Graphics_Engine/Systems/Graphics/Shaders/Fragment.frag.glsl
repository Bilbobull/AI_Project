#version 430

out vec4 outColor;

uniform vec4 Color;
uniform sampler2D image;

void main ()
{
  outColor = texture2D (image, gl_PointCoord);
  outColor = Color;
}
