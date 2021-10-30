attribute vec3 position;
attribute vec3 iColor;
attribute vec3 iNormal;
attribute vec2 iUV;

varying vec3 oColor;
varying vec3 oFragPos;
varying vec3 oNormal;
varying vec2 oUV;

/*uniform mat4 uWorld;*/
uniform float uTime;
uniform mat4 uWorldInvTran;
uniform mat4 uYawMat;
uniform mat4 objYaw;
uniform mat4 objPitch;
uniform mat4 uPitchMat;
uniform vec3 uObjPos;
uniform vec3 uCameraPos;
uniform mat4 uViewMat;

mat4 trans = mat4(
	1.0, 0.0, 0.0, uCameraPos.x,
	0.0, 1.0, 0.0, uCameraPos.y,
	0.0, 0.0, 1.0, uCameraPos.z,
	0.0, 0.0, 0.0, 1.0
);

mat4 trans2 = mat4(
	1.0, 0.0, 0.0, -uCameraPos.x,
	0.0, 1.0, 0.0, -uCameraPos.y,
	0.0, 0.0, 1.0, -uCameraPos.z,
	0.0, 0.0, 0.0, 1.0
);

void main()
{
	vec4 pos = vec4(position, 1.0) * trans;
	vec4 res = /*vec4(position + uCameraPos, 1.0);/**/(vec4(pos.xyz, 1.0) * (trans2 * uPitchMat * uYawMat * trans));/**/
	gl_Position = res * uViewMat;
	oFragPos = vec4(res * uViewMat).xyz;
	oColor = iColor;
	oUV = iUV;
	oNormal = vec3(normalize(uWorldInvTran * vec4(iNormal, 0.0)));
}