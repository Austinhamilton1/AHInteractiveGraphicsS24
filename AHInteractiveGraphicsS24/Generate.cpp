#include "Generate.h"

std::shared_ptr<VertexBuffer> Generate::Cuboid(float width, float height, float depth, glm::vec3 color, glm::vec2 tex) {
	std::shared_ptr<VertexBuffer> buffer = std::make_shared<VertexBuffer>(8);

	float halfWidth = width / 2;
	float halfHeight = height / 2;
	float halfDepth = depth / 2;

	//front face
	buffer->AddVertexData(8, -halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, 0.0f, tex[1]);
	buffer->AddVertexData(8, -halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, 0.0f, 0.0f);
	buffer->AddVertexData(8, halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, tex[0], 0.0f);
	buffer->AddVertexData(8, -halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, 0.0f, tex[1]);
	buffer->AddVertexData(8, halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, tex[0], 0.0f);
	buffer->AddVertexData(8, halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, tex[0], tex[1]);

	//right face
	buffer->AddVertexData(8, halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, 0.0f, tex[1]);
	buffer->AddVertexData(8, halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, 0.0f, 0.0f);
	buffer->AddVertexData(8, halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, tex[0], 0.0f);
	buffer->AddVertexData(8, halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, 0.0f, tex[1]);
	buffer->AddVertexData(8, halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, tex[0], 0.0f);
	buffer->AddVertexData(8, halfWidth, halfHeight, -halfDepth, color.r, color.g, color.b, tex[0], tex[1]);

	//back face
	buffer->AddVertexData(8, halfWidth, halfHeight, -halfDepth, color.r, color.g, color.b, 0.0f, tex[1]);
	buffer->AddVertexData(8, halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, 0.0f, 0.0f);
	buffer->AddVertexData(8, -halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, tex[0], 0.0f);
	buffer->AddVertexData(8, halfWidth, halfHeight, -halfDepth, color.r, color.g, color.b, 0.0f, tex[1]);
	buffer->AddVertexData(8, -halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, tex[0], 0.0f);
	buffer->AddVertexData(8, -halfWidth, halfHeight, -halfDepth, color.r, color.g, color.b, tex[0], tex[1]);

	//left face
	buffer->AddVertexData(8, -halfWidth, halfHeight, -halfDepth, color.r, color.g, color.b, 0.0f, tex[1]);
	buffer->AddVertexData(8, -halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, 0.0f, 0.0f);
	buffer->AddVertexData(8, -halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, tex[0], 0.0f);
	buffer->AddVertexData(8, -halfWidth, halfHeight, -halfDepth, color.r, color.g, color.b, 0.0f, tex[1]);
	buffer->AddVertexData(8, -halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, tex[0], 0.0f);
	buffer->AddVertexData(8, -halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, tex[0], tex[1]);

	//top face
	buffer->AddVertexData(8, -halfWidth, halfHeight, -halfDepth, color.r, color.g, color.b, 0.0f, tex[1]);
	buffer->AddVertexData(8, -halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, 0.0f, 0.0f);
	buffer->AddVertexData(8, halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, tex[0], 0.0f);
	buffer->AddVertexData(8, -halfWidth, halfHeight, -halfDepth, color.r, color.g, color.b, 0.0f, tex[1]);
	buffer->AddVertexData(8, halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, tex[0], 0.0f);
	buffer->AddVertexData(8, halfWidth, halfHeight, -halfDepth, color.r, color.g, color.b, tex[0], tex[1]);

	//bottom face
	buffer->AddVertexData(8, halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, 0.0f, tex[1]);
	buffer->AddVertexData(8, halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, 0.0f, 0.0f);
	buffer->AddVertexData(8, -halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, tex[0], 0.0f);
	buffer->AddVertexData(8, halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, 0.0f, tex[1]);
	buffer->AddVertexData(8, -halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, tex[0], 0.0f);
	buffer->AddVertexData(8, -halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, tex[0], tex[1]);

	buffer->AddVertexAttribute("position", 0, 3, 0);
	buffer->AddVertexAttribute("vertexColor", 1, 3, 3);
	buffer->AddVertexAttribute("texCoord", 2, 2, 6);

	return buffer;
}

