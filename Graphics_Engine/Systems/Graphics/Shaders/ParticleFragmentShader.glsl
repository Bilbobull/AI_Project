#version 330

in vec4 Color;
out vec4 outColor;

uniform sampler2D image;

void main (void)
{
  outColor = texture (image, gl_PointCoord) * Color;
}