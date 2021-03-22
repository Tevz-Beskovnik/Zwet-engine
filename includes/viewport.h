#pragma once

#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<fstream>
#include<string>
#include<vector>
#include "vecs.h"

void convertMeshToArray(const vecs::mesh, std::vector<float>&);

class Viewport {

public:
	std::string vertexDir;
	std::string fragDir;
	std::string geometryDir;
	std::vector<float> startVec;
	GLenum drawType;
	int vecSize;

	Viewport(std::string, std::string, std::string, std::vector<float>&, GLenum);

	unsigned int initRender();

	int screenResolution();
private:

	void readShader(std::string, std::string&);

	unsigned int compileShader(unsigned int, const std::string&);

	unsigned int createShader(const std::string, const std::string, const std::string);
};