#pragma once

#include "Module.h"
#include "Mesh.h"

#include <assimp/material.h>

class ModuleModel : public Module {

public:

	ModuleModel();

	bool Init();

	void Load(const char* model_path);

	void Load(const char* model_path, const char* vertex_shader_path, const char* fragment_shader_pat);
	unsigned int CreateProgram(const char* vertex_shader_path, const char* fragment_shader_path);
	void LoadMeshes(aiMesh** const mMeshes, unsigned int mNumMeshes, unsigned int program);
	void Draw();
	void LoadTextures(aiMaterial** const mMaterials, unsigned int mNumMaterials, const char* src_path);

	unsigned int GetNumVertices();

	std::vector<Mesh> meshes;
	std::vector<unsigned int> textures;

	bool CleanUp();
};