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

		vecs::vec3 U = t1 - t0;
		vecs::vec3 V = t2 - t0;

		vecs::vec3 newNormal = {
			(U.y * V.z) - (V.y * U.z),
			(U.z * V.x) - (V.z * U.x),
			(U.x * V.y) - (V.x * U.y)
		};

		end.tris.push_back({ { t0, t1, t2 }, { tri.texUv[0], tri.texUv[1], tri.texUv[2] }, tri.color, newNormal });
	}

	info.objectMesh = end;
}

void createMesh(ObjectInfo& info)
{
	//load object from file
	bool pass = vecs::loadFromObjectFile(info.objectModelDir, info.objectMesh, info.color);
	if (pass == true){
		applyStaticRotation(info);
	}
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