#include "UtilMesh.h"

#ifndef ARRAYSIZE
#define ARRAYSIZE(a) \
			((sizeof(a) / sizeof(*(a))) / \
			static_cast<size_t>(!(sizeof(a) % sizeof(*(a)))))
#endif


Mesh UtilMesh::MakeScreenQuad()
{
	Mesh mesh = {};
	const float vertices[] =
	{
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
	};

	uint32 indices[] =
	{
		0, 1, 2,
		2, 3, 0,
	};

	mesh.vertexCount = 4;
	mesh.vertexStride = sizeof(vertices) / mesh.vertexCount;
	mesh.vertices = (float*)malloc(mesh.vertexStride * mesh.vertexCount);
	mesh.indexCount = ARRAYSIZE(indices);
	mesh.indices = (uint32*)malloc(sizeof(uint32) * mesh.indexCount);

	memcpy(mesh.vertices, vertices, sizeof(vertices));
	memcpy(mesh.indices, indices, sizeof(indices));

	return mesh;
}

void UtilMesh::Free(Mesh mesh)
{
	free(mesh.vertices);
	free(mesh.indices);
}