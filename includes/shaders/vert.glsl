#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 iColor;

out vec3 oColor;

uniform mat4 uRotation;
uniform float uTime;
uniform mat4 uProjMat;

void main()
{
	vec4 boind = uRotation * vec4(position, 1.0);
	vec4 res = boind;
    res.z -= 1.0;

	gl_Position = vec4(res.xyz, 1.0);
	oColor = iColor;
}