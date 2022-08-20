attribute vec3 position;
attribute vec3 iColor;
attribute vec3 iNormal;
attribute vec2 iUV;

varying vec3 oColor;
varying vec3 oFragPos;
varying vec3 oNormal;
varying vec2 oUV;

/*uniform mat4 uWorld;*/
uniform mat4 uWorldInvTran;
uniform vec3 uObjPos;
uniform mat4 uViewMat;

mat4 trans = mat4(
	1.0, 0.0, 0.0, uObjPos.x,
	0.0, 1.0, 0.0, uObjPos.y,
	0.0, 0.0, 1.0, uObjPos.z,
	0.0, 0.0, 0.0, 1.0
);

void main()
{
	vec4 pos = vec4(position, 1.0) * trans;
	vec4 res = uViewMat * pos;
	gl_Position = res;
	oFragPos = res.xyz;
	oColor = iColor;
	oUV = iUV;
	oNormal = vec3(normalize(uWorldInvTran * vec4(iNormal, 0.0)));
}