#version 330 core

layout(location = 0) out vec4 color;
in vec3 vPos;

void main()
{
	color = vec4(vPos, 1.0);
}