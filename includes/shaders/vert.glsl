#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 iColor;

out vec3 oColor;

uniform mat4 uProjMat;
uniform float uTime;
uniform vec2 uRot;

void main()
{
	//z rotation matrix
    mat4 rotZ = mat4(
        cos(-uRot.x * 0.3), -sin(-uRot.x * 0.3), 0.0, 0.0, 
        sin(-uRot.x * 0.3), cos(-uRot.x * 0.3), 0.0, 0.0, 
        0.0, 0.0, 1.0, 0.0, 
        0.0, 0.0, 0.0, 1.0
    );

    //x rotation matrix
    mat4 rotX = mat4(
        1.0, 0.0, 0.0, 0.0,
        0.0, cos(uRot.y * 0.3), -sin(uRot.y * 0.3), 0.0, 
        0.0, sin(uRot.y * 0.3), cos(uRot.y * 0.3), 0.0, 
        0.0, 0.0, 0.0, 1.0
    );

	vec4 boind = rotX * rotZ * vec4(position*0.3, 1.0);
	boind = boind * uProjMat;
    boind.z -= 0.8;
	gl_Position = vec4(boind.xyz, 1.0);
	oColor = iColor;
}