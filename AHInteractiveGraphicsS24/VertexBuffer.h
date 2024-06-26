#pragma once
#include <glad/glad.h> 
#include <vector>
#include <unordered_map>
#include <string>
#include <memory>
#include "Texture.h"

struct VertexAttribute {
	unsigned int index;
	unsigned int numberOfComponents;
	int type;
	int isNormalized;
	unsigned int bytesToNext;
	void* byteOffset;
};

class VertexBuffer
{
protected:
	unsigned int numberOfElementsPerVertex;
	unsigned int numberOfVertices;
	unsigned int vboId;
	int primitiveType;
	std::vector<float> vertexData;
	std::unordered_map<std::string, VertexAttribute> attributeMap;
	int textureUnit;
	std::shared_ptr<Texture> texture;
	bool isDynamic;
	unsigned long long maxData;

public:
	VertexBuffer(unsigned int numElementsPerVertex = 3, bool isDynamic = false);
	~VertexBuffer();

	inline void Select() { glBindBuffer(GL_ARRAY_BUFFER, vboId); }
	inline void Deselect() { glBindBuffer(GL_ARRAY_BUFFER, 0); }
	inline unsigned int GetNumberOfVertices() const { return numberOfVertices; }
	inline int GetPrimitiveType() const { return primitiveType; }
	inline void SetPrimitiveType(int primitiveType) { this->primitiveType = primitiveType; }
	inline const int GetTextureUnit() const { return textureUnit; }
	inline void SetTextureUnit(int textureUnit) { this->textureUnit = textureUnit; }
	inline const std::shared_ptr<Texture> GetTexture() const { return texture; }
	inline void SetTexture(std::shared_ptr<Texture> texture) { this->texture = texture; }
	inline bool HasTexture() { return texture != nullptr; }
	inline void SelectTexture() { texture->SelectToRender(textureUnit); }
	inline bool IsDynamic() { return isDynamic; }
	inline unsigned long long GetMaxData() { return maxData; }
	inline void SetMaxData(unsigned long long maxData) { this->maxData = maxData; }
	inline std::vector<float>& GetData() { return vertexData; }

	// Variadic function
	void AddVertexData(unsigned int count, ...);
	void StaticAllocate();
	void DynamicAllocate();
	void AddVertexAttribute(
		const std::string& name, unsigned int index,
		unsigned int numberOfElements, unsigned int offsetCount = 0);
	void SetUpAttributeInterpretration();
	void Clear();
};

