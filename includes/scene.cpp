#include "scene.h"

void Scene::setGameObject(ObjectInfo info)
{
	sceneObjects.insert(std::pair<std::string, ObjectInfo>(info.name, info));

	totalTris += info.triangles;
}

void Scene::setStepFunction(std::string objName, std::function<void(std::map<std::string, ObjectInfo>&, std::string)> func)
{
	std::map<std::string, ObjectInfo>::iterator it;

	it = sceneObjects.find(objName);
	if (it == sceneObjects.end())
		throw "The object you are tring to asign a function to doesn't exist";

	stepFunctions.insert(std::pair<std::string, std::function<void(std::map<std::string, ObjectInfo>&, std::string)>>(objName, func));
}

void Scene::setCreateFunction(std::string objName, std::function<void(std::map<std::string, ObjectInfo>&, std::string)> func)
{
	std::map<std::string, ObjectInfo>::iterator it;

	it = sceneObjects.find(objName);
	if(it == sceneObjects.end())
		throw "The object you are tring to asign a function to doesn't exist";

	createFunctions.insert(std::pair<std::string, std::function<void(std::map<std::string, ObjectInfo>&, std::string)>>(objName, func));
}

void Scene::callStepFunction(std::string objName)
{
	std::map<std::string, std::function<void(std::map<std::string, ObjectInfo>&, std::string)>>::const_iterator el;
	el = stepFunctions.find(objName);
	if (el == stepFunctions.end())
		throw "The object you are calling the step function for does not exist";

	el->second(sceneObjects, objName);
}

void Scene::callCreateFunction(std::string objName)
{
	std::map<std::string, std::function<void(std::map<std::string, ObjectInfo>&, std::string)>>::const_iterator el;
	el = createFunctions.find(objName);
	if (el == createFunctions.end())
		throw "The object you are calling the step function for does not exist";

	el->second(sceneObjects, objName);
}