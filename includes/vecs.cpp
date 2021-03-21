#include "vecs.h"

void vecs::identityMat(vecs::mat4& mat)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			mat.r[i][j] = 0;
	
	mat.r[0][0] = 1.0f;
	mat.r[1][1] = 1.0f;
	mat.r[2][2] = 1.0f;
	mat.r[3][3] = 1.0f;
}