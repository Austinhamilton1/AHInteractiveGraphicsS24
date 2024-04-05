#include "Cloth.h"
#include "Generate.h"

Cloth::Cloth(glm::vec3 position, unsigned int rows, unsigned int columns, float width, float height, float density, float dampingFactor) :
	rows(rows), columns(columns), density(density), dampingFactor(dampingFactor)
{
	int numParticles = rows * columns;
	for (int i = 0; i < numParticles; i++) {
		massMatrix.push_back(0.0f);
		forceAccum.push_back({ 0.0f, 0.0f, 0.0f });
	}

	for (int i = 0; i < rows - 1; i++) {
		for (int j = 0; j < columns - 1; j++) {
			int a = i * columns + j;
			int b = a + rows + 1;
			int c1 = a + 1;
			int c2 = b - 1;
			Triangle triangle1 = { a, c1, b };
			Triangle triangle2 = { a, b, c2 };
			triangleMesh.push_back(triangle1);
			triangleMesh.push_back(triangle2);
		}
	}
	
	float halfWidth = width / 2;
	float halfHeight = height / 2;
	float widthStep = width / ((float)rows);
	float heightStep = height / ((float)columns);
	for (float y = position.y - halfHeight; y < position.y + halfHeight; y += heightStep) {
		for (float x = position.x - halfWidth; x < position.x + halfWidth; x += widthStep) {
			glm::vec3 pos = { x, y, 0.0f };
			glm::vec3 vel = { 0.0f, 0.0f, 0.0f };
			positions.push_back(pos);
			velocities.push_back(vel);
		}
	}

	for (int i = 0; i < numParticles; i++) {
		float xPercentage = (positions[i].x - positions[0].x) / width;
		float yPercentage = (positions[i].y - positions[0].y) / height;
		textureMapping.push_back({ xPercentage, yPercentage });
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns - 1; j++) {
			int current = i * columns + j;
			int next = current + 1;
			Spring spring = { STRETCH, 10.0f, glm::distance(positions[current], positions[next]), current, next};
			springs.push_back(spring);
		}
	}

	for (int i = 0; i < rows - 1; i++) {
		for (int j = 0; j < columns; j++) {
			int current = i * columns + j;
			int next = current + rows;
			Spring spring = { STRETCH, 10.0f, glm::distance(positions[current], positions[next]), current, next};
			springs.push_back(spring);
		}
	}
	
	for (int i = 0; i < rows - 1; i++) {
		for (int j = 0; j < columns - 1; j++) {
			int current = i * columns + j;
			int next = current + rows + 1;
			Spring spring = { SHEAR, 10.0f, glm::distance(positions[current], positions[next]), current, next };
			springs.push_back(spring);
		}
	}
	
	for (int i = 1; i < rows; i++) {
		for (int j = 1; j < columns; j++) {
			int current = i * columns + j;
			int next = current - rows - 1;
			Spring spring = { SHEAR, 10.0f, glm::distance(positions[current], positions[next]), current, next };
			springs.push_back(spring);
		}
	}

	for (int i = 0; i < rows - 2; i++) {
		for (int j = 0; j < columns - 2; j++) {
			int current = i * columns + j;
			int next = current + 2;
			Spring spring = { BEND, 10.0f, glm::distance(positions[current], positions[next]), current, next };
			springs.push_back(spring);
		}
	}

	for (int i = 0; i < rows - 2; i++) {
		for (int j = 0; j < columns - 2; j++) {
			int current = i * columns + j;
			int next = current + 2 * rows;
			Spring spring = { BEND, 10.0f, glm::distance(positions[current], positions[next]), current, next };
			springs.push_back(spring);
		}
	}
}

void Cloth::Pin(unsigned int vertex) {
	pins.insert(vertex);
}

void Cloth::Pin(unsigned int row, unsigned int col) {
	pins.insert(row * columns + col);
}

