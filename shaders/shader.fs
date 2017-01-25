#version 330

out vec4 FragColor;
in vec3 pos;
in vec3 Normal0;
in vec2 TextCoord;

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

PointLightAttenuation
{
    float Constant;
    float Linear;
    float Exp;
};

struct Light
{
    vec3 Color;
    float DiffuseIntensity;
    float AmbientIntensity;
};

stuct DirectionalLight
{
    vec3 Direction;  
    Light m_light;
};

const int kMaxPointLights;

struct PointLight
{
    Light m_light;
    vec3 position;
};


uniform PointLight pointlights[kMaxPointLights];
uniform int gPointlightsNumber;

uniform DirectionalLight gDirectionalLight;
uniform float gMatSpecularIntensity;
uniform float gSpecularPower;

uniform SpecularLight gSpecularLight;
uniform sampler2D gSampler; 


vec4 CalculateLight(Light lght, vec direction)
{
    
}

vec4 CelacuteDirectionalLight(Light lght)
{
    return CalculateLight(lght, )
}

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
    FragColor = texture2D(gSampler, TextCoord.xy) * (AmbientColor + DiffuseColor + SpecularColor);
}
