#pragma once
#include <glm/glm.hpp>
#include "BaseObject.h"
#include "Ray.h"

class GeometricPlane : public BaseObject {
protected:
	glm::vec3 normal;
	float distanceFromOrigin;

public:
	GeometricPlane(glm::vec3 normal, float distanceFromOrigin) : normal(normal), distanceFromOrigin(distanceFromOrigin) {};
	float GetIntersectionOffset(Ray ray);
};