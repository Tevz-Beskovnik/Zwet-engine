#pragma once
#include<vector>

namespace vecs
{
	struct vec3 {
		float x, y, z;
	};

	struct mat4 {
		float r[4][4];

		inline mat4 operator*(vecs::mat4 mat)
		{
			vecs::mat4 output;

			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					output.r[j][i] = this->r[j][0] * mat.r[0][i] + this->r[j][1] * mat.r[1][i] + this->r[j][2] * mat.r[2][i] + this->r[j][3] * mat.r[3][i];

			return output;
		}
	};

	struct rgb {
		float r, g, b;
	};

	struct triangle {
		vec3 p[3];
		rgb color;
	};

	struct mesh {
		std::vector<triangle> tris;
	};

	void identityMat(mat4&);
};