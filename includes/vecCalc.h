#pragma once
#include<iostream>
#include<vector>
#include<math.h>
#include<cmath>
#include "vecs.h"

namespace vc
{
	float vecLen(vecs::vec3);

	float dotPru(vecs::vec3, vecs::vec3);

	vecs::vec3 normalize(vecs::vec3);

	vecs::vec3 crossPru(vecs::vec3, vecs::vec3);

	vecs::vec3 vecSub(vecs::vec3, vecs::vec3);

	vecs::mat4 rotX(float);

	vecs::mat4 rotY(float);
	
	vecs::mat4 rotZ(float);
};