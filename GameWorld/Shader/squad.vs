#version 330 core

layout(location = 0) in vec3 aPos;

uniform vec3 uTranslateVec;
uniform mat4 uVPmat;
uniform vec3 uColor;

out vec3 vColor;

void main()
{
	float scale = 0.1;
	vec3 pos = scale * (uTranslateVec + aPos);
	pos = vec3(uVPmat * vec4(pos, 1.0));
	vColor = uColor;
	gl_Position = vec4(pos, 1.0);
}

