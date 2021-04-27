#pragma once

#include<string>
#include<iostream>
#include<vector>
#include<functional>
#include "kbInput.h"
#include "vecCalc.h"
#include "vecs.h"
#include "vecCalc.h"
#include "collision.h"
#include "viewport.h"

//all posible object need for the object (no this probably isn't all the info needed)
typedef struct ObjectInfo
{
	std::string name;
	vecs::vec3 position;
	vecs::mesh boundingBox;
	vecs::mesh objectMesh;
	unsigned int program;
	std::vector<ShaderInfo> shaderDirs;
	std::string objectModelDir;
	bool depthTest;
	std::map<std::string, int> objectInts;
	std::map<std::string, float> objectFloats;
	std::map<std::string, vecs::vec3> objectVectors;
	std::map<std::string, vecs::mat4> objectMats;
	int triangles;
} Obj;

void createMesh(ObjectInfo&);

void createObjectShaders(unsigned int, ObjectInfo&);

void addInt(std::string, int, ObjectInfo&);

void addFloat(std::string, float, ObjectInfo&);

void addVec(std::string, vecs::vec3, ObjectInfo&);

void addMat(std::string, vecs::mat4, ObjectInfo&);