#pragma once

#include "Def.h"
#include "Maths.h"

struct Vertex
{
	Vector3 position;
	Vector3 normal;
};

struct Mesh
{
	void *vertices;
	uint32 vertexCount;
	uint32 vertexStride;
	uint32 *indices;
	uint32 indexCount;
};

namespace UtilMesh
{
	Mesh MakeCubeCenteredWithNormals(float edgeSize);
	Mesh MakeScreenQuad();
	void Free(Mesh mesh);
}