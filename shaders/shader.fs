#version 330

out vec4 FragColor;
in vec3 pos;
in vec3 Normal0;
in vec2 TextCoord;

struct PointLightAttenuation
{
    float Constant;
    float Linear;
    float Exp;
};

struct Light
{
    vec3 color;
    float diffuseIntensity;
    float ambientIntensity;
};

struct DirectionalLight
{
    vec3 direction;  
    Light light;
};

const int kMaxPointLights = 1;

struct PointLight
{
    Light light;
    vec3 position;
};

struct SpecularLight
{
    float intensity;
    float power;

};

uniform vec3 cameraPos;
uniform vec3 position;
uniform SpecularLight gSpecularLight;
uniform PointLightAttenuation gPointLightAttenuation;
uniform DirectionalLight gDirectionalLight;
uniform int gPointlightsNumber;
uniform sampler2D gSampler; 
uniform PointLight pointlights[kMaxPointLights];





vec4 CalculateLight(Light lght, vec3 direction)
{
    vec4 AmbientColor = vec4(lght.color * lght.ambientIntensity, 1.0f);
    float DiffuseFactor = dot(normalize(Normal0), -direction);
    vec4 DiffuseColor = vec4(0);
    vec4 SpecularColor = vec4(0);

    if (DiffuseFactor > 0) {
        DiffuseColor = vec4(lght.color * lght.diffuseIntensity * DiffuseFactor, 1.0f);
        vec3 viewVector = normalize(cameraPos - position);
        vec3 ReflectVector = normalize(reflect(direction, Normal0));

        float SpecularFactor = dot(viewVector, ReflectVector);
        if (SpecularFactor > 0)
        {
            SpecularFactor = pow(SpecularFactor, gSpecularLight.power);
            SpecularColor = vec4(lght.color * SpecularFactor * gSpecularLight.intensity, 1.0f);
        }
    }
    else {
        DiffuseColor = vec4(0, 0, 0, 0);
    }
    return AmbientColor + DiffuseColor + SpecularColor;
}

vec4 CalcPointLight(int index)
{
    vec3 direction = cameraPos - pointlights[index].position;
    float distance = length(direction);
    direction = normalize(direction);
    vec4 Color = CalculateLight(pointlights[index].light, direction);
    float attenuation = gPointLightAttenuation.Constant + 
                        gPointLightAttenuation.Linear * distance +
                        gPointLightAttenuation.Exp * distance * distance;
    return Color  / attenuation;
}

vec4 CalcuteDirectionalLight()
{
    return CalculateLight(gDirectionalLight.light, gDirectionalLight.direction);
}

void main()
{
    vec4 totalLight = CalcuteDirectionalLight();
    for (int i = 0; i < gPointlightsNumber; i++)
    {
        totalLight += CalcPointLight(i);
    }
    FragColor = texture2D(gSampler, TextCoord.xy) * totalLight;
}
