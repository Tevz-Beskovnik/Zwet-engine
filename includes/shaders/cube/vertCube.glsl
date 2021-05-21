#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 iColor;
layout(location = 2) in vec3 iNormal;
layout(location = 3) in vec2 iUV;

out vec3 oColor;
out vec3 oFragPos;
out vec3 oNormal;
out vec2 oUV;

/*uniform mat4 uWorld;*/
uniform mat4 uWorldInvTran;
uniform vec3 uObjPos;

mat4 trans = mat4(
	1.0, 0.0, 0.0, uObjPos.x,
	0.0, 1.0, 0.0, uObjPos.y,
	0.0, 0.0, 1.0, uObjPos.z,
	0.0, 0.0, 0.0, 1.0
);

void main()
{
	vec4 pos = vec4(position, 1.0);// * trans;
	vec4 res = pos;
	gl_Position = res;
	oFragPos = res.xyz;
	oColor = iColor;
	oUV = iUV;
	oNormal = normalize(mat3(uWorldInvTran) * iNormal);
}