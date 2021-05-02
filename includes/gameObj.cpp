#include "gameObj.h"

void applyStaticRotation(ObjectInfo& info)
{
	//apply a static rotation to a objects mesh
	vecs::mesh end;

	for (const auto& tri : info.objectMesh.tris)
	{
		vecs::vec3 t0 = vc::customVecMultiply(createWorldMatrix(info.staticObjectRotation, info.position, 1.0f), tri.p[0]);
		vecs::vec3 t1 = vc::customVecMultiply(createWorldMatrix(info.staticObjectRotation, info.position, 1.0f), tri.p[1]);
		vecs::vec3 t2 = vc::customVecMultiply(createWorldMatrix(info.staticObjectRotation, info.position, 1.0f), tri.p[2]);

		end.tris.push_back({ { t0, t1, t2 }, tri.color, tri.normal });
	}

	info.objectMesh = end;
}

void createMesh(ObjectInfo& info)
{
	//load object from file
	bool pass = vecs::loadFromObjectFile(info.objectModelDir, info.objectMesh, info.color);
	if (pass != true)
		throw "Provided file path is not valid or does not exist!";	

	applyStaticRotation(info);
}

void createObjectShaders(unsigned int drawType, ObjectInfo& info)
{
	/*std::vector<float> convertedObjectMesh;
	convertMeshToArray(info.objectMesh, convertedObjectMesh);

	Viewport objectView(convertedObjectMesh, drawType);

	info.program = objectView.bindBuffer(info.shaderDirs, info.depthTest, info.buffer);

	info.triangles = objectView.vecSize;*/
}

void addInt(std::string name, int num, ObjectInfo& obj)
{
	obj.objectInts.insert(std::pair<std::string, int>(name, num));
}

void addFloat(std::string name, float num, ObjectInfo& obj)
{
	obj.objectFloats.insert(std::pair<std::string, float>(name, num));
}

void addVec(std::string name, vecs::vec3 vec, ObjectInfo& obj)
{
	obj.objectVectors.insert(std::pair<std::string, vecs::vec3>(name, vec));
}

void addMat(std::string name, vecs::mat4 mat, ObjectInfo& obj)
{
	obj.objectMats.insert(std::pair<std::string, vecs::mat4>(name, mat));
}