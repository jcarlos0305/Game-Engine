#include "ComponentTransform.h"
#include "Resources/GameObject.h"

#include <assimp/cimport.h>

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
	global_matrix = game_object->GetParent() != nullptr ? game_object->GetParent()->GetGlobalMatrix() * local_matrix : local_matrix;
}

void ComponentTransform::SetTransform(float3 translate_vector, float3 rotation_vector, float3 scale_vector) {
	scale = scale_vector;
	rotation = rotation_vector;
	translate = translate_vector;

	//rotation_quat = Quat(rotation_vector.x, rotation_vector.y, rotation_vector.z, 1.0f);
	rotation_quat = Quat::FromEulerXYZ(rotation_vector.x, rotation_vector.y, rotation_vector.z);

	local_matrix = float4x4::FromTRS(translate, rotation_quat, scale);
	global_matrix = game_object->GetParent() != nullptr ? game_object->GetParent()->GetGlobalMatrix() * local_matrix : local_matrix;
}