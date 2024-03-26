#include "Ray.h"

Ray::Ray(glm::vec3 start, glm::vec3 end) {
	direction = glm::normalize(end - start);
	startPoint = start;
}

glm::vec3 Ray::GetPoint(float offset) const {
	return startPoint + (offset * direction);
}
