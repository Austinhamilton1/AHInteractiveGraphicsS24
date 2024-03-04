#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() {
	referenceFrame = glm::mat4(1.0f);
	lookFrame = glm::mat4(1.0f);
	speed = 10.0f;
}

void Camera::SetPosition(const glm::vec3& pos) {
	glm::vec4 position = glm::vec4(pos, 1.0f);
	referenceFrame[3] = position;
}

glm::mat4 Camera::LookForward() {
	glm::vec3 cameraPosition = referenceFrame[3];
	glm::vec3 cameraForward = -lookFrame[2];
	glm::vec3 cameraTarget = cameraPosition + cameraForward;
	glm::vec3 cameraUp = lookFrame[1];
	return glm::lookAt(cameraPosition, cameraTarget, cameraUp);
}

glm::mat4 Camera::LookAt(const glm::vec3& point) {
	glm::vec3 cameraPosition = referenceFrame[3];
	glm::vec3 cameraUp = lookFrame[1];
	return glm::lookAt(cameraPosition, point, cameraUp);
	
}

void Camera::MoveForward(double elapsedTime) {
	glm::vec3 forward = -lookFrame[2];
	glm::vec3 position = referenceFrame[3];
	forward = forward * static_cast<float>(speed * elapsedTime);
	position += forward;
	referenceFrame[3] = glm::vec4(position, 1.0f);
}

void Camera::MoveBackwards(double elapsedTime) {
	glm::vec3 backward = lookFrame[2];
	glm::vec3 position = referenceFrame[3];
	backward = backward * static_cast<float>(speed * elapsedTime);
	position += backward;
	referenceFrame[3] = glm::vec4(position, 1.0f);
}

void Camera::MoveLeft(double elapsedTime) {
	glm::vec3 left = -lookFrame[0];
	glm::vec3 position = referenceFrame[3];
	left = left * static_cast<float>(speed * elapsedTime);
	position += left;
	referenceFrame[3] = glm::vec4(position, 1.0f);
}

void Camera::MoveRight(double elapsedTime) {
	glm::vec3 right = lookFrame[0];
	glm::vec3 position = referenceFrame[3];
	right = right * static_cast<float>(speed * elapsedTime);
	position += right;
	referenceFrame[3] = glm::vec4(position, 1.0f);
}

void Camera::MoveUp(double elapsedTime) {
	glm::vec3 up = referenceFrame[1];
	glm::vec3 position = referenceFrame[3];
	up = up * static_cast<float>(speed * elapsedTime);
	position += up;
	referenceFrame[3] = glm::vec4(position, 1.0f);
}

void Camera::MoveDown(double elapsedTime) {
	glm::vec3 down = -referenceFrame[1];
	glm::vec3 position = referenceFrame[3];
	down = down * static_cast<float>(speed * elapsedTime);
	position += down;
	referenceFrame[3] = glm::vec4(position, 1.0f);
}
