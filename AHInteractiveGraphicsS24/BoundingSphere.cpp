#include "BoundingSphere.h"

bool BoundingSphere::IsIntersecting(BoundingSphere other) {
    float radii = other.GetRadius() + radius;
    float distance = glm::distance(center, other.GetCenter());
    return distance < radii;
}

bool BoundingSphere::IsRayIntersecting(Ray ray) {
	//solve for tc
	glm::vec3 L = center - ray.startPoint;
	float tc = glm::dot(L, ray.direction);
	if (tc < 0.0) return false;

	float length = glm::length(L);
	float d = (tc * tc) - (length * length);
	if (d > radius * radius) return false;

	return true;
}
