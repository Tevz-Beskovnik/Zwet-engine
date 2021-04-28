#pragma once

#ifndef PI
	#define PI 3.14159265358979323846
#endif // PI

#include<math.h>
#include "gameObj.h"

typedef struct Camera
{
	//things to do with camera position and projections 
	vecs::vec3 pos = { 0.0f, 0.0f, 0.0f };
	vecs::mat4 projMat;
	vecs::vec3 lookDir = { 0.0f, 0.0f, 1.0f };
	vecs::vec3 lookDirSqued = { 1.0f, 0.0f, 0.0f };
	vecs::vec3 lookDirSquedUp = { 0.0f, 1.0f, 0.0f };
	vecs::vec3 up = { 0.0f, 1.0f, 0.0f };
	//movement controls
	/*TODO 
		- add support that you can adjust movement for all the x, y, z axises, 
		- add support that you can look around all around you (up, down, left, right, rotate left, rotate right),
		- let the programer have access to the entire camera PASS IT BY REFRENCE in the create and step function 
		  of the game objects so you have full access to it
		- take the calculations in main.cpp for the view matrix add support for the missing axis / rotation in the scene calculateViewMat() function
	*/
	float forward = 0.0f;   
	float sideways = 0.0f;
	float vertical = 0.0f;
	float yaw = 0.0f;
	float roll = 0.0f;
	float pitch = 0.0f;
} Cam;

class Scene
{
	public:
		int totalTris = 0;
		Camera sceneCamera;

		void calculateViewMat();

		void addProjMat(float, float, float, float, float);

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