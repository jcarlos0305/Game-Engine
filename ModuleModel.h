#pragma once

#include "Module.h"
#include "Mesh.h"

#include <assimp/material.h>
#include "MathGeoLib/Math/float4x4.h"

class ModuleModel : public Module {

public:

	ModuleModel();
	~ModuleModel();

	bool Init();

	void Load(const char* model_path);
	void Load(const char* model_path, const char* vertex_shader_path, const char* fragment_shader_pat);

	unsigned int CreateProgram(const char* vertex_shader_path, const char* fragment_shader_path);

	void LoadTextures(aiMaterial** const mMaterials, unsigned int mNumMaterials, const char* src_path);
	void LoadMeshes(aiMesh** const mMeshes, unsigned int mNumMeshes, unsigned int program);

	float3 GetModelCenterPoint();

	float GetModelRadius();

	void Draw();

	unsigned int GetNumVertices();
	bool CleanUp();
	
public:
	std::vector<Mesh> meshes;
	std::vector<unsigned int> textures;
	float4x4 model_matrix = float4x4::zero;

	float min_x;
	float max_x;

	float min_y;
	float max_y;

	float min_z;
	float max_z;
};