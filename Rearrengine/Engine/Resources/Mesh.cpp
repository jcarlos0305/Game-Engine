#include "Mesh.h"
#include "Main/Application.h"
#include "Modules/ModuleCamera.h"
#include "Debug Draw/ModuleDebugDraw.h"
#include "Modules/ModuleRender.h"
#include "Modules/ModuleModel.h"
#include "Utils/Utils.h"
#include "Utils/UUID.h"

#include <GL/glew.h>
#include "Math/float2.h"

#include "Utils/LeakTest.h"

Mesh::Mesh(unsigned int program) : program(program), UUID(custom_UUID::generate()) {
	min_x = 0.0; max_x = 0.0;
	min_y = 0.0; max_y = 0.0;
	min_z = 0.0; max_z = 0.0;
}

Mesh::Mesh(std::string _mesh_path) {
	FromJson(_mesh_path);
}

Mesh::~Mesh() {
	program = 0;
	vao = 0;
	vbo = 0;
	ebo = 0;
}

void Mesh::LoadVBO(const aiMesh* mesh) {
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	unsigned vertex_size = (sizeof(float) * 3 + sizeof(float) * 2);
	unsigned vertices_size = vertex_size * mesh->mNumVertices;

	name = mesh->mName.C_Str();
	material_index = mesh->mMaterialIndex;
	num_vertices = mesh->mNumVertices;
	num_faces = mesh->mNumFaces;

	glBufferData(GL_ARRAY_BUFFER, vertices_size, nullptr, GL_STATIC_DRAW);

	float* uvs = (float*)(glMapBufferRange(GL_ARRAY_BUFFER, 0, vertices_size, GL_MAP_WRITE_BIT));

	min_x = mesh->mVertices[0].x; min_y = mesh->mVertices[0].y; min_z = mesh->mVertices[0].z;
	max_x = mesh->mVertices[0].x; max_y = mesh->mVertices[0].y; max_z = mesh->mVertices[0].z;

	Json::Value vbo_json(Json::arrayValue);

	for (unsigned i = 0, position = 0; i < mesh->mNumVertices; ++i) {
		if (mesh->mVertices[i].x > max_x) max_x = mesh->mVertices[i].x;
		if (mesh->mVertices[i].x < min_x) min_x = mesh->mVertices[i].x;
		if (mesh->mVertices[i].y > max_y) max_y = mesh->mVertices[i].y;
		if (mesh->mVertices[i].y < min_y) min_y = mesh->mVertices[i].y;
		if (mesh->mVertices[i].z > max_z) max_z = mesh->mVertices[i].z;
		if (mesh->mVertices[i].z < min_z) min_z = mesh->mVertices[i].z;

		// vertices
		uvs[position++] = mesh->mVertices[i].x; vbo_json.append(mesh->mVertices[i].x);
		uvs[position++] = mesh->mVertices[i].y; vbo_json.append(mesh->mVertices[i].y);
		uvs[position++] = mesh->mVertices[i].z; vbo_json.append(mesh->mVertices[i].z);

		// UV
		if (mesh->mTextureCoords[0]) {
			uvs[position++] = mesh->mTextureCoords[0][i].x; vbo_json.append(mesh->mTextureCoords[0][i].x);
			uvs[position++] = mesh->mTextureCoords[0][i].y; vbo_json.append(mesh->mTextureCoords[0][i].y);
		}
		else {
			uvs[position++] = 0; vbo_json.append(0);
			uvs[position++] = 0; vbo_json.append(0);
		}
	}
	ToJson();
	mesh_root[JSON_PROPERTY_MESH][JSON_PROPERTY_MESH_VBO] = vbo_json;

	glUnmapBuffer(GL_ARRAY_BUFFER);
}

void Mesh::LoadVBO(Json::Value& _vbo_data) {
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	unsigned vertex_size = (sizeof(float) * 3 + sizeof(float) * 2);
	unsigned vertices_size = vertex_size * num_vertices;

	glBufferData(GL_ARRAY_BUFFER, vertices_size, nullptr, GL_STATIC_DRAW);

	float* uvs = (float*)(glMapBufferRange(GL_ARRAY_BUFFER, 0, vertices_size, GL_MAP_WRITE_BIT));
	unsigned int i = 0;

	for (Json::Value vbo_vertex : _vbo_data) {
		uvs[i++] = vbo_vertex.asFloat();
	}

	glUnmapBuffer(GL_ARRAY_BUFFER);
}

void Mesh::LoadEBO(const aiMesh* mesh) {
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	unsigned index_size = sizeof(unsigned) * mesh->mNumFaces * 3;

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_size, nullptr, GL_STATIC_DRAW);
	unsigned* indices = (unsigned*)(glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, 0, index_size, GL_MAP_WRITE_BIT));

	Json::Value ebo_json(Json::arrayValue);

	for (unsigned i = 0; i < mesh->mNumFaces; ++i) {
		for (unsigned j = 0; j < mesh->mFaces[i].mNumIndices; j++) {
			*(indices++) = mesh->mFaces[i].mIndices[j]; ebo_json.append(mesh->mFaces[i].mIndices[j]);
		}
	}
	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);

	num_indices = mesh->mNumFaces * 3;
	mesh_root[JSON_PROPERTY_MESH][JSON_PROPERTY_MESH_NUM_INDICES] = num_indices;

	mesh_root[JSON_PROPERTY_MESH][JSON_PROPERTY_MESH_EBO] = ebo_json;

	PrintToFile(name, JSON_MESH_DIRECTORY, mesh_root);
}

