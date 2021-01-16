#pragma once

#include "Resources/Mesh.h";
#include "Component.h"

class ComponentMesh : public Component {
public:
	ComponentMesh();
	ComponentMesh(Json::Value& _component_mesh_data, GameObject* _game_object);
	~ComponentMesh();

	inline void SetMesh(Mesh* _mesh) { mesh = _mesh; }
	inline Mesh* GetMesh() { return mesh; };
	void Draw() const;

	void ToJson(Json::Value& _owner_root) const override;
	void FromJson(Json::Value& _component_data) override;

private:
	Mesh* mesh = nullptr;
};