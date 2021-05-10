#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 iColor;
layout(location = 2) in vec3 iNormal;

out vec3 oColor;
out vec3 oFragPos;
out vec3 oNormal;

/*uniform mat4 uWorld;*/
uniform float uTime;
uniform mat4 uWorldInvTran;
uniform mat4 uYawMat;
uniform mat4 uPitchMat;
uniform vec3 uObjPos;
uniform vec3 uCameraPos;

mat4 trans = mat4(
	1.0, 0.0, 0.0, uCameraPos.x,
	0.0, 1.0, 0.0, uCameraPos.y,
	0.0, 0.0, 1.0, uCameraPos.z,
	0.0, 0.0, 0.0, 1.0
);

void main()
{
	vec4 res = /*vec4(uObjPos + position, 1.0);*/vec4(position + uCameraPos, 1.0) * trans * uPitchMat * uYawMat;/**/
	gl_Position = res;
	oFragPos = res.xyz;
	oColor = iColor;
	oNormal = normalize(mat3(uWorldInvTran) * iNormal);
}