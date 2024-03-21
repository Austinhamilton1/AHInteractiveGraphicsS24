#pragma once
#include "BaseObject.h"
#include <glm/glm.hpp>

class Camera : public BaseObject {
protected:
	glm::mat4 referenceFrame;
	glm::mat4 lookFrame;
	float speed;

public:
	Camera();
	glm::vec3& GetPosition();
	void SetLookFrame(const glm::mat4& lookFrame) { this->lookFrame = lookFrame; }
	void SetSpeed(float speed) { this->speed = speed; }
	void SetPosition(const glm::vec3& pos);
	glm::mat4 LookForward();
	glm::mat4 LookAt(const glm::vec3& point);
	void MoveForward(double elapsedTime);
	void MoveBackwards(double elapsedTime);
	void MoveLeft(double elapsedTime);
	void MoveRight(double elapsedTime);
	void MoveUp(double elapsedTime);
	void MoveDown(double elapsedTime);
};