#pragma once

#include "Module.h"
#include "Resources/Mesh.h"

#include <assimp/material.h>
#include "Math/float4x4.h"
#include "Math/float3.h"

#include <json/json.h>

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
	bool SearchTexture(const char* texture_path, const char* src_path);
	void LoadModelChildren(aiMesh** const mMeshes, unsigned int program, aiNode* node, GameObject* father);
	void LoadDefaultTextures(const char* src_path);
	void LoadTexturesFromJson(Json::Value& textures_root);

	void SetMinMax(Mesh* _mesh);
	void UpdateMinMax(float3& vector, Mesh* _mesh);

	float3 GetModelCenterPoint();

	float GetModelRadius();

	unsigned int GetNumVertices();
	bool CleanUp() override;

public:
	std::vector<Mesh> meshes;
	std::vector<unsigned int> textures;
	float4x4 model_matrix = float4x4::zero;

	float min_x, max_x;
	float min_y, max_y;
	float min_z, max_z;

private:
	Json::Value textures_root;
};