#pragma include "Assets/Shader/ShaderHeader.glsl"

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexcoord;
out vec2 vTexcoord;
out vec3 vPosition;
out vec3 vNormal;
uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProj;
uniform mat4 uModelInvT;

void main()
{
	vTexcoord   = aTexcoord;
	vNormal     = mat3(uModelInvT) * aNormal;
	vPosition   = vec3(uModel * vec4(aPosition, 1.0));
	gl_Position = uProj * uView * vec4(vPosition, 1.0);
}
