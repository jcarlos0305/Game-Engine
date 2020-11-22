#include "ModuleModel.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleProgram.h"

#include <GL\glew.h>
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "LeakTest.h"

ModuleModel::ModuleModel() {}

bool ModuleModel::Init() {
	return true;
}

void ModuleModel::Load(const char* model_path, const char* vertex_shader_path, const char* fragment_shader_path) {
	unsigned int vertex_shader = 0;
	unsigned int fragment_shader = 0;
	unsigned int program = 0;

	char* vertex_shader_url = App->program->LoadShaderSource(vertex_shader_path);
	if (vertex_shader_url) vertex_shader = App->program->CompileShader(GL_VERTEX_SHADER, vertex_shader_url);

	char* fragment_shader_url = App->program->LoadShaderSource(fragment_shader_path);
	if (fragment_shader_url) fragment_shader = App->program->CompileShader(GL_FRAGMENT_SHADER, fragment_shader_url);

	if (vertex_shader && fragment_shader)
	program = App->program->CreateProgram(vertex_shader, fragment_shader);

	const aiScene* scene = aiImportFile(model_path, aiProcessPreset_TargetRealtime_MaxQuality);
	if ( program && scene) {

		LoadTextures(scene->mMaterials, scene->mNumMaterials);
		LoadMeshes(scene->mMeshes, scene->mNumMeshes, program);
	}
	else {
		LOG("Error loading %s: %s", model_path, aiGetErrorString());
	}
	aiReleaseImport(scene);
}

void ModuleModel::LoadTextures(aiMaterial** const mMaterials, unsigned int mNumMaterials) {
	aiString file;
	textures.reserve(mNumMaterials);
	for (unsigned i = 0; i < mNumMaterials; ++i) {
		if (mMaterials[i]->GetTexture(aiTextureType_DIFFUSE, 0, &file) == AI_SUCCESS) {
			textures.push_back(App->texture->LoadTexture(file.data));
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
	meshes.reserve(mNumMeshes);

	for (unsigned int i = 0; i < mNumMeshes; i++) {
		meshes.push_back(Mesh(program));
		meshes[i].LoadVBO(mMeshes[i]);
		meshes[i].LoadEBO(mMeshes[i]);
		meshes[i].CreateVAO();
	}
}

void ModuleModel::Draw() {
	for (unsigned int i = 0; i < meshes.size(); i++) {
		meshes[i].Draw(textures);
	}
}
