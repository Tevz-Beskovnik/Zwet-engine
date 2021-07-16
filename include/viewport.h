#pragma once

#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include "vecs.h"

void convertMeshToArray(const vecs::mesh, std::vector<float>&);

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

	void genBuffer(unsigned int*);

	void bindBufferData(unsigned int&);

	void bindAttributes(unsigned int&, unsigned int&);
};

void readShader(std::string, std::string&);

unsigned int compileShader(unsigned int, const std::string&);

vecs::mat4 pointAtMatrix(vecs::vec3&, vecs::vec3&, vecs::vec3&);

unsigned int createShader(std::vector<ShaderInfo>);