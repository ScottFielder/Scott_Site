#pragma once
#include "Component.h"
#include <Matrix.h>
#include <Quaternion.h>
using namespace MATH;

class TransformComponent : public Component {
private:
	Vec3 pos;
	Vec3 scale;
	Quaternion orientation;

public:
	TransformComponent(Component* parent_, Vec3 pos_, Quaternion orientation_, Vec3 scale_ = Vec3(1.0f, 1.0f, 1.0f));
	~TransformComponent();
	bool OnCreate();
	void OnDestroy();
	void Update(const float deltaTime);
	void Render() const;

	Vec3 GetPosition() { return pos; }
	Vec3 GetScale() { return scale; }
	Quaternion GetOrientation() { return orientation; }
	void SetTransform(Vec3 pos_, Quaternion orientation_, Vec3 scale_ = Vec3(1.0f, 1.0f, 1.0f)) {
		pos = pos_;
		orientation = orientation_;
		scale = scale_;
	}
	void SetOrientation(Quaternion orientation_) { orientation = orientation_; }
	void SetPosition(Vec3 pos_) { pos = pos_; }
	Matrix4 GetTransformMatrix() const;
};

