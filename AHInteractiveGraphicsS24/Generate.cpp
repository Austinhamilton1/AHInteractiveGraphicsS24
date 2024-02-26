#include "Generate.h"

std::shared_ptr<VertexBuffer> Generate::Cuboid(float width, float height, float depth, glm::vec3 color, glm::vec2 tex)
{
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

std::shared_ptr<VertexBuffer> Generate::XZPlane(float width, float depth, glm::vec3 color, glm::vec2 tex)
{
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
