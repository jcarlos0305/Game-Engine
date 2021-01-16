#include "ComponentTransform.h"
#include "Resources/GameObject.h"
#include "Utils/UUID.h"
#include "Utils/Utils.h"

#include <assimp/cimport.h>

ComponentTransform::ComponentTransform() {
	type = ComponentTypes::kTransform;
	SetUUID(custom_UUID::generate());
}

ComponentTransform::ComponentTransform(Json::Value& _component_data, GameObject* _game_object) {
	type = ComponentTypes::kTransform;
	SetOwner(_game_object);
	FromJson(_component_data);
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

	rotation_quat = Quat::FromEulerXYZ(DEGTORAD(rotation_vector.x), DEGTORAD(rotation_vector.y), DEGTORAD(rotation_vector.z));

	local_matrix = float4x4::FromTRS(translate, rotation_quat, scale);
	UpdateGlobalMatrix();
}

void ComponentTransform::FromJson(Json::Value& _component_data) {
	SetTransform(
		float3(_component_data[JSON_PROPERTY_TRANSLATE][0].asFloat(),
		_component_data[JSON_PROPERTY_TRANSLATE][1].asFloat(),
		_component_data[JSON_PROPERTY_TRANSLATE][2].asFloat()),

		float3(_component_data[JSON_PROPERTY_ROTATION][0].asFloat(),
		_component_data[JSON_PROPERTY_ROTATION][1].asFloat(),
		_component_data[JSON_PROPERTY_ROTATION][2].asFloat()),

		float3(_component_data[JSON_PROPERTY_SCALE][0].asFloat(),
		_component_data[JSON_PROPERTY_SCALE][1].asFloat(),
		_component_data[JSON_PROPERTY_SCALE][2].asFloat())
	);
}

void ComponentTransform::UpdateGlobalMatrix() {
	global_matrix = game_object->GetParent() != nullptr ? game_object->GetParent()->GetGlobalMatrix() * local_matrix : local_matrix;
}

void ComponentTransform::ToJson(Json::Value& _owner_root) const {
	Json::Value component_transform_root;

	Json::Value _scale(Json::arrayValue);
	Float3ToJson(_scale, scale);

	Json::Value _rotation(Json::arrayValue);
	Float3ToJson(_rotation, rotation);

	Json::Value _translate(Json::arrayValue);
	Float3ToJson(_translate, translate);

	component_transform_root[JSON_PROPERTY_UUID] = UUID;
	component_transform_root[JSON_PROPERTY_TYPE] = (int)type;
	component_transform_root[JSON_PROPERTY_SCALE] = _scale;
	component_transform_root[JSON_PROPERTY_ROTATION] = _rotation;
	component_transform_root[JSON_PROPERTY_TRANSLATE] = _translate;

	_owner_root.append(component_transform_root);

	//std::string name = "component_transform_" + UUID;
	//PrintToFile(name, component_transform_root);
}