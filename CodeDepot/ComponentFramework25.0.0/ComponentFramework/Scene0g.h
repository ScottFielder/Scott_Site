#ifndef SCENE0_H
#define SCENE0_H
#include "Scene.h"
#include "Vector.h"
#include <Matrix.h>
using namespace MATH;

/// Forward declarations 
union SDL_Event;
class Body;
class Mesh;
class Shader;

class Scene0g : public Scene {
private:
	Body* sphere;
	Shader* shader;
	Mesh* mesh;
	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;
	Matrix4 modelMatrix;
	bool drawInWireMode;

public:
	explicit Scene0g();
	virtual ~Scene0g();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event &sdlEvent) override;
};


#endif // SCENE0_H