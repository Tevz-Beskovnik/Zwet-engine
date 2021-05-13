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
		vecs::vec3 staticSceneRotation = { 0.0f };
		vecs::vec3 dynamicSceneRotation = { 0.0f };
		Camera sceneCamera;

		void sceneStep();

		void sceneCreate();

		void applyStaticSceneRotation();

		void addCameraProjMat(float width, float height, float fFar, float fNear, float fov);

		void addGameObject(ObjectInfo);
	
		void setStepFunction(std::string, std::function<void(std::map<std::string, ObjectInfo>&, std::string, Camera&)>);
	
		void setCreateFunction(std::string, std::function<void(std::map<std::string, ObjectInfo>&, std::string, Camera&)>);
		
		/*TODO
			-add texturing to objects, read UV map from obj file,
			-add abilit to read color info of objects (gotta look into that),
			-possiblity to create multiple instances of the same object that have the same create and step functions,
				-add objectID system za managenje tega,
				-možnost kreiranja drugih objektov iz step / create funkcij drugih objecktov,
				-when adding this make sure to make a proper *create* function that runs on object
				 creation and not when the game starts becouse you can add them at run time duh,
				-add a event that runs before the game starts (becouse the create function now
				 does something else now (mostly for optimisation (or disern when the create is at begin of game or at runtime :D))
			-parent child system (to je probably malo komplicirano),
			-etc......
		*/
		void callStepFunction(std::string);
	
		void callCreateFunction(std::string);

		std::vector<std::string> objectNames();
	
	private:
		vecs::mat4 worldMat;
		vecs::mat4 transposedWorldMat;
		vecs::mat4 viewMat;
		std::map<std::string, ObjectInfo> sceneObjects;
		std::map<std::string, std::function<void(std::map<std::string, ObjectInfo>&, std::string, Camera&)>> stepFunctions;
		std::map<std::string, std::function<void(std::map<std::string, ObjectInfo>&, std::string, Camera&)>> createFunctions;

		void calculateWorldMat();

		void calculateViewMat(Camera& cam);
};