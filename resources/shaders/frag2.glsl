#version 330 core

layout(location = 0) out vec4 color;

in vec3 iColor;
in vec3 iFragPos;
in vec3 iNormal;
in vec2 iUV;
in float iDp;

uniform vec3 uCameraPos;

uniform sampler2D uTexture;

/*ambient lighting*/
vec3 lightColor = vec3(0.9803, 0.9372, 0.537);
float ambientStrength = 0.7;
vec3 ambient = ambientStrength * lightColor;

/*difuse lighting*/
vec3 lightPos = vec3(0.0, 1.0, -1.0);
vec3 lightDir = normalize(lightPos - iFragPos);
float diff = max(dot(iNormal, lightDir), 0.0);
vec3 diffuse = diff * lightColor;

/*specular lighting*/
float specularStrength = 0.5;
vec3 viewDir = normalize(uCameraPos - iFragPos);
vec3 reflectDir = reflect(-lightDir, iNormal);
float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16);
vec3 specular = specularStrength * spec * lightColor;

/*combine all three to make PHONG LIGTING JAAAAAAA*/
void main() 
{
    //vec3 res = ;//(ambient + diffuse + specular) /** iColor/**/;
    color = texture(uTexture, iUV);
}