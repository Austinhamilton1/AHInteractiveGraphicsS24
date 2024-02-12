#pragma once
#include "BaseObject.h"
#include <unordered_map>
#include <glad/glad.h>

class Texture : public BaseObject {
protected:
	unsigned char* textureData = nullptr;
	unsigned int textureId;
	std::unordered_map<GLenum, GLuint> parameters;
	unsigned int width;
	unsigned int height;

public:
	Texture(unsigned int width, unsigned int height);
	void SetTextureData(unsigned int count, unsigned char*);
	void CleanUp();
	void GenerateTexture();
	void SetParameter(GLenum parameterName, GLuint parameterValue);
};