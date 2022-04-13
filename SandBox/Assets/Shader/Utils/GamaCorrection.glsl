
vec3 ConvertHdrToLdr(vec3 color)
{
	// HDR tonemapping
	color = color / (color + vec3(1.0));
	return color;
}

vec3 CorrectionGama(vec3 color)
{
	// gamma correct
	color = pow(color, vec3(1.0 / 2.2));
	return color;
}

