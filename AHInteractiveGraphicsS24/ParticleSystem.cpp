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
			Triangle triangle2 = { a, b, c1 };
			Triangle triangle3 = { a, b, c2 };
			Triangle triangle4 = { a, c2, b };
			triangleMesh.push_back(triangle1);
			triangleMesh.push_back(triangle2);
			triangleMesh.push_back(triangle3);
			triangleMesh.push_back(triangle4);
			for (int k = 0; k < 12; k++) {
				normals.push_back({ 0.0f, 0.0f, 1.0f });
			}
		}
	}

	float halfWidth = width / 2;
	float halfHeight = height / 2;
	float widthStep = width / ((float)rows);
	float heightStep = height / ((float)columns);
	float boundingSphereRadius = glm::max(widthStep, heightStep);
	float startX = position.x - halfWidth;
	float stopX = position.x + halfWidth;
	float startY = position.y - halfHeight;
	float stopY = position.y + halfHeight;
	for (float y = startY; y < stopY; y += heightStep) {
		for (float x = startX; x < stopX; x += widthStep) {
			glm::vec3 pos = { x, y, 0.0f };
			positions.push_back(pos);
			prevPositions.push_back(pos);
			boundingSpheres.push_back(BoundingSphere(pos, boundingSphereRadius));
			float xPercent = (x - startX) / width;
			float yPercent = (x - startY) / height;
			textureMapping.push_back({ xPercent, yPercent });
		}
	}

	for (int i = 0; i < triangleMesh.size(); i += 2) {
		Triangle t = triangleMesh[i];
		Constraint a = { t.a, t.b, glm::distance(positions[t.a], positions[t.b]) };
		Constraint b = { t.a, t.c, glm::distance(positions[t.a], positions[t.c]) };
		Constraint c = { t.b, t.c, glm::distance(positions[t.b], positions[t.c]) };
		constraints.push_back(a);
		constraints.push_back(b);
		constraints.push_back(c);
	}

	planeOfMovement.Set({0.0f, 0.0f, -1.0f}, 0.0f);
}

void ParticleSystem::Update(double elapsedTime) {
	AccumulateForces();
	Verlet(elapsedTime);
	SatisfyConstraints(3);
	ResetBuffer();
}

int ParticleSystem::Grab(Ray ray) {
	for (int i = 0; i < boundingSpheres.size(); i++) {
		if (boundingSpheres[i].IsRayIntersecting(ray))
			return i;
	}
	return -1;
}

void ParticleSystem::Move(int particle, Ray ray) {
	float offset = planeOfMovement.GetIntersectionOffset(ray);
	glm::vec3 position = ray.startPoint + offset * ray.direction;
	positions[particle] = position;
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
		for (int i = 0; i < positions.size(); i++) {
			glm::vec3& particle = positions[i];
			particle.x = glm::min(glm::max(particle.x, -6.0f), 6.0f);
			particle.y = glm::max(particle.y, -2.0f);
		}
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
		glm::vec3 position = positions[i];
		glm::vec3 wind = GenerateWind(position.x, position.y, position.z);
		forceAccum[i] += 15.0f * wind;
	}
}

glm::vec3 ParticleSystem::GenerateWind(float x, float y, float z) {
	float epsilon = 0.0001f;
	float n1 = db::perlin(x + epsilon, y, z);
	float n2 = db::perlin(x - epsilon, y, z);
	float dx = (n1 - n2) / (2 * epsilon);


	n1 = db::perlin(x, y + epsilon, z);
	n2 = db::perlin(x, y - epsilon, z);
	float dy = (n1 - n2) / (2 * epsilon);


	n1 = db::perlin(x, y, z + epsilon);
	n2 = db::perlin(x, y, z - epsilon);
	float dz = (n1 - n2) / (2 * epsilon);

	return glm::vec3(dz, dy, -dx);
}

void ParticleSystem::ResetBuffer() {
	if (buffer != nullptr) {
		buffer->Clear();
		if (buffer->GetPrimitiveType() == GL_LINES) {
			for (int i = 0; i < rows * columns; i++) {
				buffer->AddVertexData(6, positions[i].x, positions[i].y, positions[i].z, color.r, color.g, color.b);
			}
		}
		else {
			std::vector<Vertex> vertices = GetVertexData();
			for (int i = 0; i < vertices.size(); i++) {
				Vertex v = GetVertexData()[i];
				buffer->AddVertexData(11, v.pos.x, v.pos.y, v.pos.z, color.r, color.g, color.b, v.tex.s, v.tex.g, v.normal.x, v.normal.y, v.normal.z);
			}
		}
	}
}

std::vector<Vertex> ParticleSystem::GetVertexData() {
	std::vector<Vertex> vertices;
	int i = 0;
	for (const Triangle& triangle : triangleMesh) {
		vertices.push_back({ positions[triangle.a], textureMapping[triangle.a], normals[i] });
		vertices.push_back({ positions[triangle.b], textureMapping[triangle.b], normals[i + 1] });
		vertices.push_back({ positions[triangle.c], textureMapping[triangle.c], normals[i + 2] });
		i += 3;
	}
	return vertices;
}
