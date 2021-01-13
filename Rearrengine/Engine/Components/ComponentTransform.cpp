#include "ComponentTransform.h"
#include "Resources/GameObject.h"

#include <assimp/cimport.h>
#include <Components/ComponentMesh.h>


ComponentTransform::ComponentTransform() {
	type = ComponentTypes::kTransform;
}

void ComponentTransform::SetTransform(const aiMatrix4x4& matrix) {
	aiVector3D assimp_scale;
	aiQuaternion assimp_rotation;
	aiVector3D assimp_translation;

	aiDecomposeMatrix(&matrix, &assimp_scale, &assimp_rotation, &assimp_translation);

	scale = float3(assimp_scale.x, assimp_scale.y, assimp_scale.z);
	rotation = float3(matrix.b1, matrix.b2, matrix.b3);
	translate = float3(assimp_translation.x, assimp_translation.y, assimp_translation.z);

	rotation_quat = Quat(assimp_rotation.x, assimp_rotation.y, assimp_rotation.z, assimp_rotation.w);

	local_matrix = float4x4::FromTRS(translate, rotation_quat, scale);
	UpdateGlobalMatrix();
}

void ComponentTransform::SetTransform(float3 translate_vector, float3 rotation_vector, float3 scale_vector) {
	scale = scale_vector;
	rotation = rotation_vector;
	translate = translate_vector;

	rotation_quat = Quat::FromEulerXYZ(rotation_vector.x, rotation_vector.y, rotation_vector.z);

	local_matrix = float4x4::FromTRS(translate, rotation_quat, scale);
	UpdateGlobalMatrix();
}

void ComponentTransform::UpdateGlobalMatrix() {
	global_matrix = game_object->GetParent() != nullptr ? game_object->GetParent()->GetGlobalMatrix() * local_matrix : local_matrix;
}

void ComponentTransform::UpdateBoundingBox()
{
	// TODO: Optimize this method
	if (game_object->GetChildrenCount() > 0) {
		std::vector<GameObject*> children = game_object->GetChildren();
		for (GameObject* _gameObject : children) {
			AABB aabb = game_object->GetAABB();
			// Gets the AABB from Max-Min Mesh's Vertex
			ComponentMesh* component_mesh = static_cast<ComponentMesh*>(game_object->GetComponentType(ComponentTypes::kMesh));
			float3 mins = float3(component_mesh->GetMinsVertex().x * scale.x, component_mesh->GetMinsVertex().y * scale.y, component_mesh->GetMinsVertex().z * scale.z);
			float3 maxs = float3(component_mesh->GetMaxsVertex().x * scale.x, component_mesh->GetMaxsVertex().y * scale.y, component_mesh->GetMaxsVertex().z * scale.z);
			aabb = AABB(mins, maxs);
			game_object->SetAABB(aabb);
		}
	}
	/*AABB aabb = game_object->GetAABB();
	// Gets the AABB from Max-Min Mesh's Vertex
	ComponentMesh* component_mesh = static_cast<ComponentMesh*>(game_object->GetComponentType(ComponentTypes::kMesh));
	float3 mins = float3(component_mesh->GetMinsVertex().x * scale.x, component_mesh->GetMinsVertex().y * scale.y, component_mesh->GetMinsVertex().z * scale.z);
	float3 maxs = float3(component_mesh->GetMaxsVertex().x * scale.x, component_mesh->GetMaxsVertex().y * scale.y, component_mesh->GetMaxsVertex().z * scale.z);
	aabb = AABB(mins, maxs);*/
}
