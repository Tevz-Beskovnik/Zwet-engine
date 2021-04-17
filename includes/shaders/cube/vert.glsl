#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 iColor;
layout(location = 2) in vec3 iNormal;

out vec3 oColor;
out vec3 oFragPos;
out vec3 oNormal;

uniform mat4 uWorld;
uniform float uTime;
uniform mat4 uWorldInvTran;

void main()
{
	vec4 res = uWorld * vec4(position, 1.0);
	gl_Position = res;
	oFragPos = res.xyz;
	oColor = iColor;
	oNormal = normalize(mat3(uWorldInvTran) * iNormal);
}