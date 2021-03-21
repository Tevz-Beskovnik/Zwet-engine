#version 330 core

layout(location = 0) out vec4 color;

in vec3 oColor;

vec3 lightColor = vec3(1.0, 1.0, 1.0);

void main() 
{
    color = vec4(oColor, 1.0);
}