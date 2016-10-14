#version 330

layout (location = 0) in vec3 Position;
uniform mat4 WVP;
out vec4 pos;
void main()
{
    gl_Position = transpose(WVP) * vec4(Position, 1.0);
    pos = vec4(Position, 1.0);
}