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

vecs::mat4 createWorldMatrix(vecs::vec3, vecs::vec3, float);

vecs::mat4 createViewMatrix(vecs::mat4, vecs::vec3&, vecs::vec3&, vecs::vec3&, float, float, float);

typedef struct
{
	std::string shader;
	unsigned int shaderType;
} ShaderInfo;

class Viewport {

public:
	std::vector<float> startVec;
	GLenum drawType;
	int vecSize;

	Viewport(std::vector<float>&, GLenum);

	unsigned int bindBuffer(std::vector<ShaderInfo>, bool);

	//unsigned int rebindBuffer(unsigned int, bool);
};

void readShader(std::string, std::string&);

unsigned int compileShader(unsigned int, const std::string&);

vecs::mat4 pointAtMatrix(vecs::vec3&, vecs::vec3&, vecs::vec3&);

unsigned int createShader(std::vector<ShaderInfo>);