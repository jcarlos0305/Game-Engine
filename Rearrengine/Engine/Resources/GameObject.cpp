#include "GameObject.h"
#include "Components/ComponentTransform.h"

GameObject::GameObject() {}

GameObject::~GameObject() {
	free(name);
	name = nullptr;
	for (Component* component : components) delete component;
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