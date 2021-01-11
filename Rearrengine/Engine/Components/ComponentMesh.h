#pragma once

#include "Resources/Mesh.h";
#include "Component.h"

class ComponentMesh : public Component {
public:
	ComponentMesh();
	~ComponentMesh();

	inline void SetMesh(Mesh* _mesh) { mesh = _mesh; }
	inline Mesh* GetMesh() { return mesh; };

	inline float3 GetMaxsVertex() { return float3(mesh->max_x, mesh->max_y, mesh->max_z); }
	inline float3 GetMinsVertex() { return float3(mesh->min_x, mesh->min_y, mesh->min_z); }

	void Draw() const;

private:
	Mesh* mesh = nullptr;
};