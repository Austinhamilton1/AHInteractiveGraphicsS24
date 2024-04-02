#include "GeometricPlane.h"

void GeometricPlane::Set(glm::vec3 normal, float distanceFromOrigin) {
    this->normal = normal;
    this->distanceFromOrigin = distanceFromOrigin;
}

float GeometricPlane::GetIntersectionOffset(Ray ray) {
    float offset = -1.0f;
    float nRayProjection = glm::dot(normal, ray.direction);
    if (nRayProjection == 0) return offset;
    float nStartProjection = glm::dot(normal, ray.startPoint);
    offset = -(nStartProjection + distanceFromOrigin) / nRayProjection;
    return offset;
}
