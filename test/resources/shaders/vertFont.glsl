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

void main()
{
	gl_Position = vec4(position, 1.0);

    oUV = iUV;
}