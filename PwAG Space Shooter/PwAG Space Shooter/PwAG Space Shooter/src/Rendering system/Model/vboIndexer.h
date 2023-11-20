#pragma once
#include "dataOBJ.h"
#include "indexedDataOBJ.h"

struct PackedVertex
{
	glm::vec3 _position;
	glm::vec2 uv;
	glm::vec3 normal;

	bool operator<(const PackedVertex that) const
	{
		return memcmp((void*)this, (void*)&that, sizeof(PackedVertex)) > 0;
	};
};

class ObjectDataIndexer
{
public:
	// Constructors / Destructor
	ObjectDataIndexer() = delete;

	// Indexing
	static IndexedDataOBJ indexVBO_TBN(DataOBJ& dataObj);

	static void indexVBO(
		std::vector<glm::vec3>& in_vertices,
		std::vector<glm::vec2>& in_uvs,
		std::vector<glm::vec3>& in_normals,

		std::vector<unsigned short>& out_indices,
		std::vector<glm::vec3>& out_vertices,
		std::vector<glm::vec2>& out_uvs,
		std::vector<glm::vec3>& out_normals
	);

	static void indexVBO_TBN(
		std::vector<glm::vec3>& in_vertices,
		std::vector<glm::vec2>& in_uvs,
		std::vector<glm::vec3>& in_normals,
		std::vector<glm::vec3>& in_tangents,
		std::vector<glm::vec3>& in_bitangents,

		std::vector<unsigned short>& out_indices,
		std::vector<glm::vec3>& out_vertices,
		std::vector<glm::vec2>& out_uvs,
		std::vector<glm::vec3>& out_normals,
		std::vector<glm::vec3>& out_tangents,
		std::vector<glm::vec3>& out_bitangents
	);

	static void indexVBO_slow(
		std::vector<glm::vec3>& in_vertices,
		std::vector<glm::vec2>& in_uvs,
		std::vector<glm::vec3>& in_normals,

		std::vector<unsigned short>& out_indices,
		std::vector<glm::vec3>& out_vertices,
		std::vector<glm::vec2>& out_uvs,
		std::vector<glm::vec3>& out_normals
	);

private:
	// Getters
	static bool _isNear(float v1, float v2);

	static bool _getSimilarVertexIndex(
		glm::vec3& in_vertex,
		glm::vec2& in_uv,
		glm::vec3& in_normal,
		std::vector<glm::vec3>& out_vertices,
		std::vector<glm::vec2>& out_uvs,
		std::vector<glm::vec3>& out_normals,
		unsigned short& result
	);

	static bool _getSimilarVertexIndexFast(
		PackedVertex& packed,
		std::map<PackedVertex, unsigned short>& VertexToOutIndex,
		unsigned short& result
	);
};