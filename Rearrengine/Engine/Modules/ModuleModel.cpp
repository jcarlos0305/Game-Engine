#include "../Utils/Globals.h"
#include "../Main/Application.h"
#include "ModuleModel.h"
#include "ModuleTexture.h"
#include "ModuleProgram.h"
#include "ModuleCamera.h"
#include "ModuleScene.h"
#include "../Resources/GameObject.h"
#include "../Components/ComponentMesh.h"
#include "../Components/ComponentTransform.h"

#include <GL\glew.h>
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>

#include "../Utils/LeakTest.h"
#include "../../Brofiler/Brofiler/Brofiler.h"

void AssimpLog(const char* msg, char* userData) {
	if (msg) LOG("Assimp %s", msg);
}

ModuleModel::ModuleModel() {
	min_x = 0.0; max_x = 0.0;
	min_y = 0.0; max_y = 0.0;
	min_z = 0.0; max_z = 0.0;
}

ModuleModel::~ModuleModel() {}

bool ModuleModel::Init() {
	struct aiLogStream stream;
	stream.callback = AssimpLog;
	aiAttachLogStream(&stream);

	Load("assets/BakerHouse.fbx", "assets/vertex.glsl", "assets/fragment.glsl");

	return true;
}

void ModuleModel::Load(const char* file_path) {
	char file_ext[_MAX_EXT];
	_splitpath_s(file_path, NULL, 0, NULL, 0, NULL, 0, file_ext, _MAX_EXT);

	if (strcmp(file_ext, ".fbx") == 0) {
		LOG("Loading model %s", file_path);
		Load(file_path, "assets/vertex.glsl", "assets/fragment.glsl");
	}
	else if (strcmp(file_ext, ".png") == 0 || strcmp(file_ext, ".dds") == 0 || strcmp(file_ext, ".jpg") == 0 || strcmp(file_ext, ".jpeg") == 0) {
		LOG("Loading texture %s", file_path);

		unsigned int loaded_texture = App->texture->LoadTexture(file_path);
		if (loaded_texture) {
			if (!textures.empty()) {
				textures.clear();
				textures.shrink_to_fit();
			}
			textures.push_back(loaded_texture);
			LOG("Texture loaded successfully");
		}
	}
}

void ModuleModel::Load(const char* model_path, const char* vertex_shader_path, const char* fragment_shader_path) {
	unsigned int program = CreateProgram(vertex_shader_path, fragment_shader_path);
	const aiScene* scene = aiImportFile(model_path, aiProcessPreset_TargetRealtime_MaxQuality);
	if (program && scene) {
		LOG("Shaders program created successfully!\n");
		LoadTextures(scene->mMaterials, scene->mNumMaterials, model_path);
		
		char model_name[_MAX_FNAME];
		_splitpath_s(model_path, NULL, 0, NULL, 0, model_name, _MAX_FNAME, NULL, 0);

		GameObject* game_object = new GameObject();
		game_object->SetName(_strdup(model_name));

		ComponentTransform* component_transform = new ComponentTransform();
		game_object->AddComponent(component_transform);

		LoadModelChildren(scene->mMeshes, program, scene->mRootNode, game_object);
		LOG("Model loaded successfully!\n");
		
		App->scene->GetRoot()->AddChild(game_object);
	}
	else {
		LOG("Error loading %s: %s", model_path, aiGetErrorString());
	}
	aiReleaseImport(scene);
}

unsigned int ModuleModel::CreateProgram(const char* vertex_shader_path, const char* fragment_shader_path) {
	unsigned int vertex_shader = 0;
	unsigned int fragment_shader = 0;
	unsigned int program = 0;

	char* vertex_shader_url = App->program->LoadShaderSource(vertex_shader_path);
	if (vertex_shader_url) vertex_shader = App->program->CompileShader(GL_VERTEX_SHADER, vertex_shader_url);

	char* fragment_shader_url = App->program->LoadShaderSource(fragment_shader_path);
	if (fragment_shader_url) fragment_shader = App->program->CompileShader(GL_FRAGMENT_SHADER, fragment_shader_url);

	if (vertex_shader && fragment_shader) {
		program = App->program->CreateProgram(vertex_shader, fragment_shader);
	}
	return program;
}

