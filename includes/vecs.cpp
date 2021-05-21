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

bool vecs::loadFromObjectFile(std::string path, vecs::mesh& object, vecs::rgb color)
{
	std::ifstream f(path);
	if (!f.is_open())
		return false;

	// Local cache of verts
	std::vector<vecs::vec3> verts;
	std::vector<vecs::vec3> normals;
	std::vector<vecs::vec2> UVs;

	while (!f.eof())
	{
		char line[128];
		f.getline(line, 128);

		std::strstream s;
		s << line;

		char junk;

		if (line[0] == 'v' && line[1] != 'n' && line[1] != 't')
		{
			vecs::vec3 v;
			s >> junk >> v.x >> v.y >> v.z;
			verts.push_back(v);
		}

		if (line[0] == 'v' && line[1] == 't')
		{
			float i, j;
			s >> junk >> junk >> i >> j;
			UVs.push_back({ (float)i, (float)j });
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
			int uv[3];
			if (UVs.empty() == false && normals.empty() == false)
			{
				s >> junk >> f[0] >> junk >> uv[0] >> junk >> vn >> f[1] >> junk >> uv[1] >> junk >> vn >> f[2] >> junk >> uv[2] >> junk >> vn;
				object.tris.push_back({ { verts[f[0] - 1], verts[f[1] - 1], verts[f[2] - 1] }, { UVs[uv[0] - 1], UVs[uv[1] - 1], UVs[uv[2] - 1] }, color, normals[vn - 1] });
			}
			else if(normals.empty() == false)
			{ 	
				s >> junk >> f[0] >> junk >> junk >> vn >> f[1] >> junk >> junk >> vn >> f[2] >> junk >> junk >> vn;
				object.tris.push_back({ { verts[f[0] - 1], verts[f[1] - 1], verts[f[2] - 1] }, { 0.0f }, color, normals[vn-1] });
			}
			else
			{
				s >> junk >> f[0] >> f[1] >> f[2];
				object.tris.push_back({ { verts[f[0] - 1], verts[f[1] - 1], verts[f[2] - 1] }, { 0.0f }, color, 1.0f, 0.0f, 0.0f });
			}
		}
	}

	return true;
}