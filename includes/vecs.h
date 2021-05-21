#ifndef identityMatix
	#define identityMatix { { 1.0f, 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 0.0f, 1.0f } }
#endif //!identityMatix

#pragma once
#include<string>
#include<fstream>
#include<vector>
#include<cmath>
#include<strstream>
#include<math.h>
#include<algorithm>

namespace vecs
{
	struct mat4 {
		float r[4][4] = { 
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};

		inline mat4 operator*(vecs::mat4 mat)
		{
			vecs::mat4 matrix;
			for (int c = 0; c < 4; c++)
				for (int r = 0; r < 4; r++)
					matrix.r[r][c] = this->r[r][0] * mat.r[0][c] + this->r[r][1] * mat.r[1][c] + this->r[r][2] * mat.r[2][c] + this->r[r][3] * mat.r[3][c];
			return matrix;
		};

	};

	struct vec2 {
		float x, y;
	};

	struct vec3{
		float x, y, z;

		inline vec3 operator+(vec3 vec)
		{
			return {
				this->x + vec.x, this->y + vec.y, this->z + vec.z
			};
		};

		inline vec3 operator-(vec3 vec)
		{
			return {
				this->x - vec.x, this->y - vec.y, this->z - vec.z
			};
		};

		inline vec3 operator*(float k)
		{
			return {
				this->x * k, this->y * k, this->z * k
			};
		};

		inline vec3 operator/(float k)
		{
			return {
				this->x / k, this->y / k, this->z / k
			};
		};

		inline vec3 operator*(mat4 mat)
		{
			float c0r0 = mat.r[0][0], c0r1 = mat.r[0][1], c0r2 = mat.r[0][2], c0r3 = mat.r[0][3];
			float c1r0 = mat.r[1][0], c1r1 = mat.r[1][1], c1r2 = mat.r[1][2], c1r3 = mat.r[1][3];
			float c2r0 = mat.r[2][0], c2r1 = mat.r[2][1], c2r2 = mat.r[2][2], c2r3 = mat.r[2][3];
			float c3r0 = mat.r[3][0], c3r1 = mat.r[3][1], c3r2 = mat.r[3][2], c3r3 = mat.r[3][3];

			float resX = (this->x * c0r0) + (this->x * c1r0) + (this->x * c2r0) + (c3r0);
			float resY = (this->y * c0r1) + (this->y * c1r1) + (this->y * c2r1) + (c3r1);
			float resZ = (this->z * c0r2) + (this->z * c1r2) + (this->z * c2r2) + (c3r2);
			float resW = (this->x * c0r3) + (this->y * c1r3) + (this->z * c2r3) + (c3r3);

			if (resW != 0)
			{
				resX /= resW; resY /= resW; resZ /= resW;
			}

			return{
				resX, resY, resZ
			};
		};
	};

	struct rgb {
		float r, g, b;
	};

	struct triangle{
		vec3 p[3];
		vec2 texUv[3];
		rgb color;
		vec3 normal;
	};
	
	struct mesh {
		std::vector<triangle> tris;
	};

	void identityMat(mat4&);

	bool loadFromObjectFile(std::string, vecs::mesh&, vecs::rgb);
};