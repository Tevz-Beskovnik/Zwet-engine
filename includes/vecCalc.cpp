#include "vecCalc.h"
#include<cmath>
#include<math.h>

float vc::dotPru(vecs::vec3 vec1, vecs::vec3 vec2) 
{
	return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

float vc::vecLen(vecs::vec3 vec) 
{
	return sqrtf(vc::dotPru(vec, vec));
}

vecs::vec3 vc::normalize(vecs::vec3 vec) 
{
	float l = vc::vecLen(vec);
	bool lf = l != 0, lt = l == 0;
	return vecs::vec3{((vec.x / l)*lf + vec.x*lt), ((vec.y / l) * lf + vec.y * lt), ((vec.z / l) * lf + vec.z * lt)};
}

vecs::vec3 vc::crossPru(vecs::vec3 vec1, vecs::vec3 vec2) 
{
	return vecs::vec3
	{
		vec1.y * vec2.z - vec1.z * vec2.y,
		vec1.z * vec2.x - vec1.x * vec2.z,
		vec1.x * vec2.y - vec1.y * vec2.x
	};
}

vecs::vec3 vc::vecSub(vecs::vec3 vec1, vecs::vec3 vec2)
{
	return vecs::vec3{
		vec1.x - vec2.x,
		vec1.y - vec2.y,
		vec1.z - vec2.z
	};
}

vecs::mat4 vc::rotX(float x)
{
	return {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, cosf(x), -sinf(x), 0.0f,
		0.0f, sinf(x), cosf(x), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
}

vecs::mat4 vc::rotY(float x)
{
	return {
		cosf(x), 0.0f, sinf(x), 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		-sinf(x), 0.0f, cosf(x), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
}

vecs::mat4 vc::rotZ(float x)
{
	return {
		cosf(x), -sinf(x), 0.0f, 0.0f, 
		sinf(x), cosf(x), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
}