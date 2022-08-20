attribute vec3 position;
attribute vec3 iColor;
attribute vec3 iNormal;
attribute vec2 iUV;

varying vec3 oColor;
varying vec3 oFragPos;
varying vec3 oNormal;
varying vec2 oUV;

uniform mat4 uWorld;
uniform mat4 uWorldInvTran;
uniform mat4 uViewMat;
/*uniform vec3 uCameraPos;*/

void main()
{
	vec4 pos = vec4(position, 1.0) * uWorld;
	vec4 res = uViewMat * pos;
	gl_Position = res;
	oFragPos = res.xyz;
	oColor = iColor;
	oUV = iUV;
	oNormal = vec3(normalize(uWorldInvTran * vec4(iNormal, 0.0)));
}