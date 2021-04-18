#pragma once

#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include "vecs.h"

void convertMeshToArray(const vecs::mesh, std::vector<float>&);

void screenResolution(float&, float&);

struct ShaderInfo
{
	std::string shader;
	unsigned int shaderType;
};

class Viewport {

public:
	std::vector<float> startVec;
	GLenum drawType;
	int vecSize;

	Viewport(std::vector<float>&, GLenum);

	vecs::mat4 createWorldMatrix(float, float, float);

	vecs::mat4 createViewMatrix(vecs::mat4, vecs::vec3&, vecs::vec3&, vecs::vec3&, float);

	unsigned int bindBuffer(std::vector<ShaderInfo>, bool);
};

void readShader(std::string, std::string&);

unsigned int compileShader(unsigned int, const std::string&);

vecs::mat4 pointAtMatrix(vecs::vec3&, vecs::vec3&, vecs::vec3&);

unsigned int createShader(std::vector<ShaderInfo>);