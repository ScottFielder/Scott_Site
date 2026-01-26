#include "CameraActor.h"
#include "TransformComponent.h"

CameraActor::CameraActor(Actor* parent_, float fovy, float aspectRatio, float near, float far):
	Actor(parent_){

	projectionMatrix = MMath::perspective(fovy, aspectRatio, near, far);
	viewMatrix.loadIdentity();
}
 
CameraActor::~CameraActor(){}

bool CameraActor::OnCreate(){
	TransformComponent *tc = GetComponent<TransformComponent>();
	if(tc != nullptr){
		viewMatrix = tc->GetTransformMatrix();
		viewMatrix.print("view matrix");
	}
	return true;
}