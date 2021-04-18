#pragma once

#include<string>
#include<iostream>
#include<vector>
#include "kbInput.h"
#include "vecCalc.h"
#include "vecs.h"
#include "vecCalc.h"
#include "collision.h"
#include "viewport.h"
#include "scene.h"

struct ObjectInfo
{
	std::string name;
	vecs::vec3 position;
	vecs::mesh boundingBox;
};

class GameObject {
	public:
		std::string objectName;
		float x;
		float y;
		float z;

		void createObj(unsigned int);

		void setShaderInfo(std::vector<ShaderInfo>);

		//TODO set function that will run on step (add function that will run on create) maybe
		void setFunction();

		void setObjectName(std::string);

		void setObjectMesh(std::string);

		void setObjectPosition(vecs::vec3);

		void setDepthTest(bool);

		void setMesh(vecs::mesh);

		void setBoundingBox(vecs::mesh);

		ObjectInfo getObject(std::string, Scene);

	private:
		vecs::mesh objectMesh;
		vecs::mesh boundingBox;
		unsigned int objectProgram;
		std::vector<ShaderInfo> shaderDirs;
		std::string objectModelDir;
		bool depthTest;

		void createMesh(void);

		void createObjectShaders(unsigned int);
};