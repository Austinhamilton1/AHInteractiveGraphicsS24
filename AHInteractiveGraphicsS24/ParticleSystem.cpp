#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(glm::vec3 position, unsigned int rows, unsigned int columns, float width, float height) : rows(rows), columns(columns), numParticles(rows*columns), gravity({0.0f, -9.8f, 0.0f}) {
	for (int i = 0; i < numParticles; i++) {
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
			positions.push_back(pos);
			prevPositions.push_back(pos);
		}
	}

	for (int i = 0; i < triangleMesh.size(); i++) {
		Triangle t = triangleMesh[i];
		Constraint a = { t.a, t.b, glm::distance(positions[t.a], positions[t.b]) };
		Constraint b = { t.a, t.c, glm::distance(positions[t.a], positions[t.c]) };
		Constraint c = { t.b, t.c, glm::distance(positions[t.b], positions[t.c]) };
		constraints.push_back(a);
		constraints.push_back(b);
		constraints.push_back(c);
	}
}

void ParticleSystem::Update(double elapsedTime) {
	AccumulateForces();
	Verlet(elapsedTime);
	SatisfyConstraints(1);
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
				//glm::vec2 tex = GetTextureMappingForRendering()[i];
				buffer->AddVertexData(6, pos.x, pos.y, pos.z, color.r, color.g, color.b);
			}
		}
	}
}

void ParticleSystem::Verlet(double elapsedTime) {
	float timeStep = static_cast<float>(elapsedTime);
	for (int i = 0; i < numParticles; i++) {
		glm::vec3& x = positions[i];
		glm::vec3 tmp = x;
		glm::vec3& oldX = prevPositions[i];
		glm::vec3& a = forceAccum[i];
		x += x - oldX + a * timeStep * timeStep;
		oldX = tmp;
	}
}

void ParticleSystem::SatisfyConstraints(int numIterations) {
	for (int i = 0; i < numIterations; i++) {
		for (int j = 0; j < constraints.size(); j++) {
			Constraint& c = constraints[j];
			glm::vec3& particleA = positions[c.particleA];
			glm::vec3& particleB = positions[c.particleB];
			glm::vec3 delta = particleB - particleA;
			float deltaLength = glm::length(delta);
			float diff = (deltaLength - c.restLength) / deltaLength;
			particleA += delta * 0.5f * diff;
			particleB -= delta * 0.5f * diff;
		}
		positions[positions.size() - 1] = prevPositions[prevPositions.size() - 1];
		positions[positions.size() - rows] = prevPositions[prevPositions.size() - rows];
	}
}

void ParticleSystem::AccumulateForces() {
	for (int i = 0; i < numParticles; i++) {
		forceAccum[i] = gravity;
	}
}

std::vector<glm::vec3> ParticleSystem::GetTriangleMeshForRendering() {
	std::vector<glm::vec3> renderPositions;
	for (const Triangle& triangle : triangleMesh) {
		renderPositions.push_back(positions[triangle.a]);
		renderPositions.push_back(positions[triangle.b]);
		renderPositions.push_back(positions[triangle.c]);
	}
	return renderPositions;
}
