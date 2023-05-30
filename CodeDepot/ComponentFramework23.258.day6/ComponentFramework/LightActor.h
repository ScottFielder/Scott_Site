#pragma once
#include "Actor.h"
#include "Vector.h"
using namespace MATH;

enum class LightStyle {
	DirectionalLight = 1,
	PointLight,
	SkyLight,
	SpotLight
};

class LightActor : public Actor {
private:
	LightStyle lightStyle;
	Vec3 position;
	Vec4 color;
	float intensity;
	Vec3 fallOff;
public:
	LightActor(Component* parent_, LightStyle lightStyle_, Vec3 location_, Vec4 color_,
		float intensity_ = 1.0f, Vec3 fallOff_ = Vec3(0.0f, 0.0f, 0.0f));


	~LightActor();

	Vec3 GetPosition() const {
		return position;
	}

};