#include "BoundingSphere.h"

bool BoundingSphere::IsIntersecting(BoundingSphere other) {
    float radii = other.GetRadius() + radius;
    float distance = glm::distance(center, other.GetCenter());
    return distance < radii;
}

bool BoundingSphere::IsRayIntersecting(Ray ray) {
	//solve for tc
	glm::vec3 L = center - ray.startPoint;
	float t = glm::dot(L, ray.direction);
	if (t < 0.0f) return false;

	glm::vec3 p = ray.startPoint + ray.direction * t;
	if (glm::distance(p, center) > radius)
		return false;

	return true;
}