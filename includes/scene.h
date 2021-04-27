#pragma once

#include "gameObj.h"



class Scene
{
	public:
		int totalTris = 0;

		void setGameObject(ObjectInfo);
	
		void setStepFunction(std::string, std::function<void(std::map<std::string, ObjectInfo>&, std::string)>);
	
		void setCreateFunction(std::string, std::function<void(std::map<std::string, ObjectInfo>&, std::string)>);
	
		void callStepFunction(std::string);
	
		void callCreateFunction(std::string);
	
	private:

		std::map<std::string, ObjectInfo> sceneObjects;
		std::map<std::string, std::function<void(std::map<std::string, ObjectInfo>&, std::string)>> stepFunctions;
		std::map<std::string, std::function<void(std::map<std::string, ObjectInfo>&, std::string)>> createFunctions;

};