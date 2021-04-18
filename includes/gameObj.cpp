#include "gameObj.h"

void GameObject::createObj(unsigned int drawType)
{
	if (objectModelDir != "" && objectMesh.tris.empty() != false)
		createMesh();
	if (objectMesh.tris.empty() != false)
		createObjectShaders(drawType);
}

void GameObject::setMesh(vecs::mesh m)
{
	objectMesh = m;
}

void GameObject::createMesh(void)
{
	//load object from file
	bool pass = vecs::loadFromObjectFile(objectModelDir, objectMesh);
	if (pass != true)
		throw "Provided file path is not valid or does not exist!";
}

void GameObject::createObjectShaders(unsigned int drawType)
{
	std::vector<float> convertedObjectMesh;
	convertMeshToArray(objectMesh, convertedObjectMesh);

	Viewport objectView(convertedObjectMesh, drawType);

	objectProgram = objectView.bindBuffer(shaderDirs, depthTest);
}

void GameObject::setShaderInfo(std::vector<ShaderInfo> shadDirs)
{
	shaderDirs = shadDirs;
}

void GameObject::setObjectMesh(std::string objDir)
{
	objectModelDir = objDir;
}

void GameObject::setObjectName(std::string name)
{
	objectName = name;
}

void GameObject::setObjectPosition(vecs::vec3 pos)
{
	x = pos.x;
	y = pos.y;
	z = pos.z;
}

void GameObject::setDepthTest(bool dpthTest)
{
	depthTest = dpthTest;
}

void GameObject::setBoundingBox(vecs::mesh bBox)
{
	boundingBox = bBox;
}

ObjectInfo GameObject::getObject(std::string objName, Scene s)
{
	return s.getObject(objName);
}