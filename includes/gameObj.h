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
	//name of object for refrencing in other objects
	std::string name;

	//position and rotation of object
	vecs::vec3 position = { 0.0f };
	vecs::vec3 staticObjectRotation = { 0.0f };
	vecs::vec3 dynamicObjectRotation = { 0.0f };

	//color
	vecs::rgb color = { 1.0f, 1.0f, 1.0f };

	//things to do with the mesh loading of mesh collision, shading and rendering
	vecs::mesh boundingBox;
	vecs::mesh objectMesh;
	std::vector<float> convertedMesh;
	unsigned int program;
	unsigned int buffer;
	unsigned int drawType;
	std::vector<ShaderInfo> shaderDirs;
	std::string objectModelDir;
	bool depthTest = true;
	
	//local variables that can be set in the create function
	std::map<std::string, int> objectInts;
	std::map<std::string, float> objectFloats;
	std::map<std::string, vecs::vec3> objectVectors;
	std::map<std::string, vecs::mat4> objectMats;

	//number of triangles in the mesh
	int triangles;
} Obj;

void applyStaticRotation(ObjectInfo&);

void createMesh(ObjectInfo&);

void createObjectShaders(unsigned int, ObjectInfo&);

void addInt(std::string, int, ObjectInfo&);

void addFloat(std::string, float, ObjectInfo&);

void addVec(std::string, vecs::vec3, ObjectInfo&);

void addMat(std::string, vecs::mat4, ObjectInfo&);