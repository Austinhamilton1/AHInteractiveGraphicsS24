#include "GeometricPlane.h"

float GeometricPlane::GetIntersectionOffset(Ray ray) {
    float offset = -1.0f;
    float nRayProjection = glm::dot(normal, ray.direction);
    if (nRayProjection == 0) return offset;
    float nStartProjection = glm::dot(normal, ray.startPoint);
    offset = -(nStartProjection + distanceFromOrigin) / nRayProjection;
    return offset;
}
