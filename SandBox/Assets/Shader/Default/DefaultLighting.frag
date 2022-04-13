#pragma include "Assets/Shader/ShaderHeader.glsl"
#pragma include "Assets/Shader/Utils/LightUtils.glsl"
#pragma include "Assets/Shader/Utils/GamaCorrection.glsl"

layout(location = 0) out vec4 fragColor;

in vec2 vTexcoords;
in vec3 vPosition;
in vec3 vNormal;

uniform vec3 uCameraPos;
uniform LightDirectional uLightDirectional;
uniform Material uMat;
uniform vec3 uAmbientLightColor;

void main()
{
	vec3 normal = normalize(vNormal);
	vec3 viewDir  = normalize(uCameraPos - vPosition);
	vec3 color = CalcLightDirectional(uLightDirectional, uMat, normal, viewDir);
	vec4 ambient = vec4(uAmbientLightColor, 1.0) * uMat.DiffuseAlbedo;
	
	fragColor = vec4(color, 1.0) + ambient;
	fragColor.rgb = ConvertHdrToLdr(fragColor.rgb);
	fragColor.rgb = CorrectionGama(fragColor.rgb);

	fragColor.a = uMat.DiffuseAlbedo.a;
}