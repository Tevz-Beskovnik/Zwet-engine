attribute vec3 position;
attribute vec3 iColor;
attribute vec3 iNormal;
attribute vec2 iUV;

varying vec3 oColor;
varying vec3 oFragPos;
varying vec3 oNormal;

/*uniform mat4 uWorld;*/
uniform float uTime;
uniform mat4 uWorldInvTran;

void main()
{
	vec4 res = uWorld * vec4(position, 1.0);
	gl_Position = res;
	oFragPos = res.xyz;
	oColor = iColor;
	oNormal = vec3(normalize(uWorldInvTran * vec4(iNormal, 0.0)));
}