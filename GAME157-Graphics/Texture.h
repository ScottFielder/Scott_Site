#ifndef TEXTURE_H
#define TEXTURE_H
#include <glew.h>


class Texture {
private:
	GLuint textureID;
public:
	Texture();
	~Texture();
	bool LoadImage(const char* filename);
	inline GLuint getTextureID() const { return textureID; }
	

};
#endif
