#pragma include "Assets/Shader/ShaderDefines.glsl"

#define MaxLights 16

const float PI = 3.14159265359;

struct Light
{
    vec3  Strength;
    float FalloffStart; // point/spot light only
    vec3  Direction;    // directional/spot light only
    float FalloffEnd;   // point/spot light only
    vec3  Position;     // point light only
    float SpotPower;    // spot light only
};

struct LightDirectional
{
	vec3 LightColor;
	vec3 LightDir;
};

struct Material
{
	vec4 DiffuseAlbedo;
	float Metallic;
	float Shininess;
};

float CalcAttenuation(float d, float falloffStart, float falloffEnd)
{
    // Linear falloff.
    return clamp((falloffEnd-d) / (falloffEnd - falloffStart), 0.0, 1.0);
}

float distributionGGX(vec3 normal, vec3 halfVec, float roughness) {
	float a2 = roughness * roughness * roughness * roughness;
	float NdotH = max(dot(normal, halfVec), 0.0);
	float denom = (NdotH * NdotH * (a2 - 1.0) + 1.0);
	return a2 / (PI * denom * denom);
}

float geometrySchlickGGX(float NdotV, float roughness) {
	float r = (roughness + 1.0);
	float k = (r * r) / 8.0;
	return NdotV / (NdotV * (1.0 - k) + k);
}

float geometrySmith(vec3 N, vec3 V, vec3 L, float roughness) {
	return geometrySchlickGGX(max(dot(N, L), 0.0), roughness) *
		geometrySchlickGGX(max(dot(N, V), 0.0), roughness);
}

vec3 SchlickFresnel(vec3 R0, vec3 normal, vec3 lightDir)
{
	float cosIncidentAngle = clamp(dot(normal, lightDir), 0.0, 1.0);

	float f0 = 1.0 - cosIncidentAngle;
	vec3 refectPercent = R0 + (1.0 - R0) * (f0 * f0 * f0 * f0 * f0);
	
	return refectPercent;
}

vec3 BlinnPhong(vec3 lightStrength, vec3 lightDir, vec3 normal, vec3 viewDir, Material mat)
{
	vec3 F0 = vec3(0.04);
	F0 = mix(F0, mat.DiffuseAlbedo.rgb, mat.Metallic);

	float m = mat.Shininess * 256.0f;
	vec3 halfVec = normalize(lightDir + viewDir);
	float roughnessFactor = (m + 8.0) * pow(max(dot(halfVec, normal), 0.0), m) / 8.0;

	vec3 fresnelFactor = SchlickFresnel(F0, halfVec, lightDir);
	
	vec3 specAlbedo = fresnelFactor * roughnessFactor;
	specAlbedo = specAlbedo / (specAlbedo + 1.0);
	return (mat.DiffuseAlbedo.rgb + specAlbedo) * lightStrength;
}

vec3 PsycialBasedLighting(vec3 lightStrength, vec3 lightDir, vec3 normal, vec3 viewDir, Material mat)
{// CookTorranceBRDF

	// calculate reflectance at normal incidence; if dia-electric (like plastic) use F0 
	// of 0.04 and if it's a metal, use the albedo color as F0 (metallic workflow)    
	vec3 F0 = vec3(0.04);
	F0 = mix(F0, mat.DiffuseAlbedo.rgb, mat.Metallic);

	vec3 halfVec = normalize(lightDir + viewDir);
	float NDF = distributionGGX(normal, halfVec, 1.0 - mat.Shininess);
	float G   = geometrySmith(normal, viewDir, lightDir, 1.0 - mat.Shininess);
	vec3  F   = SchlickFresnel(F0, halfVec, lightDir);
	
	// kS is equal to Fresnel
	vec3 kS = F;
	// for energy conservation, the diffuse and specular light can't
	// be above 1.0 (unless the surface emits light); to preserve this
	// relationship the diffuse component (kD) should equal 1.0 - kS.
	vec3 kD = vec3(1.0) - kS;
	// multiply kD by the inverse metalness such that only non-metals 
	// have diffuse lighting, or a linear blend if partly metal (pure metals
	// have no diffuse light).
	kD *= 1.0 - mat.Metallic;

	vec3  numerator = NDF * G * F;
	float denominator = 4.0 * max(dot(normal, viewDir), 0.0) * max(dot(normal, lightDir), 0.0);
	vec3  specular = numerator / max(denominator, 0.001);

	float NdotL = max(dot(normal, lightDir), 0.0);
	// scale light by NdotL
	vec3 color = (kD * mat.DiffuseAlbedo.rgb / PI + specular) * lightStrength * NdotL;
	return color;
}

