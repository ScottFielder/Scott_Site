#include "Actor.h"
#include "TransformComponent.h"


Actor::Actor(Component* parent_):Component(parent_) {}

Actor::~Actor() {}

bool Actor::OnCreate() {
	for (auto component : components) {
		bool status = component->OnCreate();
		if (status == false) {
			return false;
		}
	}
	return true;
}

void Actor::OnDestroy() {
}

void Actor::Update(const float deltaTime){
};

void Actor::Render() const {
}

void Actor::ListComponents() const {
	std::cout << typeid(*this).name() << " contain the following components:\n";
	for (auto component : components) {
			std::cout << typeid(*component).name() << std::endl;	
	}
}


void Actor::RemoveAllComponents() {
	for (auto component : components) {
		component->OnDestroy();
		delete component;
	}
	/// Clear out the components std::vector
	components.clear();
}

Matrix4 Actor::GetModelMatrix(){
	TransformComponent *tc = GetComponent<TransformComponent>();
	if(tc != nullptr){
		// add parenting code here
		return tc->GetTransformMatrix();
	}
	return Matrix4(); /// else return the identity matrix
}