std::shared_ptr<VertexBuffer> Generate::XZPlane(float width, float depth, glm::vec3 color, glm::vec2 tex) {
	std::shared_ptr<VertexBuffer> buffer = std::make_shared<VertexBuffer>(8);

	float halfWidth = width / 2;
	float halfDepth = depth / 2;

	buffer->AddVertexData(8, -halfWidth, 0.0f, -halfDepth, color.r, color.g, color.b, 0.0f, tex[1]);
	buffer->AddVertexData(8, -halfWidth, 0.0f, halfDepth, color.r, color.g, color.b, 0.0f, 0.0f);
	buffer->AddVertexData(8, halfWidth, 0.0f, halfDepth, color.r, color.g, color.b, tex[0], 0.0f);
	buffer->AddVertexData(8, -halfWidth, 0.0f, -halfDepth, color.r, color.g, color.b, 0.0f, tex[1]);
	buffer->AddVertexData(8, halfWidth, 0.0f, halfDepth, color.r, color.g, color.b, tex[0], 0.0f);
	buffer->AddVertexData(8, halfWidth, 0.0f, -halfDepth, color.r, color.g, color.b, tex[0], tex[1]);
	
	buffer->AddVertexAttribute("position", 0, 3, 0);
	buffer->AddVertexAttribute("vertexColor", 1, 3, 3);
	buffer->AddVertexAttribute("texCoord", 2, 2, 6);

	return buffer;
}

std::shared_ptr<VertexBuffer> Generate::XYPlane(float width, float height, glm::vec3 color, glm::vec2 tex) {
	std::shared_ptr<VertexBuffer> buffer = std::make_shared<VertexBuffer>(8);

	float halfWidth = width / 2;
	float halfHeight = height / 2;

	buffer->AddVertexData(8, -halfWidth, halfHeight, 0.0f, color.r, color.g, color.b, 0.0f, tex[1]);
	buffer->AddVertexData(8, -halfWidth, -halfHeight, 0.0f, color.r, color.g, color.b, 0.0f, 0.0f);
	buffer->AddVertexData(8, halfWidth, -halfHeight, 0.0f, color.r, color.g, color.b, tex[0], 0.0f);
	buffer->AddVertexData(8, -halfWidth, halfHeight, 0.0f, color.r, color.g, color.b, 0.0f, tex[1]);
	buffer->AddVertexData(8, halfWidth, -halfHeight, 0.0f, color.r, color.g, color.b, tex[0], 0.0f);
	buffer->AddVertexData(8, halfWidth, halfHeight, 0.0f, color.r, color.g, color.b, tex[0], tex[1]);

	buffer->AddVertexAttribute("position", 0, 3, 0);
	buffer->AddVertexAttribute("vertexColor", 1, 3, 3);
	buffer->AddVertexAttribute("texCoord", 2, 2, 6);

	return buffer;
}

std::shared_ptr<VertexBuffer> Generate::XZLineCircle(float radius, glm::vec3 color, int steps) {
	std::shared_ptr<VertexBuffer> buffer = std::make_shared<VertexBuffer>(6);

	for (float theta = 0; theta < 360; theta += steps) {
		float radianTheta = glm::radians(theta);
		float x = radius * glm::cos(radianTheta);
		float z = radius * glm::sin(radianTheta);
		buffer->AddVertexData(6, x, 0.0f, z, color.r, color.g, color.b);
	}

	buffer->AddVertexAttribute("position", 0, 3, 0);
	buffer->AddVertexAttribute("vertexColor", 1, 3, 3);

	return buffer;
}

void Generate::LineCircleIndexes(std::shared_ptr<IndexBuffer>& bufferToFill, int numberOfLineSegments, bool isClosed) {
	for (int i = 0; i < numberOfLineSegments - 1; i++) {
		bufferToFill->AddIndexData(2, i, i + 1);
	}
	if (isClosed)
		bufferToFill->AddIndexData(2, numberOfLineSegments - 1, 0);
}

