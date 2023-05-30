#include "TransformComponent.h"
#include "MMath.h"
#include "QMath.h"
using namespace MATH;

TransformComponent::TransformComponent(Component* parent_, Vec3 pos_, Quaternion orientation_, Vec3 scale_): 
	Component(parent_) {

	pos = pos_;
	orientation = orientation_;
	scale = scale_;
}

TransformComponent::~TransformComponent() {
	OnDestroy();
}

bool TransformComponent::OnCreate() { 

	return true;
}

void TransformComponent::OnDestroy() {}

void TransformComponent::Render() const {}

void TransformComponent::Update(const float deltaTime) {}

Matrix4 TransformComponent::GetTransformMatrix() const {
	return MMath::translate(pos) * MMath::scale(scale) * MMath::toMatrix4(orientation);
}


