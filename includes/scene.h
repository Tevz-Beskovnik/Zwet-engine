#pragma once
#include<iterator>
#include "gameObj.h";

class Scene
{
	public:
		void addObject(ObjectInfo);
	
		ObjectInfo getObject(std::string);
	
		bool updateObject(ObjectInfo);
	
	private:
		std::map<std::string, ObjectInfo> objects;
};