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
	vecs::mat4 projMat = { 
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
	};
	vecs::vec3 lookDir = { 0.0f, 0.0f, 1.0f };
	vecs::vec3 lookDirSqued = { 1.0f, 0.0f, 0.0f };
	vecs::vec3 lookDirSquedUp = { 0.0f, 1.0f, 0.0f };
	vecs::vec3 up = { 0.0f, 1.0f, 0.0f };
	//movement controls
	/*TODO
		- let the programer have access to the entire camera PASS IT BY REFRENCE in the create and step function 
		  of the game objects so you have full access to it
	*/
	float forward = 0.0f;   
	float sideways = 0.0f;
	float vertical = 0.0f;
	float yaw = 0.0f;
	float roll = 0.0f;
	float pitch = 0.0f;
} Cam;

/*TODO
	-Make sure the projection mat is bound in the step function to a preset uniform,
	-Make sure the world mat is bound in the step function to a present uniform,
	-Make sure the transposed world mat is bound to a preset uniform,
	-POSSIBLY add option to precalculate all the object meshes with the world matrix
	 to increase the SPEED OF RENDER BRRRRRRR,
*/

class Scene
{
	public:
		int totalTris = 0;
		float sceneRotationX = 0.0f;
		float sceneRotationY = 0.0f;
		float sceneRotationZ = 0.0f;
		Camera sceneCamera;

		vecs::mat4 calculateViewMat();

		vecs::mat4 calculateWorldMat();

		void addCameraProjMat(float, float, float, float, float);

		void setGameObject(ObjectInfo);
	
		void setStepFunction(std::string, std::function<void(std::map<std::string, ObjectInfo>&, std::string)>);
	
		void setCreateFunction(std::string, std::function<void(std::map<std::string, ObjectInfo>&, std::string)>);
	
		void callStepFunction(std::string);
	
		void callCreateFunction(std::string);
	
	private:

		vecs::mat4 worldMat;
		vecs::mat4 transposedWorldMat;
		std::map<std::string, ObjectInfo> sceneObjects;
		std::map<std::string, std::function<void(std::map<std::string, ObjectInfo>&, std::string)>> stepFunctions;
		std::map<std::string, std::function<void(std::map<std::string, ObjectInfo>&, std::string)>> createFunctions;

};