void Mesh::LoadEBO(Json::Value& _ebo_data) {
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	unsigned index_size = sizeof(unsigned) * num_faces * 3;

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_size, nullptr, GL_STATIC_DRAW);
	unsigned* indices = (unsigned*)(glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, 0, index_size, GL_MAP_WRITE_BIT));
	unsigned int i = 0;

	for (Json::Value ebo_index : _ebo_data) {
		indices[i++] = ebo_index.asFloat();
	}
	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
}

void Mesh::CreateVAO() {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3 + sizeof(float) * 2, (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 3 + sizeof(float) * 2, (void*)(sizeof(float) * 3));

	glBindVertexArray(0);
}

void Mesh::Draw(const std::vector<unsigned>& model_textures, const float4x4 model) {

	float4x4 proj  = App->camera->GetActiveCamera()->GetCamera()->GetProjectionMatrix();
	float4x4 view  = App->camera->GetActiveCamera()->GetCamera()->GetViewMatrix();

	glUseProgram(program);

	glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_TRUE, (const float*)&model);
	glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_TRUE, (const float*)&view);
	glUniformMatrix4fv(glGetUniformLocation(program, "proj"), 1, GL_TRUE, (const float*)&proj);

	glUniform1i(glGetUniformLocation(program, "mytexture"), 0);

	glBindVertexArray(vao);
	glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, model_textures[material_index]); TODO: This will be updated with the materials
	glBindTexture(GL_TEXTURE_2D, model_textures[0]);

	glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, nullptr);

	glBindVertexArray(0);
}

void Mesh::ToJson() {
	mesh_root[JSON_PROPERTY_MESH][JSON_PROPERTY_MESH_NAME] = name;
	mesh_root[JSON_PROPERTY_MESH][JSON_PROPERTY_MESH_NUM_FACES] = num_faces;
	mesh_root[JSON_PROPERTY_MESH][JSON_PROPERTY_MESH_NUM_VERTICES] = num_vertices;
	mesh_root[JSON_PROPERTY_MESH][JSON_PROPERTY_MESH_MATERIAL_INDEX] = material_index;

	mesh_root[JSON_PROPERTY_MESH][JSON_PROPERTY_MESH_MIN_X] = min_x;
	mesh_root[JSON_PROPERTY_MESH][JSON_PROPERTY_MESH_MIN_Y] = min_y;
	mesh_root[JSON_PROPERTY_MESH][JSON_PROPERTY_MESH_MIN_Z] = min_z;

	mesh_root[JSON_PROPERTY_MESH][JSON_PROPERTY_MESH_MAX_X] = max_x;
	mesh_root[JSON_PROPERTY_MESH][JSON_PROPERTY_MESH_MAX_Y] = max_y;
	mesh_root[JSON_PROPERTY_MESH][JSON_PROPERTY_MESH_MAX_Z] = max_z;
}

void Mesh::FromJson(std::string _mesh_path) {
	Json::Value mesh_root;
	LoadFromFile(_mesh_path, mesh_root);

	name = _strdup(mesh_root[JSON_PROPERTY_MESH][JSON_PROPERTY_MESH_NAME].asCString());
	num_faces = mesh_root[JSON_PROPERTY_MESH][JSON_PROPERTY_MESH_NUM_FACES].asInt();
	num_vertices = mesh_root[JSON_PROPERTY_MESH][JSON_PROPERTY_MESH_NUM_VERTICES].asInt();
	material_index = mesh_root[JSON_PROPERTY_MESH][JSON_PROPERTY_MESH_MATERIAL_INDEX].asInt();
	num_indices = mesh_root[JSON_PROPERTY_MESH][JSON_PROPERTY_MESH_NUM_INDICES].asInt();

	min_x = mesh_root[JSON_PROPERTY_MESH][JSON_PROPERTY_MESH_MIN_X].asFloat();
	min_y = mesh_root[JSON_PROPERTY_MESH][JSON_PROPERTY_MESH_MIN_Y].asFloat();
	min_z = mesh_root[JSON_PROPERTY_MESH][JSON_PROPERTY_MESH_MIN_Z].asFloat();

	max_x = mesh_root[JSON_PROPERTY_MESH][JSON_PROPERTY_MESH_MAX_X].asFloat();
	max_y = mesh_root[JSON_PROPERTY_MESH][JSON_PROPERTY_MESH_MAX_Y].asFloat();
	max_z = mesh_root[JSON_PROPERTY_MESH][JSON_PROPERTY_MESH_MAX_Z].asFloat();

	program = App->model->CreateProgram("assets/vertex.glsl", "assets/fragment.glsl");

	LoadVBO(mesh_root[JSON_PROPERTY_MESH][JSON_PROPERTY_MESH_VBO]);
	LoadEBO(mesh_root[JSON_PROPERTY_MESH][JSON_PROPERTY_MESH_EBO]);
	CreateVAO();
}