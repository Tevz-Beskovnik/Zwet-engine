#include "scene.h"

void Scene::addObject(ObjectInfo obj)
{
	objects.insert(std::pair<std::string, ObjectInfo>(obj.name, obj));
}

ObjectInfo Scene::getObject(std::string objName)
{
	std::map<std::string, ObjectInfo>::iterator it = objects.find(objName);
	if (it != objects.end())
		return it->second;
}

bool Scene::updateObject(ObjectInfo obj)
{
	std::map<std::string, ObjectInfo>::iterator it = objects.find(obj.name);
	if (it != objects.end())
	{
		it->second = obj;
		return true;
	}
	else
		return false;
}