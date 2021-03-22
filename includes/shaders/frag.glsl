#version 330 core

layout(location = 0) out vec4 color;

in vec3 iColor;
in float iDp;

vec3 lightColor = vec3(1.0, 1.0, 1.0);
float ambientStrength = 0.1;
vec3 ambient = ambientStrength * lightColor;

float diff = max(iDp, 0.0);
vec3 diffuse = diff * lightColor;

void main() 
{
    vec3 res = (ambient + diffuse) * iColor;

    color = vec4(res, 1.0);
}