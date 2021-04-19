#include "gameObj.h"

void GameObject::createObj(unsigned int drawType)
{
	if (objectModelDir != "" && info.objectMesh.tris.empty() != false)
		createMesh();
	if (info.objectMesh.tris.empty() != false)
		createObjectShaders(drawType);
}

void GameObject::setMesh(vecs::mesh m)
{
	info.objectMesh = m;
}

void GameObject::createMesh(void)
{
	//load object from file
	bool pass = vecs::loadFromObjectFile(objectModelDir, info.objectMesh);
	if (pass != true)
		throw "Provided file path is not valid or does not exist!";
}

void GameObject::createObjectShaders(unsigned int drawType)
{
	std::vector<float> convertedObjectMesh;
	convertMeshToArray(info.objectMesh, convertedObjectMesh);

	Viewport objectView(convertedObjectMesh, drawType);

	info.program = objectView.bindBuffer(shaderDirs, depthTest);
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
	info.name = name;
}

void GameObject::setObjectPosition(vecs::vec3 pos)
{
	info.position = pos;
}

void GameObject::setDepthTest(bool dpthTest)
{
	depthTest = dpthTest;
}

void GameObject::setBoundingBox(vecs::mesh bBox)
{
	info.boundingBox = bBox;
}

ObjectInfo obGet(std::string objName, Scene sc)
{
	return sc.getObject(objName);
}

void GameObject::stepFunction(std::function<ObjectInfo (ObjectInfo, std::function<ObjectInfo(std::string, Scene)>, Scene)> f)
{
	ObjectInfo updatedInfo = f(info, obGet, objectParentScene);
	bool objUpdate = updateObjectInfo();
	if (objUpdate != true)
		throw "Something went wrong in the scene system, object isn't registered or data got changed.";
}

void GameObject::setScene(Scene scene)
{
	objectParentScene = scene;
}

bool GameObject::updateObjectInfo(void)
{
	return objectParentScene.updateObject(info);
}