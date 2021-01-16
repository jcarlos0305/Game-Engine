#pragma once

#include "Math/float4x4.h"

#include <assimp/mesh.h>
#include <vector>
#include <string>
#include <json/json.h>

class Mesh {
public:
	Mesh(unsigned int program);
	Mesh(std::string _mesh_path);
	~Mesh();

	void LoadVBO(const aiMesh* mesh);
	void LoadVBO(Json::Value& _vbo_data);
	void LoadEBO(const aiMesh* mesh);
	void LoadEBO(Json::Value& _ebo_data);
	void CreateVAO();
	void Draw(const std::vector<unsigned>& model_textures, float4x4 model);
	void ToJson();
	void FromJson(std::string _mesh_path);
	std::string GetName() const { return name; };

	unsigned int num_vertices = 0;
	unsigned int num_faces = 0;
	unsigned int num_indices = 0;
	unsigned int material_index = 0;

	float min_x, max_x;
	float min_y, max_y;
	float min_z, max_z;

private:
	Json::Value mesh_root;
	std::string UUID;
	std::string name;
	unsigned int program = 0;
	unsigned int vao = 0;
	unsigned int vbo = 0;
	unsigned int ebo = 0;
};