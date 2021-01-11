#include "GameObject.h"
#include "Components/ComponentTransform.h"

#include "Main/Application.h"
#include "Modules/ModuleRender.h"
#include "Debug Draw/ModuleDebugDraw.h"
#include "Components/ComponentMesh.h"

GameObject::GameObject() {}

GameObject::~GameObject() {
	free(name);
	name = nullptr;
	for (Component* component : components) delete component; // ?
}

void GameObject::AddComponent(Component* _component)
{
	// Create GameObject's AABB if the component is a Mesh
	if (_component->GetType() == ComponentTypes::kMesh) {
		ComponentMesh* component_mesh = static_cast<ComponentMesh*>(_component);
		// Gets the AABB from Max-Min Mesh's Vertex
		aabb = AABB(component_mesh->GetMinsVertex(), component_mesh->GetMaxsVertex());
	}
	// Save the component
	components.push_back(_component);
}

bool GameObject::HasComponentType(ComponentTypes _type) const {
	for (Component* component : components) {
		if (component->GetType() == _type) return true;
	}
	return false;
}

Component* GameObject::GetComponentType(ComponentTypes _type) const {
	for (Component* component : components) {
		if (component->GetType() == _type) return component;
	}
	return nullptr;
}

const float4x4 GameObject::GetGlobalMatrix() const {
	ComponentTransform* transform = static_cast<ComponentTransform*>(GetComponentType(ComponentTypes::kTransform));
	return transform->GetGlobalMatrix();
}

void GameObject::UpdateChildrenGlobalMatrix() {
	for (GameObject* child : children) {
		ComponentTransform* transform = static_cast<ComponentTransform*>(child->GetComponentType(ComponentTypes::kTransform));
		transform->UpdateGlobalMatrix();
	}
}