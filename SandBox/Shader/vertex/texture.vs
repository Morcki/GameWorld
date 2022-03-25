#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTexCoord;

uniform vec3 uTranslateVec;
uniform mat4 uVPmat;

out vec2 texCoord;

void main()
{
	vec3 pos = uTranslateVec + aPosition;
	pos = vec3(uVPmat * vec4(pos, 1.0));
	texCoord = aTexCoord;
	gl_Position = vec4(pos, 1.0);
}
