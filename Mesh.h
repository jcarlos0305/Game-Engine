#pragma once

#include <assimp/mesh.h>
#include <vector>

class Mesh {

public:
	Mesh(unsigned int program);
	void LoadVBO(const aiMesh* mesh);
	void LoadEBO(const aiMesh* mesh);
	void CreateVAO();
	void Draw(const std::vector<unsigned>& model_textures);

	unsigned int num_vertices = 0;
	unsigned int num_indices = 0;
	unsigned int material_index = 0;

	unsigned vao = 0;
	unsigned vbo = 0;
	unsigned ebo = 0;

private:
	unsigned int program = 0;
};