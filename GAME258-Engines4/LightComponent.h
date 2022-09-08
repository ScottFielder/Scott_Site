#pragma once
#include "Component.h"
#include "Vector.h"
using namespace MATH;

enum class LightStyle :short {
	DirectionalLight = 1,
	PointLight,
	SkyLight,
	SpotLight
};

class LightComponent : public Component {
	/// Unless you know what these do don't allow them
	/// to be created implicitly 
	LightComponent(const LightComponent&) = delete;
	LightComponent(LightComponent&&) = delete;
	LightComponent& operator=(const LightComponent&) = delete;
	LightComponent& operator=(LightComponent&&) = delete;

private:
	LightStyle lightStyle;
	Vec3 position;
	Vec4 color;
	float intensity;
	Vec3 fallOff;
public:
	LightComponent(Component* parent_,LightStyle lightStyle_, Vec3 location_, 
		Vec4 color, float intensity = 1.0f, Vec3 fallOff = Vec3(0.0f, 0.0f, 0.0f));
	~LightComponent();
	bool OnCreate() override;
	void OnDestroy() override;
	void Update(const float deltaTime) override;
	void Render() const override;
	Vec3 GetPosition() { return position; }
	Vec4 GetColor() { return color; }
	float GetIntensity()  { return intensity; }
};

