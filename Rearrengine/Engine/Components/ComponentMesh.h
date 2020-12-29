#pragma once

#include "../Resources/Mesh.h";
#include "Component.h"

class ComponentMesh : public Component {
public:
	ComponentMesh();

	inline void SetMesh(Mesh* _mesh) { mesh = _mesh; }
	void Draw() const;

private:
	Mesh* mesh = nullptr;
};