#include "scene.h"

void Scene::setGameObject(ObjectInfo info)
{
	//put a new object in the scene
	ObjectInfo temp = info;

	createMesh(temp);

	createObjectShaders(temp.drawType, temp);

	sceneObjects.insert(std::pair<std::string, ObjectInfo>(info.name, temp));

	totalTris += temp.triangles;
}

void Scene::setStepFunction(std::string objName, std::function<void(std::map<std::string, ObjectInfo>&, std::string, Camera&)> func)
{
	//set the function that is suppost to run at step (every render cycle)
	std::map<std::string, ObjectInfo>::iterator it;

	it = sceneObjects.find(objName);
	if (it == sceneObjects.end())
		throw "The object you are tring to asign a function to doesn't exist";

	stepFunctions.insert(std::pair<std::string, std::function<void(std::map<std::string, ObjectInfo>&, std::string, Camera&)>>(objName, func));
}

void Scene::setCreateFunction(std::string objName, std::function<void(std::map<std::string, ObjectInfo>&, std::string, Camera&)> func)
{
	//set the create function (runs before the render cycle)
	std::map<std::string, ObjectInfo>::iterator it;

	it = sceneObjects.find(objName);
	if(it == sceneObjects.end())
		throw "The object you are tring to asign a function to doesn't exist";

	createFunctions.insert(std::pair<std::string, std::function<void(std::map<std::string, ObjectInfo>&, std::string, Camera&)>>(objName, func));
}

void Scene::callStepFunction(std::string objName)
{
	//call the before asigned step function
	std::map<std::string, std::function<void(std::map<std::string, ObjectInfo>&, std::string, Camera&)>>::const_iterator el;
	el = stepFunctions.find(objName);
	el->second(sceneObjects, objName, sceneCamera);

	//get uniform locations to bind the predefined uniforms
	int uWorld = glGetUniformLocation(sceneObjects[objName].program, "uWorld");
	int uWorldInvTran = glGetUniformLocation(sceneObjects[objName].program, "uWorldInvTran");
	int uViewMat = glGetUniformLocation(sceneObjects[objName].program, "uViewMat");
	int uCameraPos = glGetUniformLocation(sceneObjects[objName].program, "uCameraPos");

	glUniformMatrix4fv(uWorld, 1, GL_FALSE, &worldMat.r[0][0]);
	glUniformMatrix4fv(uWorldInvTran, 1, GL_FALSE, &transposedWorldMat.r[0][0]);
	glUniformMatrix4fv(uViewMat, 1, GL_FALSE, &viewMat.r[0][0]);
	glUniform3f(uCameraPos, sceneCamera.pos.x, sceneCamera.pos.y, sceneCamera.pos.z);
}

void Scene::callCreateFunction(std::string objName)
{
	//call the before asigned create function
	std::map<std::string, std::function<void(std::map<std::string, ObjectInfo>&, std::string, Camera&)>>::const_iterator el;
	el = createFunctions.find(objName);
	el->second(sceneObjects, objName, sceneCamera);
}

void Scene::addCameraProjMat(float width, float height, float fFar, float fNear, float fov)
{
	//add the projection matrix to the scene camera
	const float fovRad = 1 / tanf(fov * 0.5f / 180.0f * (float)PI);

	const float aspectRatio = height / width;

	sceneCamera.projMat = {
		aspectRatio * fovRad, 0.0f, 0.0f, 0.0f,
		0.0f, fovRad, 0.0f, 0.0f,
		0.0f, 0.0f, fFar / (fFar - fNear), 1.0f,
		0.0f, 0.0f, (-fFar * fNear) / (fFar - fNear), 0.0f
	};
}

void Scene::calculateViewMat(Camera& cam)
{
	//add the new look directions to the camera position
	cam.pos = cam.pos + (cam.lookDir * cam.forward) + (cam.lookDirSqued * cam.sideways) + (cam.lookDirSquedUp * cam.vertical);

	//targets for all 3 axis
	vecs::vec3 vTargetF = { 0.0f, 0.0f, 1.0f };

	//create camera rotation matrix for yaw
	vecs::mat4 mCameraRot = vc::rotY(cam.yaw);

	//add up the new look directions with the new camera rotation
	cam.lookDir = vc::customVecMultiply(mCameraRot, vTargetF);
	cam.lookDirSqued = vc::customVecMultiply(mCameraRot, { 1.0f, 0.0f, 0.0f });
	cam.lookDirSquedUp = vc::customVecMultiply(mCameraRot, { 0.0f, 1.0f, 0.0f });

	//asign new target
	vTargetF = cam.pos + cam.lookDir;

	viewMat =  createViewMatrix(cam.projMat, cam.pos, vTargetF, cam.up, cam.pitch, 0.0f, 0.0f);
}

void Scene::calculateWorldMat()
{
	//calculates the world and the inverted transposed world mat 
	worldMat = createWorldMatrix(dynamicSceneRotation, { 0.0f, 0.0f, 0.0f }, 1.0f);
	transposedWorldMat = vc::transposeMat(vc::quickInverse(worldMat));
}

void Scene::applyStaticSceneRotation()
{
	for (auto& kv : sceneObjects)
	{
		vecs::mesh endWorld;

		for (const auto& tri : kv.second.objectMesh.tris)
		{
			vecs::vec3 t0 = vc::customVecMultiply(createWorldMatrix(staticSceneRotation, kv.second.position, 1.0f), tri.p[0]);
			vecs::vec3 t1 = vc::customVecMultiply(createWorldMatrix(staticSceneRotation, kv.second.position, 1.0f), tri.p[1]);
			vecs::vec3 t2 = vc::customVecMultiply(createWorldMatrix(staticSceneRotation, kv.second.position, 1.0f), tri.p[2]);

			endWorld.tris.push_back({ { t0, t1, t2 }, tri.color, tri.normal });
		}

		kv.second.objectMesh = endWorld;
	}
}

void Scene::sceneStep()
{
	//things that need to be called at step but not multiple times
	calculateViewMat(sceneCamera);
	calculateWorldMat();
}

void Scene::sceneCreate()
{
	//things that run before the render cycle and don't need to be done repetativly
	calculateViewMat(sceneCamera);
	calculateWorldMat();
}