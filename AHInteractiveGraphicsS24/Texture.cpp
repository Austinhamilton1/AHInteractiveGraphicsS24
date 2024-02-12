#include "Texture.h"

Texture::Texture(unsigned int width, unsigned int height) {
	this->width = width;
	this->height = height;
}

void Texture::SetTextureData(unsigned int count, unsigned char* textureData) {
	this->textureData = new unsigned char[count];
	memcpy(this->textureData, textureData, count);
}

void Texture::CleanUp() {
	if (textureData != nullptr) {
		delete[] textureData;
	}
	textureData = nullptr;
}

void Texture::GenerateTexture() {
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	for (auto& it : parameters) {
		glTexParameteri(GL_TEXTURE_2D, it.first, it.second);
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA8, GL_UNSIGNED_BYTE, textureData);
	glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::SetParameter(GLenum parameterName, GLuint parameterValue) {
	parameters[parameterName] = parameterValue;
}