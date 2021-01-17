#pragma once

#include "Component.h"

#include "Math/float3.h"
#include "Math/float4x4.h"
#include "Math/Quat.h"

#include <assimp/matrix4x4.h>

class ComponentTransform : public Component {
public:
	ComponentTransform();
	ComponentTransform(Json::Value& _component_transform_data, GameObject* _game_object);

	void SetTransform(const aiMatrix4x4& matrix);
	void SetTransform(float3 position_vector, float3 rotation_vector, float3 scale_vector);

	void ToJson(Json::Value& _owner_root) const override;
	void FromJson(Json::Value& _component_data) override;
	void UpdateGlobalMatrix();
	void RecursiveUpdateBoundingBox(GameObject* game_object);

	inline float3 GetScale() { return scale; };
	inline float3 GetRotation() { return rotation; };
	inline float3 GetTranslate() { return translate; };

	float4x4 GetLocalMatrix() { return local_matrix; };
	float4x4 GetGlobalMatrix() { return global_matrix; };

private:
	float3 scale = float3::one;
	float3 rotation = float3::zero;
	float3 translate = float3::zero;

	Quat rotation_quat = Quat::identity;

	float4x4 local_matrix = float4x4::identity;
	float4x4 global_matrix = float4x4::identity;
};