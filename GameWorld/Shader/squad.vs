#version 330 core

layout(location = 0) in vec3 aPos;

uniform mat4 uVPmat;

out vec3 vPos;

void main()
{
	vPos = vec3(uVPmat * vec4(aPos, 1.0));
	gl_Position = vec4(vPos, 1.0);
}

