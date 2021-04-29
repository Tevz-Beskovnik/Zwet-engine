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

void Scene::addCameraProjMat(float width, float height, float fFar, float fNear, float fov)
{
	const float fovRad = 1 / tanf(fov * 0.5f / 180.0f * (float)PI);

	const float aspectRatio = height / width;

	sceneCamera.projMat = {
		aspectRatio * fovRad, 0.0f, 0.0f, 0.0f,
		0.0f, fovRad, 0.0f, 0.0f,
		0.0f, 0.0f, fFar / (fFar - fNear), 1.0f,
		0.0f, 0.0f, (-fFar * fNear) / (fFar - fNear), 0.0f
	};
}

vecs::mat4 Scene::calculateViewMat()
{
	//check if the camera is moving
	vecs::vec3 vForward = sceneCamera.lookDir * sceneCamera.forward;
	vecs::vec3 vSideways = sceneCamera.lookDirSqued * sceneCamera.sideways;
	vecs::vec3 vVertical = sceneCamera.lookDirSquedUp * sceneCamera.vertical;

	//add the new look directions to the camera position
	sceneCamera.pos = sceneCamera.pos + vForward;
	sceneCamera.pos = sceneCamera.pos + vSideways;
	sceneCamera.pos = sceneCamera.pos + vVertical;

	//targets for all 3 axis
	vecs::vec3 vTargetF = { 0.0f, 0.0f, 1.0f };
	vecs::vec3 vTargetS = { 1.0f, 0.0f, 0.0f };
	vecs::vec3 vTargetV = { 0.0f, 1.0f, 0.0f };

	//create camera rotation matrix for yaw
	vecs::mat4 mCameraRot = vc::rotY(sceneCamera.yaw);

	//add up the new look directions with the new camera rotation
	sceneCamera.lookDir = vc::customVecMultiply(mCameraRot, vTargetF);
	sceneCamera.lookDirSqued = vc::customVecMultiply(mCameraRot, vTargetS);
	sceneCamera.lookDirSquedUp = vc::customVecMultiply(mCameraRot, vTargetV);

	//asign new target
	vTargetF = sceneCamera.pos + sceneCamera.lookDir;

	return createViewMatrix(sceneCamera.projMat, sceneCamera.pos, vTargetF, sceneCamera.up, sceneCamera.pitch, sceneCamera.yaw, sceneCamera.roll);
}

vecs::mat4 Scene::calculateWorldMat()
{
	worldMat = createWorldMatrix(sceneRotationX, sceneRotationY, sceneRotationZ);
	transposedWorldMat = vc::transposeMat(vc::quickInverse(worldMat));
}