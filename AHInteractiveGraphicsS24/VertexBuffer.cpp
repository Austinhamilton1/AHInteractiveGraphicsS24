#include "VertexBuffer.h"
#include <cstdarg>


VertexBuffer::VertexBuffer(unsigned int numElementsPerVertex, bool isDynamic)
{
	numberOfElementsPerVertex = numElementsPerVertex;
	numberOfVertices = 0;
	primitiveType = GL_TRIANGLES;
	glGenBuffers(1, &vboId);
	texture = nullptr;
	textureUnit = 0;
	this->isDynamic = isDynamic;
	maxData = 0;
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &vboId);
}

void VertexBuffer::AddVertexData(unsigned int count, ...)
{
	if (count != numberOfElementsPerVertex) {
		throw "Invalid vertex data count!";
	}
	va_list args;
	va_start(args, count);
	while (count > 0) {
		// The default is double, so accept as double and then cast to
		// float.
		vertexData.push_back(static_cast<float>(va_arg(args, double)));
		count--;
	}
	numberOfVertices++;
	va_end(args);
}

void VertexBuffer::StaticAllocate()
{
	unsigned long long bytesToAllocate = vertexData.size() * sizeof(float);
	glBufferData(
		GL_ARRAY_BUFFER, bytesToAllocate, vertexData.data(), GL_STATIC_DRAW);
	if (texture != nullptr)
		texture->Allocate();
}

void VertexBuffer::DynamicAllocate() {
	glBufferData(
		GL_ARRAY_BUFFER, maxData, nullptr, GL_DYNAMIC_DRAW
	);
	if (texture != nullptr)
		texture->Allocate();
}

void VertexBuffer::AddVertexAttribute(
	const std::string& name, unsigned int index,
	unsigned int numberOfElements, unsigned int offsetCount)
{
	unsigned int vertexSizeInBytes = sizeof(float) * numberOfElementsPerVertex;
	unsigned int bytesToNext = vertexSizeInBytes;
	unsigned long long offsetBytes = sizeof(float) * offsetCount;
	VertexAttribute attr = {
		index, numberOfElements, GL_FLOAT, GL_FALSE,
		bytesToNext, (void*)offsetBytes
	};
	attributeMap[name] = attr;
}

void VertexBuffer::SetUpAttributeInterpretration()
{
	for (const std::pair<const std::string, VertexAttribute>& item : attributeMap) {
		const auto& attr = item.second;
		glEnableVertexAttribArray(attr.index);
		glVertexAttribPointer(
			attr.index, attr.numberOfComponents, attr.type,
			attr.isNormalized, attr.bytesToNext, attr.byteOffset
		);
	}
}

void VertexBuffer::Clear() {
	vertexData.clear();
	numberOfVertices = 0;
}
