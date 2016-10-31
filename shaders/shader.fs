#version 330

out vec4 FragColor;
in vec4 pos;
in vec3 Normal0;

struct DirectionalLight
{
    vec3 Color;
    float AmbientIntensity;
    float DiffuseIntensity;
    vec3 Direction;
};
 
uniform DirectionalLight gDirectionalLight;   

void main()
{
	vec4 AmbientColor = vec4(gDirectionalLight.Color * gDirectionalLight.AmbientIntensity, 1.0f);
	float DiffuseFactor = dot(normalize(Normal0), -gDirectionalLight.Direction);
	vec4 DiffuseColor;

    if (DiffuseFactor > 0) {
        DiffuseColor = vec4(gDirectionalLight.Color * gDirectionalLight.DiffuseIntensity * DiffuseFactor, 1.0f);
    }
    else {
        DiffuseColor = vec4(0, 0, 0, 0);
    }

    FragColor =  (AmbientColor + DiffuseColor);
}
