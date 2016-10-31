#version 330

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;
uniform mat4 WVP;
uniform mat4 gWorld;
out vec4 pos;
out vec3 Normal0;
void main()
{
    gl_Position = transpose(WVP) * vec4(Position, 1.0);
    pos = vec4(Position, 1.0);
    Normal0 = (transpose(gWorld) * vec4(Normal, 0)).xyz;
}