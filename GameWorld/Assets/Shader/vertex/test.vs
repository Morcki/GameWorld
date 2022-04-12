#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;

uniform mat4 uVPmat;
uniform vec3 uTranslateVec;

out vec3 v_Position;
out vec4 v_Color;
void main()
{
	v_Position = vec3(uVPmat * vec4(uTranslateVec + a_Position, 1.0));
	v_Color = a_Color;
	gl_Position = vec4(v_Position, 1.0);
}