#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in vec3 oColor[];

out vec3 iColor;
out float iDp;

uniform mat4 uProjMat;
//uniform mat4 uView;

void main()
{
	vec4 vert1 = gl_in[0].gl_Position;
	vec4 vert2 = gl_in[1].gl_Position;
	vec4 vert3 = gl_in[2].gl_Position;
	
	float dp = dot(normalize(cross(vert2.xyz - vert1.xyz, vert3.xyz - vert1.xyz)), vec3(0.0, 1.0, -1.0));
	
	gl_Position = uProjMat * vec4(vert1);
	iColor = oColor[0];
	iDp = dp;
	EmitVertex();

	gl_Position = uProjMat * vec4(vert2);
	iColor = oColor[1];
	iDp = dp;
	EmitVertex();

	gl_Position = uProjMat * vec4(vert3);
	iColor = oColor[2];
	iDp = dp;
	EmitVertex();
}