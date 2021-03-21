#pragma once
#include<vector>

namespace vecs
{
	struct vec3 {
		float x, y, z;
	};

	struct mat4 {
		float r[4][4];
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