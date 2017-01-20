#version 330

out vec4 FragColor;
in vec3 pos;
in vec3 Normal0;

struct DirectionalLight
{
    vec3 Color;
    float AmbientIntensity;
    float DiffuseIntensity;
    vec3 Direction;
};

struct SpecularLight
{
    float SpecularPower;
    vec3 cameraPos;
    float SpecularIntensity;
};
 
uniform DirectionalLight gDirectionalLight;
uniform SpecularLight gSpecularLight;

void main()
{
	vec4 AmbientColor = vec4(gDirectionalLight.Color * gDirectionalLight.AmbientIntensity, 1.0f);
	float DiffuseFactor = dot(normalize(Normal0), -gDirectionalLight.Direction);
	vec4 DiffuseColor;
    vec4 SpecularColor;

    if (DiffuseFactor > 0) {
        DiffuseColor = vec4(gDirectionalLight.Color * gDirectionalLight.DiffuseIntensity * DiffuseFactor, 1.0f);
        vec3 viewVector = normalize(gSpecularLight.cameraPos - pos);
        vec3 ReflectVector = normalize(reflect(gDirectionalLight.Direction, Normal0));

        float SpecularFactor = dot(viewVector, ReflectVector);
        if (SpecularFactor > 0)
        {
            SpecularFactor = pow(SpecularFactor, gSpecularLight.SpecularPower);
            SpecularColor = vec4(gDirectionalLight.Color * SpecularFactor * gSpecularLight.SpecularIntensity, 1.0f);
        }
    }
    else {
        DiffuseColor = vec4(0, 0, 0, 0);
    }
    FragColor = (AmbientColor + DiffuseColor + SpecularColor);
}
