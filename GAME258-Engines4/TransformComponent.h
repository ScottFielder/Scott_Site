#pragma once
#include "Component.h"
#include "Matrix.h"
#include "QMath.h"
#include "Euler.h"
using namespace MATH;
class TransformComponent : public Component {
private:
	Vec3 pos;
	Vec3 scale;
	Quaternion orientation;
 
public:
	TransformComponent(Component* parent_);
	TransformComponent(Component* parent_,Vec3 pos_, Quaternion orientation_, Vec3 scale_ = Vec3(1.0f, 1.0f, 1.0f));
	~TransformComponent();
	bool OnCreate();
	void OnDestroy();
	void Update(const float deltaTime_);
	void Render() const;

	Vec3 GetPosition() { return pos; }
	Vec3 GetScale() { return scale; }
	Quaternion GetQuaternion() { return orientation; }
	Matrix4 GetTransformMatrix() const;
	void SetTransform(Vec3 pos_, Quaternion orientation_, Vec3 scale_ = Vec3(1.0f, 1.0f, 1.0f) ) {
		pos = pos_;
		orientation = orientation_;
		scale = scale_;
	}


};

