#pragma once
#include <glew.h>
#include "Component.h"
class MaterialComponent: public Component {
private:
	const char* filename;
	GLuint textureID;
public:
	MaterialComponent(Component* parent_, const char* filename_);
	virtual ~MaterialComponent();
	virtual bool OnCreate();
	virtual void OnDestroy();
	virtual void Update(const float deltaTime_);
	virtual void Render()const;

	GLuint GetTextureID() const { return textureID; }
};

