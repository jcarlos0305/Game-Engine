#include "ModuleModel.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleProgram.h"

#include <GL\glew.h>
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>

#include "LeakTest.h"

void AssimpLog(const char* msg, char* userData) {
	if (msg) LOG("Assimp %s", msg);
}

ModuleModel::ModuleModel() {}

ModuleModel::~ModuleModel() {}

bool ModuleModel::Init() {
	struct aiLogStream stream;
	stream.callback = AssimpLog;
	aiAttachLogStream(&stream);
	return true;
}

void ModuleModel::Load(const char* file_path) {
	char file_ext[_MAX_EXT];
	_splitpath_s(file_path, NULL, 0, NULL, 0, NULL, 0, file_ext, _MAX_EXT);

	if (strcmp(file_ext,".fbx") == 0) {
		LOG("Loading model %s", file_path);
		Load(file_path, "../vertex.glsl", "../fragment.glsl");
	}
	else if (strcmp(file_ext, ".png" ) == 0 || strcmp(file_ext, ".dds" ) == 0 || strcmp(file_ext, ".jpg" ) == 0 || strcmp(file_ext, ".jpeg") == 0) {
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
		LoadMeshes(scene->mMeshes, scene->mNumMeshes, program);
		LOG("Model loaded successfully!\n");
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

void ModuleModel::LoadMeshes(aiMesh** const mMeshes, unsigned int mNumMeshes, unsigned int program) {
	if (!meshes.empty()) {
		meshes.clear();
		meshes.shrink_to_fit();
	}

	meshes.reserve(mNumMeshes);

	for (unsigned int i = 0; i < mNumMeshes; i++) {
		meshes.push_back(Mesh(program));
		meshes[i].LoadVBO(mMeshes[i]);
		meshes[i].LoadEBO(mMeshes[i]);
		meshes[i].CreateVAO();
	}
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
