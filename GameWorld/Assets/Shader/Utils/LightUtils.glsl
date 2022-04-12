R"(
#define MaxLights 16

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
	vec3 FresnelR0;
	float Shininess;
};

float CalcAttenuation(float d, float falloffStart, float falloffEnd)
{
    // Linear falloff.
    return clamp((falloffEnd-d) / (falloffEnd - falloffStart), 0.0, 1.0);
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
	float m = mat.Shininess * 256.0;
	vec3 halfVec = normalize(lightDir + viewDir);

	float roughnessFactor = (m + 8.0) * pow(max(dot(halfVec, normal), 0.0), m) / 8.0;
	vec3 fresnelFactor = SchlickFresnel(mat.FresnelR0, halfVec, lightDir);
	
	vec3 specAlbedo = fresnelFactor * roughnessFactor;
	specAlbedo = specAlbedo / (specAlbedo + 1.0);
	return (mat.DiffuseAlbedo.rgb + specAlbedo) * lightStrength;
}

//---------------------------------------------------------------------------------------
// Evaluates the lighting equation for directional lights.
//---------------------------------------------------------------------------------------

vec3 CalcLightDirectional(LightDirectional L, Material mat, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = -normalize(L.LightDir);
	float ndotL = max(dot(lightDir, normal), 0.0);
	vec3 lightStrength = L.LightColor * ndotL;
	return BlinnPhong(lightStrength, lightDir, normal, viewDir, mat);
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

)"