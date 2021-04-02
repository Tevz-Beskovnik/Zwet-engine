#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 iColor;

out vec3 oColor;

uniform mat4 uWorld;
uniform float uTime;

void main()
{
	gl_Position = uWorld * vec4(position, 1.0);
	oColor = iColor;
}