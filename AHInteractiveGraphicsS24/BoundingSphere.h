#pragma once
#include <glm/glm.hpp>
#include "Ray.h"

class BoundingSphere {
	glm::vec3 center;
	float radius;

public:
	BoundingSphere(glm::vec3 center, float radius) : center(center), radius(radius) {};
	glm::vec3 GetCenter() { return center; }
	float GetRadius() { return radius; }
	bool IsIntersecting(BoundingSphere other);
	bool IsRayIntersecting(Ray ray);
};