//---------------------------------------------------------------------------------------
// Evaluates the lighting equation for directional lights.
//---------------------------------------------------------------------------------------

vec3 CalcLightDirectional(LightDirectional L, Material mat, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = -normalize(L.LightDir);
	float ndotL = max(dot(lightDir, normal), 0.0);
	vec3 lightStrength = L.LightColor * ndotL;
#if (USE_LIGHTING_MODE == USE_BLIINPHONE_LIGHTING)
	return BlinnPhong(lightStrength, lightDir, normal, viewDir, mat);
#elif (USE_LIGHTING_MODE == USE_PYSICIAL_LIGHTING)
	return PsycialBasedLighting(lightStrength, lightDir, normal, viewDir, mat);
#else
	return vec3(0.0);
#endif
}

//---------------------------------------------------------------------------------------
// Evaluates the lighting equation for point lights.
//---------------------------------------------------------------------------------------
vec3 ComputePointLight(Light L, Material mat, vec3 pos, vec3 normal, vec3 viewDir)
{
    // The vector from the surface to the light.
    vec3 lightDir = L.Position - pos;

    // The distance from surface to light.
    float d = length(lightDir);

    // Range test.
    if(d > L.FalloffEnd)
        return 0.0f;

    // Normalize the light vector.
    lightDir /= d;

    // Scale light down by Lambert's cosine law.
    float ndotl = max(dot(lightDir, normal), 0.0f);
    vec3 lightStrength = L.Strength * ndotl;

    // Attenuate light by distance.
    float att = CalcAttenuation(d, L.FalloffStart, L.FalloffEnd);
    lightStrength *= att;

    return BlinnPhong(lightStrength, lightDir, normal, viewDir, mat);
}

//---------------------------------------------------------------------------------------
// Evaluates the lighting equation for spot lights.
//---------------------------------------------------------------------------------------
vec3 ComputeSpotLight(Light L, Material mat, vec3 pos, vec3 normal, vec3 viewDir)
{
    // The vector from the surface to the light.
    vec3 lightDir = L.Position - pos;

    // The distance from surface to light.
    float d = length(lightDir);

    // Range test.
    if(d > L.FalloffEnd)
        return 0.0f;

    // Normalize the light vector.
    lightDir /= d;

    // Scale light down by Lambert's cosine law.
    float ndotl = max(dot(lightDir, normal), 0.0f);
    vec3 lightStrength = L.Strength * ndotl;

    // Attenuate light by distance.
    float att = CalcAttenuation(d, L.FalloffStart, L.FalloffEnd);
    lightStrength *= att;

    // Scale by spotlight
    float spotFactor = pow(max(dot(-lightDir, L.Direction), 0.0f), L.SpotPower);
    lightStrength *= spotFactor;

    return BlinnPhong(lightStrength, lightDir, normal, viewDir, mat);
}

vec4 ComputeLighting(Light gLights[MaxLights], Material mat,
                       vec3 pos, vec3 normal, vec3 viewDir,
                       vec3 shadowFactor)
{
    vec3 result = vec3(0.0f);

    int i = 0;

#if (NUM_DIR_LIGHTS > 0)
    for(i = 0; i < NUM_DIR_LIGHTS; ++i)
    {
        result += shadowFactor[i] * ComputeDirectionalLight(gLights[i], mat, normal, viewDir);
    }
#endif

#if (NUM_POINT_LIGHTS > 0)
    for(i = NUM_DIR_LIGHTS; i < NUM_DIR_LIGHTS+NUM_POINT_LIGHTS; ++i)
    {
        result += ComputePointLight(gLights[i], mat, pos, normal, viewDir);
    }
#endif

#if (NUM_SPOT_LIGHTS > 0)
    for(i = NUM_DIR_LIGHTS + NUM_POINT_LIGHTS; i < NUM_DIR_LIGHTS + NUM_POINT_LIGHTS + NUM_SPOT_LIGHTS; ++i)
    {
        result += ComputeSpotLight(gLights[i], mat, pos, normal, viewDir);
    }
#endif 

    return vec4(result, 0.0f);
}