void Cloth::AddForce(glm::vec3 force) {
	for (int i = 0; i < rows * columns; i++) {
		forceAccum[i] += force;
	}
}

void Cloth::ClearAccum() {
	forceAccum.clear();
	for (int i = 0; i < rows * columns; i++) {
		forceAccum.push_back({ 0.0f, 0.0f, 0.0f });
	}
}

void Cloth::ClearMass() {
	for (int i = 0; i < rows * columns; i++) {
		massMatrix[i] = 0.0f;
	}
}

void Cloth::CalculateMass() {
	for (const Triangle& triangle : triangleMesh) {
		float particleArea = (triangle.GetArea(positions) / 3.0f) * density;
		massMatrix[triangle.a] += particleArea;
		massMatrix[triangle.b] += particleArea;
		massMatrix[triangle.c] += particleArea;
	}
}

void Cloth::Update(double elapsedTime) {
	ClearMass();
	CalculateMass();
	float time = static_cast<float>(elapsedTime);
	AddForce({0.0f, -9.7f, 0.0f});
	for (const Spring& spring : springs) {
		float distance = glm::distance(positions[spring.i], positions[spring.j]);
		glm::vec3 force = -spring.k
			* (distance - spring.length)
			* (positions[spring.i] - positions[spring.j])
			/ distance;
		forceAccum[spring.i] += force;
		forceAccum[spring.j] -= force;

		glm::vec3 dampingForce = -dampingFactor * (velocities[spring.i] - velocities[spring.j]);
		forceAccum[spring.i] += dampingForce;
		forceAccum[spring.j] -= dampingForce;
	}
	for (int i = 0; i < rows * columns; i++) {
		if (pins.find(i) == pins.end()) {
			positions[i] += time * velocities[i];
			velocities[i] += time * (massMatrix[i] * forceAccum[i]);
		}
	}
	if (buffer != nullptr) {
		buffer->Clear();
		if (buffer->GetPrimitiveType() == GL_LINES) {
			for (int i = 0; i < rows * columns; i++) {
				buffer->AddVertexData(6, positions[i].x, positions[i].y, positions[i].z, color.r, color.g, color.b);
			}
		}
		else {
			for (int i = 0; i < GetTriangleMeshForRendering().size(); i++) {
				glm::vec3 pos = GetTriangleMeshForRendering()[i];
				glm::vec2 tex = GetTextureMappingForRendering()[i];
				buffer->AddVertexData(8, pos.x, pos.y, pos.z, color.r, color.g, color.b, tex.s, tex.g);
			}
		}
	}
	ClearAccum();
}

void Cloth::SetBendFactor(float factor) {
	for (Spring& spring : springs) {
		if (spring.type == BEND)
			spring.k = factor;
	}
}

void Cloth::SetShearFactor(float factor) {
	for (Spring& spring : springs) {
		if (spring.type == SHEAR)
			spring.k = factor;
	}
}

void Cloth::SetStretchFactor(float factor) {
	for (Spring& spring : springs) {
		if (spring.type == STRETCH)
			spring.k = factor;
	}
}

void Cloth::SetDampingFactor(float factor) {
	dampingFactor = factor;
}

std::vector<glm::vec3> Cloth::GetTriangleMeshForRendering() {
	std::vector<glm::vec3> renderPositions;
	for (const Triangle& triangle : triangleMesh) {
		renderPositions.push_back(positions[triangle.a]);
		renderPositions.push_back(positions[triangle.b]);
		renderPositions.push_back(positions[triangle.c]);
	}
	return renderPositions;
}

std::vector<glm::vec2> Cloth::GetTextureMappingForRendering() {
	std::vector<glm::vec2> textureMappings;
	for (const Triangle& triangle : triangleMesh) {
		textureMappings.push_back(textureMapping[triangle.a]);
		textureMappings.push_back(textureMapping[triangle.b]);
		textureMappings.push_back(textureMapping[triangle.c]);
	}
	return textureMappings;
}
