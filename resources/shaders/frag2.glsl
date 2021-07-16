varying vec3 oColor;
varying vec3 oFragPos;
varying vec3 oNormal;
varying vec2 oUV;
varying float oDp;

uniform vec3 uCameraPos;

uniform sampler2D uTexture;

/*combine all three to make PHONG LIGTING JAAAAAAA*/
void main() 
{
    /*ambient lighting*/
    //vec3 lightColor = vec3(0.9803, 0.9372, 0.537);
    //float ambientStrength = 0.3;
    //vec3 ambient = ambientStrength * lightColor;

    /*difuse lighting*/
    //vec3 lightPos = vec3(0.0, 1.0, -1.0);
    //vec3 lightDir = normalize(lightPos - oFragPos);
    //float diff = max(dot(oNormal, lightDir), 0.0);
    //vec3 diffuse = diff * lightColor;

    /*specular lighting*/
    //float specularStrength = 0.5;
    //vec3 viewDir = normalize(uCameraPos - oFragPos);
    //vec3 reflectDir = reflect(-lightDir, oNormal);
    //float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16);
    //vec3 specular = specularStrength * spec * lightColor;

    //vec3 res = ;//(ambient + diffuse + specular) /** iColor/**/;
    gl_FragColor = texture2D(uTexture, oUV);
}