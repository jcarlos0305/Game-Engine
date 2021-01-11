#pragma once

#include "Math/float4x4.h"
#include <assimp/mesh.h>
#include <vector>

class Mesh {
public:
	Mesh(unsigned int program);
	~Mesh();

	void LoadVBO(const aiMesh* mesh);
	void LoadEBO(const aiMesh* mesh);
	void CreateVAO();
	void Draw(const std::vector<unsigned>& model_textures, float4x4 model);
	void ToJson() const;

	unsigned int num_vertices = 0;
	unsigned int num_faces = 0;
	unsigned int num_indices = 0;
	unsigned int material_index = 0;

	float min_x, max_x;
	float min_y, max_y;
	float min_z, max_z;

private:
	unsigned int program = 0;
	unsigned int vao = 0;
	unsigned int vbo = 0;
	unsigned int ebo = 0;
};