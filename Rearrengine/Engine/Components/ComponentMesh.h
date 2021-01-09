#pragma once

#include "Resources/Mesh.h";
#include "Component.h"

class ComponentMesh : public Component {
public:
	ComponentMesh();
	~ComponentMesh();

	inline void SetMesh(Mesh* _mesh) { mesh = _mesh; }
	inline Mesh* GetMesh() { return mesh; };
	void Draw() const;

private:
	Mesh* mesh = nullptr;
};