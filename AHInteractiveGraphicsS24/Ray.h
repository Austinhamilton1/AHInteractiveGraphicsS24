#pragma once
#include <glm/glm.hpp>
#include "BaseObject.h"

class Ray : public BaseObject {
public:
	glm::vec3 startPoint;
	glm::vec3 direction;
	Ray() {};
	Ray(glm::vec3 start, glm::vec3 end);
	glm::vec3 GetPoint(float offset) const;
};