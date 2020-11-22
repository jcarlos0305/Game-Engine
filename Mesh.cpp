#include "Mesh.h"
#include "Application.h"
#include "ModuleCamera.h"
#include "ModuleRender.h"
#include <GL/glew.h>
#include "MathGeoLib/Math/float2.h"

#include "LeakTest.h"

Mesh::Mesh(unsigned int program) : program(program) {}

void Mesh::LoadVBO(const aiMesh* mesh) {

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	unsigned vertex_size = (sizeof(float) * 3 + sizeof(float) * 2);
	unsigned vertices_size = vertex_size * mesh->mNumVertices;

	glBufferData(GL_ARRAY_BUFFER, vertices_size, nullptr, GL_STATIC_DRAW);

	float* uvs = (float*)(glMapBufferRange(GL_ARRAY_BUFFER, 0, vertices_size, GL_MAP_WRITE_BIT));

	for (unsigned i = 0, position = 0; i < mesh->mNumVertices; ++i) {
		// vertices
		uvs[position++] = mesh->mVertices[i].x;
		uvs[position++] = mesh->mVertices[i].y;
		uvs[position++] = mesh->mVertices[i].z;
		// UV 
		uvs[position++] = mesh->mTextureCoords[0][i].x;
		uvs[position++] = mesh->mTextureCoords[0][i].y;
	}

	glUnmapBuffer(GL_ARRAY_BUFFER);
	num_vertices = mesh->mNumVertices;
}

void Mesh::LoadEBO(const aiMesh* mesh) {
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	unsigned index_size = sizeof(unsigned) * mesh->mNumFaces * 3;

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_size, nullptr, GL_STATIC_DRAW);
	unsigned* indices = (unsigned*)(glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, 0, index_size, GL_MAP_WRITE_BIT));

	for (unsigned i = 0; i < mesh->mNumFaces; ++i) {
		assert(mesh->mFaces[i].mNumIndices == 3);

		*(indices++) = mesh->mFaces[i].mIndices[0];
		*(indices++) = mesh->mFaces[i].mIndices[1];
		*(indices++) = mesh->mFaces[i].mIndices[2];
	}

	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
	num_indices = mesh->mNumFaces * 3;
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

void Mesh::Draw(const std::vector<unsigned>& model_textures) {

	float4x4 proj = App->camera->frustum.ProjectionMatrix();
	float4x4 view = App->camera->frustum.ViewMatrix();
	float4x4 model = float4x4::identity;

	glUseProgram(program);

	glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_TRUE, (const float*)&model);
	glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_TRUE, (const float*)&view);
	glUniformMatrix4fv(glGetUniformLocation(program, "proj"), 1, GL_TRUE, (const float*)&proj);

	glUniform1i(glGetUniformLocation(program, "mytexture"), 0);

	glBindVertexArray(vao);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, model_textures[material_index]);

	glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, nullptr);

	glBindVertexArray(0);
}