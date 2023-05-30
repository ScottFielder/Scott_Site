#include <glew.h>
#include <iostream>
#include <SDL.h>
#include "Debug.h"
#include "Scene0.h"
#include "MMath.h"
#include "QMath.h"
#include "Debug.h"
#include "Actor.h"
#include "MeshComponent.h"
#include "ShaderComponent.h"
#include "MaterialComponent.h"
#include "TransformComponent.h"
#include "CameraActor.h"
#include "LightActor.h"


Scene0::Scene0():camera(nullptr),mario(nullptr), light(nullptr)  {
	Debug::Info("Created Scene0: ", __FILE__, __LINE__);
}

Scene0::~Scene0() {
	Debug::Info("Deleted Scene0: ", __FILE__, __LINE__);

}

bool Scene0::OnCreate() {
	Debug::Info("Loading assets Scene0: ", __FILE__, __LINE__);

	camera = new CameraActor(nullptr);
	camera->AddComponent<TransformComponent>(nullptr, Vec3(0.0f, 0.0f, 0.0f), Quaternion());
	camera->OnCreate();

	light = new LightActor(nullptr, LightStyle::DirectionalLight, Vec3(0.0f, 0.0f, 0.0f), Vec4(0.6f, 0.6f, 0.6f, 0.0f));
	light->OnCreate();

	mario = new Actor(nullptr);
	mario->AddComponent<MeshComponent>(nullptr, "meshes/Mario.obj");
	mario->AddComponent<ShaderComponent>(nullptr, "shaders/textureVert.glsl", "shaders/textureFrag.glsl");
	mario->AddComponent<MaterialComponent>(nullptr,"textures/mario_main.png");
	mario->AddComponent<TransformComponent>(nullptr, Vec3(0.0f, 0.0f, 0.0f), Quaternion());
	mario->OnCreate();
	mario->ListComponents();
	return true;
}

void Scene0::OnDestroy() {
	mario->RemoveAllComponents();
	Debug::Info("Deleting assets Scene0: ", __FILE__, __LINE__);
}

void Scene0::HandleEvents(const SDL_Event &sdlEvent) {
	switch( sdlEvent.type ) {
    case SDL_KEYDOWN:
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

void Scene0::Update(const float deltaTime) {
	static float rot = 0.0f;
	rot += deltaTime * 50.0f;
	Vec3 pos = mario->GetComponent<TransformComponent>()->GetPosition();
	mario->GetComponent<TransformComponent>()->SetTransform(pos, QMath::angleAxisRotation(rot, Vec3(0.0f, 1.0f, 0.0f)));
}

void Scene0::Render() const {
	glEnable(GL_DEPTH_TEST);
	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /// Separated these from the OpenGL code below just to make it easier to debug.  
	ShaderComponent* shader = mario->GetComponent<ShaderComponent>();
	MeshComponent* mesh = mario->GetComponent<MeshComponent>();
	MaterialComponent* texture = mario->GetComponent<MaterialComponent>();

	glUseProgram(shader->GetProgram());
	glUniformMatrix4fv(shader->GetUniformID("projectionMatrix"), 1, GL_FALSE, camera->GetProjectionMatrix());
	glUniformMatrix4fv(shader->GetUniformID("viewMatrix"), 1, GL_FALSE, camera->GetViewMatrix());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, mario->GetModelMatrix());
	glUniform3fv(shader->GetUniformID("lightPos"), 1, light->GetPosition());
	glBindTexture(GL_TEXTURE_2D, texture->GetTextureID());
	mesh->Render(GL_TRIANGLES);
	glUseProgram(0);
}



	
