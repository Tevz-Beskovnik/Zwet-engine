#pragma once

#define UFLOAT 0
#define UVEC3 1
#define UMAT4 2

#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<fstream>
#include<string>
#include<vector>
#include "vecs.h"

void convertMeshToArray(const vecs::mesh, std::vector<float>&);

void screenResolution(float&, float&);

class Viewport {

public:
	std::string vertexDir;
	std::string fragDir;
	std::string geometryDir;
	std::vector<float> startVec;
	GLenum drawType;
	int vecSize;

	Viewport(std::string, std::string, std::string, std::vector<float>&, GLenum);

	vecs::mat4 createWorldMatrix(float, float, float);

	vecs::mat4 createViewMatrix(vecs::mat4, vecs::vec3&, vecs::vec3&, vecs::vec3&);

	unsigned int initRender();
private:

	void readShader(std::string, std::string&);

	unsigned int compileShader(unsigned int, const std::string&);

	vecs::mat4 pointAtMatrix(vecs::vec3&, vecs::vec3&, vecs::vec3&);

	unsigned int createShader(const std::string, const std::string, const std::string);
};