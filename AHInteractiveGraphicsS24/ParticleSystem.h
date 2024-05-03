#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "GraphicsObject.h"
#include "GraphicsStructures.h"
#include "BoundingSphere.h"
#include "Ray.h"
#include "GeometricPlane.h"
#include "db_perlin.hpp"

struct Constraint {
	int particleA, particleB;
	float restLength;
};

class ParticleSystem : public GraphicsObject {
private:
	int rows, columns, numParticles;
	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> prevPositions;
	std::vector<glm::vec3> forceAccum;
	glm::vec3 gravity;
	std::vector<Constraint> constraints;
	std::vector<Triangle> triangleMesh;
	glm::vec3 color;
	std::vector<BoundingSphere> boundingSpheres;
	GeometricPlane planeOfMovement;
	std::vector<glm::vec2> textureMapping;
	std::vector<glm::vec3> normals;
	float windSpeed = 15.0f;

public:
	ParticleSystem(glm::vec3 position = { 0.0f, 0.0f, 0.0f }, unsigned int rows = 50, unsigned int columns = 50, float width = 10, float height = 10);
	void Update(double elapsedTime);
	void SetColor(glm::vec3 color) { this->color = color; }
	int Grab(Ray ray);
	void Move(int particle, Ray ray);

protected:
	void Verlet(double elapsedTime);
	void SatisfyConstraints(int numIterations);
	void AccumulateForces();
	glm::vec3 GenerateWind(float x, float y, float z);
	void ResetBuffer();

public:
	std::vector<Vertex> GetVertexData();
	void SetWindSpeed(float speed) { windSpeed = speed; }
};