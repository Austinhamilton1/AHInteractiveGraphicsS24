#pragma once
#include "BaseObject.h"

class Texture : public BaseObject {
protected:
	unsigned char* textureData;
	bool isLoadedFromFile;
	unsigned int textureId, type, width, height,
		internalFormat, sourceFormat, wrapS, wrapT,
		magFilter, minFilter;
	int numberOfChannels;


public:
	Texture();
	~Texture();
	inline const unsigned char* GetTextureData() const { return textureData; }
	inline const bool IsLoadedFromFile() const { return isLoadedFromFile; }
	void SetTextureData(unsigned int count, unsigned char* data);
	inline const int GetTextureId() const { return textureId; }
	inline const int GetNumberOfChannels() const { return numberOfChannels; }
	void SetWidth(unsigned int width);
	void SetHeight(unsigned int height);
	void SelectToChange();
	void Deselect();
	void SelectToRender(int textureUnit = 0);
	void Allocate();
	void LoadTextureDataFromFile(const std::string& filePath);
	inline void SetWrapS(unsigned int wrapS) { this->wrapS = wrapS; }
	inline void SetWrapT(unsigned int wrapT) { this->wrapT = wrapT; }
	inline void SetMagFilter(unsigned int magFilter) { this->magFilter = magFilter; }
	inline void SetMinFilter(unsigned int minFilter) { this->minFilter = minFilter; }

private:
	void CleanUp();
};