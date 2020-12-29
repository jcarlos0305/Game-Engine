#pragma once

#include "Component.h"

#include "Math/float3.h"
#include "Math/float4x4.h"
#include "Math/Quat.h"
#include <assimp/matrix4x4.h>

class ComponentTransform : public Component {
public:
	ComponentTransform();
	
	void SetTransform(const aiMatrix4x4& matrix);

private:
	float3 scale       = float3::one;
	float3 rotation    = float3::zero;
	float3 translation = float3::zero;

	Quat rotation_quat    = Quat::identity;
	float4x4 local_matrix = float4x4::identity;

};