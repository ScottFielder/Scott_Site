#pragma once
/// The camera still doesn't exist mathamatically but there is utility in placeing the
/// view and projections matricies in class. Might as well call it a camera.
#include <Vector.h>
#include <Matrix.h>
#include <Quaternion.h>
#include "SkyBox.h"
#include "Trackball.h"
using namespace MATH;

union SDL_Event;

class Camera {
private:
	Quaternion orientation;
	Vec3 position;
	Matrix4 projection;
	Matrix4 view;
	Trackball trackball;
	SkyBox* skybox;

public:
	Camera();
	~Camera();
	bool OnCreate();
	void OnDestroy();
	void RenderSkyBox() const;
	void HandelEvents(const SDL_Event& sdlEvent);
	
	/// Some getters and setters
	Matrix4 GetViewMatrix() const {
		return  MMath::toMatrix4(orientation) * MMath::translate(position);
	}

	Matrix4 GetProjectionMatrix() const {
		return projection;
	}

	Quaternion GetOrientation() const { return orientation; }

	void SetView(const Quaternion& orientation_, const Vec3& position_);
};

