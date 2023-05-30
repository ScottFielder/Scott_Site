#include "CameraActor.h"
#include <MMath.h>
#include <QMath.h>
#include "TransformComponent.h"
using namespace MATH;

CameraActor::CameraActor(Component* parent_) :Actor(parent_) {

}

CameraActor::~CameraActor() {
	OnDestroy();
}

bool CameraActor::OnCreate() {
	if (isCreated) return true;
	projectionMatrix = MMath::perspective(45.0f, (16.0f / 9.0f), 0.5f, 100.0f);
	viewMatrix = MMath::lookAt(Vec3(0.0f, 0.0f, 10.0), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
	isCreated = true;
	return true;
}

void CameraActor::OnDestroy() {}

void CameraActor::Update(const float deltaTime) {}

void CameraActor::Render() const {}

void CameraActor::UpdateProjectionMatrix(const float fovy, const float aspectRatio, const float near, const float far) {
	projectionMatrix = MMath::perspective(fovy, aspectRatio, near, far);

}

void CameraActor::UpdateViewMatrix() {
	TransformComponent* transformComponent = GetComponent<TransformComponent>();
	if (transformComponent == nullptr) {
		/// Never liked lookAt()
		viewMatrix = MMath::lookAt(Vec3(0.0f, 0.0f, 5.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
	} else {
		Quaternion quaternion = transformComponent->GetOrientation();
		Vec3 position = transformComponent->GetPosition();
		/// The order of the matrix multilies is from the point-of-view of the camera
		viewMatrix = MMath::toMatrix4(quaternion) * MMath::translate(position);
	}



}