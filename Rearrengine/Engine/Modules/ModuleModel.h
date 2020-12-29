#pragma once

#include "Module.h"
#include "../Resources/Mesh.h"

#include <assimp/material.h>
#include "Math/float4x4.h"

class GameObject;
struct aiNode;

class ModuleModel : public Module {

public:

	ModuleModel();
	~ModuleModel();

	bool Init() override;

	void Load(const char* model_path);
	void Load(const char* model_path, const char* vertex_shader_path, const char* fragment_shader_pat);

	unsigned int CreateProgram(const char* vertex_shader_path, const char* fragment_shader_path);

	void LoadTextures(aiMaterial** const mMaterials, unsigned int mNumMaterials, const char* src_path);
	void LoadMeshes(aiMesh** const mMeshes, unsigned int mNumMeshes, unsigned int program);
	void LoadModelChildren(aiMesh** const mMeshes, unsigned int program, aiNode* node, GameObject* father);

	void SetMinMax(Mesh* _mesh);

	float3 GetModelCenterPoint();

	float GetModelRadius();

	void Draw();

	unsigned int GetNumVertices();
	bool CleanUp() override;
	
public:
	std::vector<Mesh> meshes;
	std::vector<unsigned int> textures;
	float4x4 model_matrix = float4x4::zero;

	float min_x, max_x;
	float min_y, max_y;
	float min_z, max_z;
};