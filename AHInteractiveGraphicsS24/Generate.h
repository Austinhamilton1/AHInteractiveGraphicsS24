#pragma once
#include <memory>
#include <glm/glm.hpp>
#include "VertexBuffer.h"
#include "IndexBuffer.h"

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

	static std::shared_ptr<VertexBuffer> XZLineCircle(
		float radius,
		glm::vec3 color = { 1.0f, 1.0f, 1.0f },
		int steps = 10
	);

	static void LineCircleIndexes(
		std::shared_ptr<IndexBuffer>& bufferToFill,
		int numberOfLineSegments = 36, bool isClosed = true
	);

	static std::shared_ptr<VertexBuffer> LineCylinder(
		float height, float radius,
		glm::vec3 color = { 1.0f, 1.0f, 1.0f },
		int steps = 10
	);

	static void LineCylinderIndexes(
		std::shared_ptr<IndexBuffer>& bufferToFill,
		int numberOfLineSegments = 36
	);

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
};