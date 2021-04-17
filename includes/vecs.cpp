#include "vecs.h"
#include<iostream>

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

bool vecs::loadFromObjectFile(std::string path, vecs::mesh& object)
{
	std::ifstream f(path);
	if (!f.is_open())
		return false;

	// Local cache of verts
	std::vector<vecs::vec3> verts;
	std::vector<vecs::vec3> normals;

	while (!f.eof())
	{
		char line[128];
		f.getline(line, 128);

		std::strstream s;
		s << line;

		char junk;

		if (line[0] == 'v' && line[1] != 'n')
		{
			vecs::vec3 v;
			s >> junk >> v.x >> v.y >> v.z;
			verts.push_back(v);
		}

		if (line[0] == 'v' && line[1] == 'n')
		{
			vecs::vec3 n;
			s >> junk >> junk >> n.x >> n.y >> n.z;
			normals.push_back(n);
		}

		if (line[0] == 'f')
		{
			int f[3];
			int vn;
			s >> junk >> f[0] >> junk >> junk >> vn >> f[1] >> junk >> junk >> vn >> f[2] >> junk >> junk >> vn;
			object.tris.push_back({ { verts[f[0] - 1], verts[f[1] - 1], verts[f[2] - 1] }, 1.0f, 1.0f, 0.0f, normals[vn-1] });
		}
	}

	return true;
}