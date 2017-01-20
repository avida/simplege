#version 330

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;
uniform mat4 WVP;
uniform mat4 gWorld;
out vec3 pos;
out vec3 Normal0;
void main()
{
    gl_Position = WVP * vec4(Position, 1.0);
    pos = (gWorld * vec4(Position, 1.0)).xyz;
    //WorldPos0   = (gWorld * vec4(Position, 1.0)).xyz;
    Normal0 = (gWorld * vec4(Normal, 0)).xyz;
}