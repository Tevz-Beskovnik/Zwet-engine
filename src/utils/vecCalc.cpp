#include <vecCalc.h>
#include<cmath>
#include<math.h>

namespace ZWET
{
float dotPru(vec3 vec1, vec3 vec2) 
{
	return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

float vecLen(vec3 vec) 
{
	return sqrtf(dotPru(vec, vec));
}

vec3 normalize(vec3 vec) 
{
	float l = vecLen(vec);
	bool lf = l != 0, lt = l == 0;
	return {((vec.x / l)*lf + vec.x*lt), ((vec.y / l) * lf + vec.y * lt), ((vec.z / l) * lf + vec.z * lt)};
}

vec3 crossPru(vec3 vec1, vec3 vec2) 
{
	return {
		(vec1.y * vec2.z - vec1.z * vec2.y),
		(vec1.z * vec2.x - vec1.x * vec2.z),
		(vec1.x * vec2.y - vec1.y * vec2.x)
	};
}

vec3 vecSub(vec3 vec1, vec3 vec2)
{
	return {
		vec1.x - vec2.x,
		vec1.y - vec2.y,
		vec1.z - vec2.z
	};
}

vec3 vecAdd(vec3 v1, vec3 v2) 
{
	return {
		v1.x + v2.x,
		v1.y + v2.y,
		v1.z + v2.z
	};
}

vec3 vecPru(vec3 v, float k) 
{
	return {
		v.x * k,
		v.y * k,
		v.z * k
	};
}

vec3 vecDiv(vec3 v, float k) 
{
	return {
		v.x / k,
		v.y / k,
		v.z / k
	};
}

mat4 rotX(float x)
{
	return {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, cos(x), -sin(x), 0.0f,
		0.0f, sin(x), cos(x), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
}

mat4 rotY(float x)
{
	return {
		cos(x), 0.0f, sin(x), 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		-sin(x), 0.0f, cos(x), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
}

mat4 rotZ(float x)
{
	return {
		cos(x), -sin(x), 0.0f, 0.0f, 
		sin(x), cos(x), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
}

mat4 translationMat(float x, float y, float z)
{
	return {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		x, y, z, 1.0f
	};
}

mat4 quickInverse(mat4 mat)
{
	mat4 ret;
	ret.r[0][0] = mat.r[0][0]; ret.r[0][1] = mat.r[1][0]; ret.r[0][2] = mat.r[2][0]; ret.r[0][3] = 0.0f;
	ret.r[1][0] = mat.r[0][1]; ret.r[1][1] = mat.r[1][1]; ret.r[1][2] = mat.r[2][1]; ret.r[1][3] = 0.0f;
	ret.r[2][0] = mat.r[0][2]; ret.r[2][1] = mat.r[1][2]; ret.r[2][2] = mat.r[2][2]; ret.r[2][3] = 0.0f;
	ret.r[3][0] = -(mat.r[3][0] * ret.r[0][0] + mat.r[3][1] * ret.r[1][0] + mat.r[3][2] * ret.r[2][0]);
	ret.r[3][1] = -(mat.r[3][0] * ret.r[0][1] + mat.r[3][1] * ret.r[1][1] + mat.r[3][2] * ret.r[2][1]);
	ret.r[3][2] = -(mat.r[3][0] * ret.r[0][2] + mat.r[3][1] * ret.r[1][2] + mat.r[3][2] * ret.r[2][2]);
	ret.r[3][3] = 1.0f;
	return ret;
}

vec3 customVecMultiply(mat4 mat, vec3 vec)
{
	// Give a simple variable name to each part of the mat, a column and row number
	float c0r0 = mat.r[0][0], c1r0 = mat.r[0][1], c2r0 = mat.r[0][2], c3r0 = mat.r[0][3];
	float c0r1 = mat.r[1][0], c1r1 = mat.r[1][1], c2r1 = mat.r[1][2], c3r1 = mat.r[1][3];
	float c0r2 = mat.r[2][0], c1r2 = mat.r[2][1], c2r2 = mat.r[2][2], c3r2 = mat.r[2][3];
	float c0r3 = mat.r[3][0], c1r3 = mat.r[3][1], c2r3 = mat.r[3][2], c3r3 = mat.r[3][3];

	// Now set some simple names for the vec
	float x = vec.x;
	float y = vec.y;
	float z = vec.z;

	// Multiply the vec against each part of the 1st column, then add together
	float resX = (x * c0r0) + (y * c0r1) + (z * c0r2) + (c0r3);

	// Multiply the vec against each part of the 2nd column, then add together
	float resY = (x * c1r0) + (y * c1r1) + (z * c1r2) + (c1r3);

	// Multiply the vec against each part of the 3rd column, then add together
	float resZ = (x * c2r0) + (y * c2r1) + (z * c2r2) + (c2r3);

	// Multiply the vec against each part of the 4th column, then add together
	float resW = (x * c3r0) + (y * c3r1) + (z * c3r2) + (c3r3);

	if (resW != 0) {
		resX /= resW; resY /= resW; resZ /= resW;
	}

	return{
		resX, resY, resZ
	};
}

mat4 matrixPointAt(vec3& pos, vec3& target, vec3& up)
{
	// Calculate new forward direction
	vec3 newForward = target - pos;
	newForward = normalize(newForward);

	// Calculate new Up direction
	vec3 a = newForward * dotPru(up, newForward);
	vec3 newUp = up - a;
	newUp = normalize(newUp);

	// New Right direction is easy, its just cross product
	vec3 newRight = crossPru(newUp, newForward);

	// Construct Dimensioning and Translation Matrix	
	mat4 matrix;
	matrix.r[0][0] = newRight.x;	matrix.r[0][1] = newRight.y;	matrix.r[0][2] = newRight.z;	matrix.r[0][3] = 0.0f;
	matrix.r[1][0] = newUp.x;		matrix.r[1][1] = newUp.y;		matrix.r[1][2] = newUp.z;		matrix.r[1][3] = 0.0f;
	matrix.r[2][0] = newForward.x;	matrix.r[2][1] = newForward.y;	matrix.r[2][2] = newForward.z;	matrix.r[2][3] = 0.0f;
	matrix.r[3][0] = pos.x;			matrix.r[3][1] = pos.y;			matrix.r[3][2] = pos.z;			matrix.r[3][3] = 1.0f;
	return matrix;

}

mat4 transposeMat(mat4 m)
{
	mat4 outMat;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			outMat.r[i][j] = m.r[j][i];

	return outMat;
}

mat4 createWorldMatrix(vec3 rot, vec3 translation, float time)
{
    mat4 mRotX, mRotY, mRotZ, mTranslation;
    mRotX = rotX(rot.x * time);
    mRotY = rotY(rot.y * time);
    mRotZ = rotZ(rot.z * time);
    mTranslation = translationMat(translation.x, translation.y, translation.z);

    return mRotX * mRotZ * mTranslation;
}

mat4 createViewMatrix(mat4 mProjMat, vec3& pos, vec3& target, vec3& up, float pitch, float yaw, float roll)
{
    mat4 mCameraRotX = rotX(pitch);
    mat4 mCameraRotY = rotY(yaw);
    mat4 mCameraRotZ = rotZ(roll);
    mat4 mView = quickInverse((mCameraRotX * mCameraRotZ * mCameraRotY) * pointAtMatrix(pos, target, up));
    return mView * mProjMat;
}

mat4 pointAtMatrix(vec3& pos, vec3& target, vec3& up)
{
    vec3 newForward = normalize(target - pos);
    vec3 a = newForward * dotPru(up, newForward);
    vec3 newUp = normalize(up - a);
    vec3 newRight = crossPru(newUp, newForward);

    mat4 matrix;
    matrix.r[0][0] = newRight.x;	matrix.r[0][1] = newRight.y;	matrix.r[0][2] = newRight.z;	matrix.r[0][3] = 0.0f;
    matrix.r[1][0] = newUp.x;		matrix.r[1][1] = newUp.y;		matrix.r[1][2] = newUp.z;		matrix.r[1][3] = 0.0f;
    matrix.r[2][0] = newForward.x;	matrix.r[2][1] = newForward.y;	matrix.r[2][2] = newForward.z;	matrix.r[2][3] = 0.0f;
    matrix.r[3][0] = pos.x;			matrix.r[3][1] = pos.y;			matrix.r[3][2] = pos.z;			matrix.r[3][3] = 1.0f;
    return matrix;
}
}