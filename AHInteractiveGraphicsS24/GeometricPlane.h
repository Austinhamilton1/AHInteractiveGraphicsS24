#pragma once
#include <glm/glm.hpp>
#include "BaseObject.h"
#include "Ray.h"

class GeometricPlane : public BaseObject {
protected:
	glm::vec3 normal;
	float distanceFromOrigin;

public:
	GeometricPlane() {};
	void Set(glm::vec3 normal, float distanceFromOrigin);
	float GetIntersectionOffset(Ray ray);
};