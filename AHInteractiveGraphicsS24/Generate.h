#pragma once
#include <memory>
#include <glm/glm.hpp>
#include "VertexBuffer.h"
#include "Cloth.h"

class Generate {
public:
	static std::shared_ptr<VertexBuffer> Cuboid(
		float width, float height, float depth,
		glm::vec3 color = { 1.0f, 1.0f, 1.0f },
		glm::vec2 tex = { 1.0f, 1.0f }
	);

	static std::shared_ptr<VertexBuffer> XZPlane(
		float width, float depth,
		glm::vec3 color = { 1.0f, 1.0f, 1.0f },
		glm::vec2 tex = { 1.0f, 1.0f }
	);

	static std::shared_ptr<VertexBuffer> XYPlane(
		float width, float height,
		glm::vec3 color = {1.0f, 1.0f, 1.0f},
		glm::vec2 tex = {1.0f, 1.0f});

	static std::shared_ptr<VertexBuffer> NormalCuboid(
		float width, float height, float depth,
		glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f },
		glm::vec2 tex = { 1.0f, 1.0f }
	);

	static std::shared_ptr<VertexBuffer> NormalXZPlane(
		float width, float depth,
		glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f },
		glm::vec2 tex = { 1.0f, 1.0f }
	);

	static std::shared_ptr<VertexBuffer> ClothBuffer(std::shared_ptr<Cloth>);
};