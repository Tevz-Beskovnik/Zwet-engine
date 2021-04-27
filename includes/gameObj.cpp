#include "gameObj.h"

void createMesh(ObjectInfo& info)
{
	//load object from file
	bool pass = vecs::loadFromObjectFile(info.objectModelDir, info.objectMesh);
	if (pass != true)
		throw "Provided file path is not valid or does not exist!";
}

void createObjectShaders(unsigned int drawType, ObjectInfo& info)
{
	std::vector<float> convertedObjectMesh;
	convertMeshToArray(info.objectMesh, convertedObjectMesh);

	Viewport objectView(convertedObjectMesh, drawType);

	info.program = objectView.bindBuffer(info.shaderDirs, info.depthTest);

	info.triangles = objectView.vecSize;
}

void addInt(std::string name, int num, ObjectInfo& obj)
{
	obj.objectInts.insert(std::pair<std::string, int>(name, num));
}

void addFloat(std::string name, float num, ObjectInfo& obj)
{
	obj.objectFloats.insert(std::pair<std::string, float>(name, num));
}

void addVec(std::string name, vecs::vec3 vec, ObjectInfo& obj)
{
	obj.objectVectors.insert(std::pair<std::string, vecs::vec3>(name, vec));
}

void addMat(std::string name, vecs::mat4 mat, ObjectInfo& obj)
{
	obj.objectMats.insert(std::pair<std::string, vecs::mat4>(name, mat));
}