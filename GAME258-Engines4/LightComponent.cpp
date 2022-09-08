#include "LightComponent.h"


LightComponent::LightComponent(Component* parent_,LightStyle lightStyle_, Vec3 position_,Vec4 color_, float intensity_, Vec3 fallOff_):
		Component(parent_), lightStyle(lightStyle_), position(position_), color(color_), 
		intensity(intensity_), fallOff(fallOff_) {


}

LightComponent::~LightComponent() {}

bool LightComponent::OnCreate() {
	return true;
}
void LightComponent::OnDestroy() {}
void LightComponent::Update(const float deltaTime) {}
void LightComponent::Render() const {}