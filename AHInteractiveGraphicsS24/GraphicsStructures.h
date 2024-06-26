#pragma once
#include <glm/glm.hpp>
#include "Ray.h"

struct SphericalCoordinate {
    float phi = 0.0f, theta = 0.0f, rho = 1.0f;

    glm::mat4 ToMat4() {
        float thetaRadians = glm::radians(theta);
        float phiRadians = glm::radians(phi);
        float sinPhi = sin(phiRadians);
        glm::vec3 zAxis{};
        zAxis.x = rho * sin(thetaRadians) * sinPhi;
        zAxis.y = rho * cos(phiRadians);
        zAxis.z = rho * cos(thetaRadians) * sinPhi;

        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 xAxis = glm::normalize(glm::cross(up, zAxis));
        glm::vec3 yAxis = glm::cross(zAxis, xAxis);
        glm::mat4 orientation(1.0f);
        orientation[0] = glm::vec4(xAxis, 0.0f);
        orientation[1] = glm::vec4(yAxis, 0.0f);
        orientation[2] = glm::vec4(zAxis, 0.0f);
        return orientation;
    }
};

struct MouseParams {
    SphericalCoordinate spherical{};
    double x = 0, y = 0;
    double windowX = 0, windowY = 0;
    int windowWidth = 0, windowHeight = 0;
    float fieldOfView = 60.0f;
    bool enabled = false;
    float normalX = 0, normalY = 0;
};

struct Material {
    float ambientIntensity;  // 0 to 1
    float specularIntensity; // 0 to 1
    float shininess;         // 0 to infinity
};

struct Light {
    glm::vec3 position;
    glm::vec3 color;
    float intensity;
    float attenuationCoef;
};

struct Triangle {
    unsigned int a;
    unsigned int b;
    unsigned int c;
    float GetArea(std::vector<glm::vec3>& positions) const {
        glm::vec3 A = positions[a];
        glm::vec3 B = positions[b];
        glm::vec3 C = positions[c];
        return 0.5f * glm::length(glm::cross(B - A, C - A));
    };
};

struct Vertex {
    glm::vec3 pos;
    glm::vec2 tex;
    glm::vec3 normal;
};