#pragma once
#include <glew.h>
#include "Component.h"
class MaterialComponent: public Component {
private:
	GLuint textureID;
	const char* filename;
	bool LoadImage(const char* filename);
public:
	MaterialComponent(Component* parent_,const char* filename_);
	virtual ~MaterialComponent();
	
	inline GLuint getTextureID() const { return textureID; }

	virtual bool OnCreate();
	virtual void OnDestroy();
	virtual void Update(const float deltaTime_);
	virtual void Render()const;
};