std::shared_ptr<VertexBuffer> Generate::LineCylinder(float height, float radius, glm::vec3 color, int steps) {
	std::shared_ptr<VertexBuffer> buffer = std::make_shared<VertexBuffer>(6);

	float halfHeight = height / 2;

	for (float theta = 0; theta < 360; theta += steps) {
		float radianTheta = glm::radians(theta);
		float x = radius * glm::cos(radianTheta);
		float z = radius * glm::sin(radianTheta);
		buffer->AddVertexData(6, x, halfHeight, z, color.r, color.g, color.b);
	}
	for (float theta = 0; theta < 360; theta += steps) {
		float radianTheta = glm::radians(theta);
		float x = radius * glm::cos(radianTheta);
		float z = radius * glm::sin(radianTheta);
		buffer->AddVertexData(6, x, -halfHeight, z, color.r, color.g, color.b);
	}

	

	buffer->AddVertexAttribute("position", 0, 3, 0);
	buffer->AddVertexAttribute("vertexColor", 1, 3, 3);

	return buffer;
}

void Generate::LineCylinderIndexes(std::shared_ptr<IndexBuffer>& bufferToFill, int numberOfLineSegments) {
	for (int i = 0; i < numberOfLineSegments; i++) {
		int next = (i + 1) % numberOfLineSegments;
		bufferToFill->AddIndexData(2, i, next);
	}
	for (int i = 0; i < numberOfLineSegments; i++) {
		int next = (i + 1) % numberOfLineSegments;
		bufferToFill->AddIndexData(2, i + numberOfLineSegments, next + numberOfLineSegments);
	}
	for (int i = 0; i < numberOfLineSegments; i++) {
		bufferToFill->AddIndexData(2, i, i + numberOfLineSegments);
	}
}

