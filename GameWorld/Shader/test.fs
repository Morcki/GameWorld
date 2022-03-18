#version 330 core

layout(location = 0) out vec4 color;
in vec3 position;
void main()
{
	color = vec4(position + 0.5, 1.0);
}
