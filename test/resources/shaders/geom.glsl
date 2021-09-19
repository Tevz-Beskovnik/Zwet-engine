#version 150 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in vec3 oColor[];
in vec3 oFragPos[];
in vec3 oNormal[];

out vec3 iColor;
out vec3 iFragPos;
out vec3 iNormal;
out float iDp;

uniform mat4 uViewMat;

void main()
{
	vec4 vert1 = uViewMat * gl_in[0].gl_Position;
	vec4 vert2 = uViewMat * gl_in[1].gl_Position;
	vec4 vert3 = uViewMat * gl_in[2].gl_Position;
	
	gl_Position = vert1;
	iFragPos = oFragPos[0];
	iColor = oColor[0];
	iNormal = oNormal[0];
	EmitVertex();

	gl_Position = vert2;
	iFragPos = oFragPos[1];
	iColor = oColor[1];
	iNormal = oNormal[1];
	EmitVertex();

	gl_Position = vert3;
	iFragPos = oFragPos[2];
	iColor = oColor[2];
	iNormal = oNormal[2];
	EmitVertex();
	EndPrimitive();
}