std::shared_ptr<VertexBuffer> Generate::NormalCuboid(float width, float height, float depth, glm::vec4 color, glm::vec2 tex)
{
	std::shared_ptr<VertexBuffer> buffer = std::make_shared<VertexBuffer>(12);

	float halfWidth = width / 2;
	float halfHeight = height / 2;
	float halfDepth = depth / 2;

	//front face
	buffer->AddVertexData(12, -halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, color.a, 0.0f, tex[1], 0.0f, 0.0f, 1.0f);
	buffer->AddVertexData(12, -halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, color.a, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	buffer->AddVertexData(12, halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, color.a, tex[0], 0.0f, 0.0f, 0.0f, 1.0f);
	buffer->AddVertexData(12, -halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, color.a, 0.0f, tex[1], 0.0f, 0.0f, 1.0f);
	buffer->AddVertexData(12, halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, color.a, tex[0], 0.0f, 0.0f, 0.0f, 1.0f);
	buffer->AddVertexData(12, halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, color.a, tex[0], tex[1], 0.0f, 0.0f, 1.0f);

	//right face
	buffer->AddVertexData(12, halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, color.a, 0.0f, tex[1], 1.0f, 0.0f, 0.0f);
	buffer->AddVertexData(12, halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, color.a, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	buffer->AddVertexData(12, halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, color.a, tex[0], 0.0f, 1.0f, 0.0f, 0.0f);
	buffer->AddVertexData(12, halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, color.a, 0.0f, tex[1], 1.0f, 0.0f, 0.0f);
	buffer->AddVertexData(12, halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, color.a, tex[0], 0.0f, 1.0f, 0.0f, 0.0f);
	buffer->AddVertexData(12, halfWidth, halfHeight, -halfDepth, color.r, color.g, color.b, color.a, tex[0], tex[1], 1.0f, 0.0f, 0.0f);

	//back face
	buffer->AddVertexData(12, halfWidth, halfHeight, -halfDepth, color.r, color.g, color.b, color.a, 0.0f, tex[1], 0.0f, 0.0f, -1.0f);
	buffer->AddVertexData(12, halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, color.a, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f);
	buffer->AddVertexData(12, -halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, color.a, tex[0], 0.0f, 0.0f, 0.0f, -1.0f);
	buffer->AddVertexData(12, halfWidth, halfHeight, -halfDepth, color.r, color.g, color.b, color.a, 0.0f, tex[1], 0.0f, 0.0f, -1.0f);
	buffer->AddVertexData(12, -halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, color.a, tex[0], 0.0f, 0.0f, 0.0f, -1.0f);
	buffer->AddVertexData(12, -halfWidth, halfHeight, -halfDepth, color.r, color.g, color.b, color.a, tex[0], tex[1], 0.0f, 0.0f, -1.0f);

	//left face
	buffer->AddVertexData(12, -halfWidth, halfHeight, -halfDepth, color.r, color.g, color.b, color.a, 0.0f, tex[1], -1.0f, 0.0f, 0.0f);
	buffer->AddVertexData(12, -halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, color.a, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	buffer->AddVertexData(12, -halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, color.a, tex[0], 0.0f, -1.0f, 0.0f, 0.0f);
	buffer->AddVertexData(12, -halfWidth, halfHeight, -halfDepth, color.r, color.g, color.b, color.a, 0.0f, tex[1], -1.0f, 0.0f, 0.0f);
	buffer->AddVertexData(12, -halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, color.a, tex[0], 0.0f, -1.0f, 0.0f, 0.0f);
	buffer->AddVertexData(12, -halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, color.a, tex[0], tex[1], -1.0f, 0.0f, 0.0f);

	//top face
	buffer->AddVertexData(12, -halfWidth, halfHeight, -halfDepth, color.r, color.g, color.b, color.a, 0.0f, tex[1], 0.0f, 1.0f, 0.0f);
	buffer->AddVertexData(12, -halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, color.a, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	buffer->AddVertexData(12, halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, color.a, tex[0], 0.0f, 0.0f, 1.0f, 0.0f);
	buffer->AddVertexData(12, -halfWidth, halfHeight, -halfDepth, color.r, color.g, color.b, color.a, 0.0f, tex[1], 0.0f, 1.0f, 0.0f);
	buffer->AddVertexData(12, halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, color.a, tex[0], 0.0f, 0.0f, 1.0f, 0.0f);
	buffer->AddVertexData(12, halfWidth, halfHeight, -halfDepth, color.r, color.g, color.b, color.a, tex[0], tex[1], 0.0f, 1.0f, 0.0f);

	//bottom face
	buffer->AddVertexData(12, halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, color.a, 0.0f, tex[1], 0.0f, -1.0f, 0.0f);
	buffer->AddVertexData(12, halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, color.a, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f);
	buffer->AddVertexData(12, -halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, color.a, tex[0], 0.0f, 0.0f, -1.0f, 0.0f);
	buffer->AddVertexData(12, halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, color.a, 0.0f, tex[1], 0.0f, -1.0f, 0.0f);
	buffer->AddVertexData(12, -halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, color.a, tex[0], 0.0f, 0.0f, -1.0f, 0.0f);
	buffer->AddVertexData(12, -halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, color.a, tex[0], tex[1], 0.0f, -1.0f, 0.0f);

	buffer->AddVertexAttribute("position", 0, 3, 0);
	buffer->AddVertexAttribute("vertexColor", 1, 4, 3);
	buffer->AddVertexAttribute("texCoord", 2, 2, 7);
	buffer->AddVertexAttribute("normal", 3, 3, 9);

	return buffer;
}

std::shared_ptr<VertexBuffer> Generate::NormalXZPlane(float width, float depth, glm::vec4 color, glm::vec2 tex) {
	std::shared_ptr<VertexBuffer> buffer = std::make_shared<VertexBuffer>(12);

	float halfWidth = width / 2;
	float halfDepth = depth / 2;

	buffer->AddVertexData(12, -halfWidth, 0.0f, -halfDepth, color.r, color.g, color.b, color.a, 0.0f, tex[1], 0.0f, 1.0f, 0.0f);
	buffer->AddVertexData(12, -halfWidth, 0.0f, halfDepth, color.r, color.g, color.b, color.a, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	buffer->AddVertexData(12, halfWidth, 0.0f, halfDepth, color.r, color.g, color.b, color.a, tex[0], 0.0f, 0.0f, 1.0f, 0.0f);
	buffer->AddVertexData(12, -halfWidth, 0.0f, -halfDepth, color.r, color.g, color.b, color.a, 0.0f, tex[1], 0.0f, 1.0f, 0.0f);
	buffer->AddVertexData(12, halfWidth, 0.0f, halfDepth, color.r, color.g, color.b, color.a, tex[0], 0.0f, 0.0f, 1.0f, 0.0f);
	buffer->AddVertexData(12, halfWidth, 0.0f, -halfDepth, color.r, color.g, color.b, color.a, tex[0], tex[1], 0.0f, 1.0f, 0.0f);

	buffer->AddVertexAttribute("position", 0, 3, 0);
	buffer->AddVertexAttribute("vertexColor", 1, 4, 3);
	buffer->AddVertexAttribute("texCoord", 2, 2, 7);
	buffer->AddVertexAttribute("normal", 3, 3, 9);

	return buffer;
}
