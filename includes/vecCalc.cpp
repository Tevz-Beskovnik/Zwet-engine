#include "vecCalc.h"

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

vecs::mat4 vc::multiplyMat(vecs::mat4 mat1, vecs::mat4 mat2)
{
	vecs::mat4 output;

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			output.r[j][i] = mat1.r[j][0] * mat2.r[0][i] + mat1.r[j][1] * mat2.r[1][i] + mat1.r[j][2] * mat2.r[2][i] + mat1.r[j][3] * mat2.r[3][i];

	return output;
}