void ModuleModel::LoadTextures(aiMaterial** const mMaterials, unsigned int mNumMaterials, const char* src_path) {
	aiString file;

	if (!textures.empty()) {
		textures.clear();
		textures.shrink_to_fit();
	}

	textures.reserve(mNumMaterials);
	for (unsigned i = 0; i < mNumMaterials; ++i) {
		if (mMaterials[i]->GetTexture(aiTextureType_DIFFUSE, 0, &file) == AI_SUCCESS) {
			LOG("Looking for: .\\%s", file.data);
			unsigned int loaded_texture = App->texture->LoadTexture(file.data);

			if (loaded_texture) {
				LOG("Texture loaded successfully!\n");
				textures.push_back(loaded_texture);
			}
			else {
				LOG("Texture not found, looking in the source path...");

				char src_file_dir[_MAX_DIR];
				char src_file_drive[_MAX_DRIVE];
				_splitpath_s(src_path, src_file_drive, _MAX_DRIVE, src_file_dir, _MAX_DIR, NULL, 0, NULL, 0);

				char texture_file_name[_MAX_FNAME];
				char texture_file_ext[_MAX_EXT];
				_splitpath_s(file.data, NULL, 0, NULL, 0, texture_file_name, _MAX_FNAME, texture_file_ext, _MAX_EXT);

				char full_path[_MAX_PATH];
				_makepath_s(full_path, _MAX_PATH, src_file_drive, src_file_dir, texture_file_name, texture_file_ext);

				LOG("Looking for: %s", full_path);
				loaded_texture = App->texture->LoadTexture(full_path);

				if (loaded_texture) {
					LOG("Texture loaded successfully!\n");
					textures.push_back(loaded_texture);
				}
				else {
					LOG("Texture not found, looking the Textures folder...");

					std::string final_path = ".\\assets\\Textures\\";
					final_path.append(texture_file_name);
					final_path.append(texture_file_ext);

					LOG("Looking for: %s", final_path.c_str());
					loaded_texture = App->texture->LoadTexture(final_path.c_str());

					if (loaded_texture) {
						LOG("Texture loaded successfully!\n");
						textures.push_back(loaded_texture);
					}
					else {
						LOG("Well.. we tried!\n");
					}
				}
			}
		}
	}
}

unsigned int ModuleModel::GetNumVertices() {
	unsigned int total_vertices = 0;
	for (unsigned int i = 0; i < meshes.size(); i++) {
		total_vertices += meshes[i].num_indices;
	}
	return total_vertices;
}

void ModuleModel::LoadModelChildren(aiMesh** const mMeshes, unsigned int program, aiNode* node, GameObject* father) {
	BROFILER_CATEGORY("Load model meshes", Profiler::Color::Blue);
	for (unsigned int i = 0; i < node->mNumChildren; i++) {

		GameObject* game_object = new GameObject();
		game_object->SetName(_strdup(node->mChildren[i]->mName.C_Str()));

		ComponentTransform* component_transform = new ComponentTransform();
		component_transform->SetTransform(node->mChildren[i]->mTransformation);

		game_object->AddComponent(component_transform);

		if (node->mChildren[i]->mNumMeshes == 1) {
			Mesh* mesh = new Mesh(program);
			mesh->LoadVBO(mMeshes[node->mChildren[i]->mMeshes[0]]);
			mesh->LoadEBO(mMeshes[node->mChildren[i]->mMeshes[0]]);
			mesh->CreateVAO();

			if (i == 0) {
				max_x = mesh->max_x; min_x = mesh->min_x;
				max_y = mesh->max_y; min_y = mesh->min_y;
				max_z = mesh->max_z; min_z = mesh->min_z;
			}
			else {
				SetMinMax(mesh);
			}

			ComponentMesh* mesh_component = new ComponentMesh();
			mesh_component->SetMesh(mesh);

			game_object->AddComponent(mesh_component);
		}
		father->AddChild(game_object);
	}
	App->camera->SetFocusToModel(GetModelCenterPoint(), GetModelRadius());
}

void ModuleModel::SetMinMax(Mesh* _mesh) {
	if (_mesh->max_x > max_x) max_x = _mesh->max_x;
	if (_mesh->min_x < min_x) min_x = _mesh->min_x;
	if (_mesh->max_y > max_y) max_y = _mesh->max_y;
	if (_mesh->min_y < min_y) min_y = _mesh->min_y;
	if (_mesh->max_z > max_z) max_z = _mesh->max_z;
	if (_mesh->min_z < min_z) min_z = _mesh->min_z;
}

float3 ModuleModel::GetModelCenterPoint() {
	return float3((max_x + min_x) / 2, (max_y + min_y) / 2, (max_z + min_z) / 2);
}

float ModuleModel::GetModelRadius() {
	return float3(max_x - min_x, max_y - min_y, max_z - min_z).Length() / 2;
}

void ModuleModel::Draw() {
	model_matrix = float4x4::identity;

	for (unsigned int i = 0; i < meshes.size(); i++) {
		meshes[i].Draw(textures, model_matrix);
	}
}

bool ModuleModel::CleanUp() {
	textures.clear();
	meshes.clear();
	return true;
}