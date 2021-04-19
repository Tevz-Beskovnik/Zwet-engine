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
#include "scene.h"

struct ObjectInfo
{
	std::string name;
	vecs::vec3 position;
	vecs::mesh boundingBox;
	vecs::mesh objectMesh;
	unsigned int program;
};

class GameObject {
	public:
		void createObj(unsigned int);

		void setShaderInfo(std::vector<ShaderInfo>);

		//TODO set function that will run on step (add function that will run on create) maybe
		void stepFunction(std::function<ObjectInfo (ObjectInfo, std::function<ObjectInfo (std::string, Scene)>, Scene)>);

		void setObjectName(std::string);

		void setObjectMesh(std::string);

		void setObjectPosition(vecs::vec3);

		void setDepthTest(bool);

		void setMesh(vecs::mesh);

		void setBoundingBox(vecs::mesh);
		 
		void setScene(Scene);

	private:
		Scene& objectParentScene;
		ObjectInfo info;
		std::vector<ShaderInfo> shaderDirs;
		std::string objectModelDir;
		bool depthTest;

		bool updateObjectInfo(void);

		void createMesh(void);

		void createObjectShaders(unsigned int);
};