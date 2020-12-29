#include "ComponentTransform.h"

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
	translation = float3(assimp_translation.x, assimp_translation.y, assimp_translation.z);

	rotation_quat = Quat(assimp_rotation.x, assimp_rotation.y, assimp_rotation.z, assimp_rotation.w);

	local_matrix = float4x4::FromTRS(translation, rotation_quat, scale);
}
