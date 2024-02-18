#include "Camera.h"
#include <SDL.h>
#include <MMath.h>
	
Camera::Camera() {
	projection = MMath::perspective(45.0f, (16.0f / 9.0f), 0.5f, 100.0f);
	orientation = Quaternion(1.0f, Vec3(0.0f, 0.0f, 0.0f));
	position = Vec3(0.0f, 0.0f, -15.0f);
	view = MMath::toMatrix4(orientation) * MMath::translate(position);

}

void Camera::SetView(const Quaternion& orientation_, const Vec3& position_) {
	orientation = orientation_;
	position = position_;
}

void Camera::OnDestroy() {
	if (skybox) {
		skybox->OnDestroy();
		delete skybox;
	}
}

Camera::~Camera() {}

bool Camera::OnCreate() {
	skybox = new SkyBox("textures/Underwater Box_Posx.png",
						"textures/Underwater Box_Negx.png",
						"textures/Underwater Box_Posy.png",
						"textures/Underwater Box_Negy.png",
						"textures/Underwater Box_Posz.png",
						"textures/Underwater Box_Negz.png");
	
	if (skybox->OnCreate() == false) {
		return false;
	}
	return true;

}

void Camera::HandelEvents(const SDL_Event& sdlEvent) {
	trackball.HandleEvents(sdlEvent);
	orientation = trackball.getQuat();
}

/// Our PASS tutor didn't like the name Render since it can't render itself. 
/// I hope this meets with his approval
void Camera::RenderSkyBox() const{
	if (skybox == nullptr) return;
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glUseProgram(skybox->GetShader()->GetProgram());
	glUniformMatrix4fv(skybox->GetShader()->GetUniformID("projectionMatrix"), 1, GL_FALSE, projection);
	glUniformMatrix4fv(skybox->GetShader()->GetUniformID("viewMatrix"), 1, GL_FALSE, MMath::toMatrix4(orientation));
	/// Here I has turned on the shader and set the matricies. The shader will remain in this state
	/// until I turn off the shader. In Skybox::Render, I will bind the textures, because that is where
	/// they are, then draw the cube.  
	skybox->Render();
	glUseProgram(0);
}
