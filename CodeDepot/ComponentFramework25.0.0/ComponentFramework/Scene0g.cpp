#include <glew.h>
#include <iostream>
#include <SDL.h>
#include "Scene0g.h"
#include <MMath.h>
#include "Debug.h"
#include "Mesh.h"
#include "Shader.h"
#include "Body.h"

Scene0g::Scene0g() :sphere{nullptr}, shader{nullptr}, mesh{nullptr},
drawInWireMode{false} {
	Debug::Info("Created Scene0: ", __FILE__, __LINE__);
}

Scene0g::~Scene0g() {
	Debug::Info("Deleted Scene0: ", __FILE__, __LINE__);
}

bool Scene0g::OnCreate() {
	Debug::Info("Loading assets Scene0: ", __FILE__, __LINE__);
	sphere = new Body();
	sphere->OnCreate();
	
	mesh = new Mesh("meshes/Sphere.obj");
	mesh->OnCreate();

	shader = new Shader("shaders/defaultVert.glsl", "shaders/defaultFrag.glsl");
	if (shader->OnCreate() == false) {
		std::cout << "Shader failed ... we have a problem\n";
	}

	projectionMatrix = MMath::perspective(45.0f, (16.0f / 9.0f), 0.5f, 100.0f);
	viewMatrix = MMath::lookAt(Vec3(0.0f, 0.0f, 5.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
	modelMatrix.loadIdentity();
	return true;
}

void Scene0g::OnDestroy() {
	Debug::Info("Deleting assets Scene0: ", __FILE__, __LINE__);
	sphere->OnDestroy();
	delete sphere;

	mesh->OnDestroy();
	delete mesh;

	shader->OnDestroy();
	delete shader;

	
}

void Scene0g::HandleEvents(const SDL_Event &sdlEvent) {
	switch( sdlEvent.type ) {
    case SDL_KEYDOWN:
		switch (sdlEvent.key.keysym.scancode) {
			case SDL_SCANCODE_W:
				drawInWireMode = !drawInWireMode;
				break;
		}
		break;

	case SDL_MOUSEMOTION:          
		break;

	case SDL_MOUSEBUTTONDOWN:              
		break; 

	case SDL_MOUSEBUTTONUP:            
	break;

	default:
		break;
    }
}

void Scene0g::Update(const float deltaTime) {
	
}

void Scene0g::Render() const {
	/// Set the background color then clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(drawInWireMode){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}else{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	glUseProgram(shader->GetProgram());
	glUniformMatrix4fv(shader->GetUniformID("projectionMatrix"), 1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(shader->GetUniformID("viewMatrix"), 1, GL_FALSE, viewMatrix);
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, modelMatrix);
	mesh->Render(GL_TRIANGLES);
	glUseProgram(0);
}



	
