#version 330

in vec3 position;
in vec4 color;

out vec4 Color;

uniform mat4 matrix;

void main(void)
{
	vec4 eyePos = vec4(position , 1.0);
	gl_Position = matrix * eyePos;
	Color = color;
}