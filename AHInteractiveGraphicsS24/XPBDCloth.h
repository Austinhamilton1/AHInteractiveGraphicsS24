#pragma once
#include "GraphicsObject.h"
#include <glm/glm.hpp>

struct Particle {
	float mass;
	float inverseMass;
	glm::vec3 position;
	glm::vec3 previousPosition;
	glm::vec3 velocity;
	glm::vec3 force;
};

struct Constraint {
	std::vector<Particle&> particles;
	void AddParticle(Particle& particle) {
		particles.push_back(particle);
	}
	virtual void Solve(float elapsedTime) = 0;
};

struct DistanceConstraint : Constraint {
	float compliance;
	float restLength;
	Particle& a;
	Particle& b;
	DistanceConstraint(float compliance, float restLength) : compliance(compliance), restLength(restLength),
		a(particles[0]), b(particles[1]) {};
	void Solve(float elapsedTime) {
		float alpha = compliance / elapsedTime / elapsedTime;
		float inverseMass = a.inverseMass + b.inverseMass;
		glm::vec3 grad = a.position - b.position;
		float length = glm::length(grad);
		grad = glm::normalize(grad);
		float c = length - restLength;
		float deltaLambda = -c / (inverseMass + alpha);
		glm::vec3 deltaP_a = deltaLambda * grad * a.inverseMass;
		glm::vec3 deltaP_b = -deltaLambda * grad * b.inverseMass;
		a.position += deltaP_a;
		b.position += deltaP_b;
	}
};

struct IsometricBendingConstraint : Constraint {
	float compliance;
	float distan
};

class XPBDCloth : public GraphicsObject {

};