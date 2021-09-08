#include <mesh.h>

namespace ZWET
{
    std::vector<float> convertMesh(mesh inputMesh)
    {
		std::vector<float> oMesh;

		for (const triangle& tri : inputMesh.tris)
        //fist vec3
    	{
    	    oMesh.push_back(tri.p[0].x);
    	    oMesh.push_back(tri.p[0].y);
    	    oMesh.push_back(tri.p[0].z);
    	    //colors for the triangle
    	    oMesh.push_back(tri.color.r);
    	    oMesh.push_back(tri.color.g);
    	    oMesh.push_back(tri.color.b);
    	    //add the normal
    	    oMesh.push_back(tri.normal.x);
    	    oMesh.push_back(tri.normal.y);
    	    oMesh.push_back(tri.normal.z);
    	    //uvs
    	    oMesh.push_back(tri.texUV[0].x);
    	    oMesh.push_back(tri.texUV[0].y);
    	    //second vec3
        	oMesh.push_back(tri.p[1].x);
	        oMesh.push_back(tri.p[1].y);
	        oMesh.push_back(tri.p[1].z);
	        //colors for the triangle
	        oMesh.push_back(tri.color.r);
	        oMesh.push_back(tri.color.g);
	        oMesh.push_back(tri.color.b);
	        //add the normal
	        oMesh.push_back(tri.normal.x);
	        oMesh.push_back(tri.normal.y);
	        oMesh.push_back(tri.normal.z);
	        //uvs
	        oMesh.push_back(tri.texUV[1].x);
	        oMesh.push_back(tri.texUV[1].y);
	        //third vec3
	        oMesh.push_back(tri.p[2].x);

	        oMesh.push_back(tri.p[2].y);
	        oMesh.push_back(tri.p[2].z);
	        //colors for the triangle
	        oMesh.push_back(tri.color.r);
	        oMesh.push_back(tri.color.g);
	        oMesh.push_back(tri.color.b);
	        //add the normal
	        oMesh.push_back(tri.normal.x);
	        oMesh.push_back(tri.normal.y);
	        oMesh.push_back(tri.normal.z);
	        //uvs
	        oMesh.push_back(tri.texUV[2].x);
	        oMesh.push_back(tri.texUV[2].y);
	    }
	}

    bool readMesh(mesh &inputMesh, std::string modelLocation, rgb color)
    {
            std::ifstream f(modelLocation);
	    if (!f.is_open())
	    	return false;

	    // Local cache of verts
	    std::vector<vec3> verts;
	    std::vector<vec3> normals;
	    std::vector<vec2> UVs;

	    while (!f.eof())
	    {
	    	char line[128];
	    	f.getline(line, 128);

	    	std::stringstream s;
	    	s << line;

	    	char junk;

	    	if (line[0] == 'v' && line[1] != 'n' && line[1] != 't')
	    	{
	    		vec3 v;
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
	    		vec3 n;
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
	    			inputMesh.tris.push_back({ { verts[f[0] - 1], verts[f[1] - 1], verts[f[2] - 1] }, { UVs[uv[0] - 1], UVs[uv[1] - 1], UVs[uv[2] - 1] }, color, normals[vn - 1] });
	    		}
	    		else if(normals.empty() == false)
	    		{ 	
	    			s >> junk >> f[0] >> junk >> junk >> vn >> f[1] >> junk >> junk >> vn >> f[2] >> junk >> junk >> vn;
	    			inputMesh.tris.push_back({ { verts[f[0] - 1], verts[f[1] - 1], verts[f[2] - 1] }, { 0.0f }, color, normals[vn-1] });
	    		}
	    		else
	    		{
	    			s >> junk >> f[0] >> f[1] >> f[2];
	    			inputMesh.tris.push_back({ { verts[f[0] - 1], verts[f[1] - 1], verts[f[2] - 1] }, { 0.0f }, color, 1.0f, 0.0f, 0.0f });
	    		}
	    	}
	    }

	    return true;
    }

    void applyStaticRotation(mesh& outMesh, vec3 rotationVector, vec3 position)
    {
		mesh endWorld;

		for (const auto& tri : outMesh.tris)
		{
			vec3 t0 = customVecMultiply(createWorldMatrix(rotationVector, position, 1.0f), tri.p[0]);
			vec3 t1 = customVecMultiply(createWorldMatrix(rotationVector, position, 1.0f), tri.p[1]);
			vec3 t2 = customVecMultiply(createWorldMatrix(rotationVector, position, 1.0f), tri.p[2]);

			endWorld.tris.push_back({ { t0, t1, t2 }, { tri.texUV[0], tri.texUV[1], tri.texUV[2] }, tri.color, tri.normal});
		}

		outMesh = endWorld;
    }
}