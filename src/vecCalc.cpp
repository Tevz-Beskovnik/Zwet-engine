#include "vecCalc.h"
#include "vecs.h"
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
	return {((vec.x / l)*lf + vec.x*lt), ((vec.y / l) * lf + vec.y * lt), ((vec.z / l) * lf + vec.z * lt)};
}

vecs::vec3 vc::crossPru(vecs::vec3 vec1, vecs::vec3 vec2) 
{
	return {
		(vec1.y * vec2.z - vec1.z * vec2.y),
		(vec1.z * vec2.x - vec1.x * vec2.z),
		(vec1.x * vec2.y - vec1.y * vec2.x)
	};
}

vecs::vec3 vc::vecSub(vecs::vec3 vec1, vecs::vec3 vec2)
{
	return {
		vec1.x - vec2.x,
		vec1.y - vec2.y,
		vec1.z - vec2.z
	};
}

vecs::vec3 vc::vecAdd(vecs::vec3 v1, vecs::vec3 v2) 
{
	return {
		v1.x + v2.x,
		v1.y + v2.y,
		v1.z + v2.z
	};
}

vecs::vec3 vc::vecPru(vecs::vec3 v, float k) 
{
	return {
		v.x * k,
		v.y * k,
		v.z * k
	};
}

vecs::vec3 vc::vecDiv(vecs::vec3 v, float k) 
{
	return {
		v.x / k,
		v.y / k,
		v.z / k
	};
}

vecs::mat4 vc::rotX(float x)
{
	return {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, cos(x), -sin(x), 0.0f,
		0.0f, sin(x), cos(x), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
}

vecs::mat4 vc::rotY(float x)
{
	return {
		cos(x), 0.0f, sin(x), 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		-sin(x), 0.0f, cos(x), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
}

vecs::mat4 vc::rotZ(float x)
{
	return {
		cos(x), -sin(x), 0.0f, 0.0f, 
		sin(x), cos(x), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
}

vecs::mat4 vc::translationMat(float x, float y, float z)
{
	return {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		x, y, z, 1.0f
	};
}

vecs::mat4 vc::quickInverse(vecs::mat4 mat)
{
	vecs::mat4 ret;
	ret.r[0][0] = mat.r[0][0]; ret.r[0][1] = mat.r[1][0]; ret.r[0][2] = mat.r[2][0]; ret.r[0][3] = 0.0f;
	ret.r[1][0] = mat.r[0][1]; ret.r[1][1] = mat.r[1][1]; ret.r[1][2] = mat.r[2][1]; ret.r[1][3] = 0.0f;
	ret.r[2][0] = mat.r[0][2]; ret.r[2][1] = mat.r[1][2]; ret.r[2][2] = mat.r[2][2]; ret.r[2][3] = 0.0f;
	ret.r[3][0] = -(mat.r[3][0] * ret.r[0][0] + mat.r[3][1] * ret.r[1][0] + mat.r[3][2] * ret.r[2][0]);
	ret.r[3][1] = -(mat.r[3][0] * ret.r[0][1] + mat.r[3][1] * ret.r[1][1] + mat.r[3][2] * ret.r[2][1]);
	ret.r[3][2] = -(mat.r[3][0] * ret.r[0][2] + mat.r[3][1] * ret.r[1][2] + mat.r[3][2] * ret.r[2][2]);
	ret.r[3][3] = 1.0f;
	return ret;
}

vecs::vec3 vc::customVecMultiply(vecs::mat4 mat, vecs::vec3 vec)
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

vecs::mat4 vc::matrixPointAt(vecs::vec3& pos, vecs::vec3& target, vecs::vec3& up)
{
	// Calculate new forward direction
	vecs::vec3 newForward = target - pos;
	newForward = vc::normalize(newForward);

	// Calculate new Up direction
	vecs::vec3 a = newForward * vc::dotPru(up, newForward);
	vecs::vec3 newUp = up - a;
	newUp = vc::normalize(newUp);

	// New Right direction is easy, its just cross product
	vecs::vec3 newRight = vc::crossPru(newUp, newForward);

	// Construct Dimensioning and Translation Matrix	
	vecs::mat4 matrix;
	matrix.r[0][0] = newRight.x;	matrix.r[0][1] = newRight.y;	matrix.r[0][2] = newRight.z;	matrix.r[0][3] = 0.0f;
	matrix.r[1][0] = newUp.x;		matrix.r[1][1] = newUp.y;		matrix.r[1][2] = newUp.z;		matrix.r[1][3] = 0.0f;
	matrix.r[2][0] = newForward.x;	matrix.r[2][1] = newForward.y;	matrix.r[2][2] = newForward.z;	matrix.r[2][3] = 0.0f;
	matrix.r[3][0] = pos.x;			matrix.r[3][1] = pos.y;			matrix.r[3][2] = pos.z;			matrix.r[3][3] = 1.0f;
	return matrix;

}

vecs::mat4 vc::transposeMat(vecs::mat4 m)
{
	vecs::mat4 outMat;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			outMat.r[i][j] = m.r[j][i];

	return outMat;
}

vecs::mat4 vc::createWorldMatrix(vecs::vec3 rot, vecs::vec3 translation, float time)
{
    vecs::mat4 mRotX, mRotY, mRotZ, mTranslation;
    mRotX = vc::rotX(rot.x * time);
    mRotY = vc::rotY(rot.y * time);
    mRotZ = vc::rotZ(rot.z * time);
    mTranslation = vc::translationMat(translation.x, translation.y, translation.z);

    return mRotX * mRotZ * mTranslation;
}

vecs::mat4 vc::createViewMatrix(vecs::mat4 mProjMat, vecs::vec3& pos, vecs::vec3& target, vecs::vec3& up, float pitch, float yaw, float roll)
{
    vecs::mat4 mCameraRotX = vc::rotX(pitch);
    vecs::mat4 mCameraRotY = vc::rotY(yaw);
    vecs::mat4 mCameraRotZ = vc::rotZ(roll);
    vecs::mat4 mView = vc::quickInverse((mCameraRotX * mCameraRotZ * mCameraRotY) * vc::pointAtMatrix(pos, target, up));
    return mView * mProjMat;
}

vecs::mat4 vc::pointAtMatrix(vecs::vec3& pos, vecs::vec3& target, vecs::vec3& up)
{
    vecs::vec3 newForward = vc::normalize(target - pos);
    vecs::vec3 a = newForward * vc::dotPru(up, newForward);
    vecs::vec3 newUp = vc::normalize(up - a);
    vecs::vec3 newRight = vc::crossPru(newUp, newForward);

    vecs::mat4 matrix;
    matrix.r[0][0] = newRight.x;	matrix.r[0][1] = newRight.y;	matrix.r[0][2] = newRight.z;	matrix.r[0][3] = 0.0f;
    matrix.r[1][0] = newUp.x;		matrix.r[1][1] = newUp.y;		matrix.r[1][2] = newUp.z;		matrix.r[1][3] = 0.0f;
    matrix.r[2][0] = newForward.x;	matrix.r[2][1] = newForward.y;	matrix.r[2][2] = newForward.z;	matrix.r[2][3] = 0.0f;
    matrix.r[3][0] = pos.x;			matrix.r[3][1] = pos.y;			matrix.r[3][2] = pos.z;			matrix.r[3][3] = 1.0f;
    return matrix;
}