#version 330

out vec4 FragColor;
in vec4 pos;

void main()
{
    FragColor = vec4(0.0, 0.5+ pos.y , .5+ pos.x , .4);
}
