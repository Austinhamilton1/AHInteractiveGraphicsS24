#pragma once
#include "IAnimation.h"
#include <glm/glm.hpp>

class TranslateAnimation : public IAnimation {
private:
	glm::vec3 direction;
	float speed;
	bool isMoving;
	float distanceToMove;
	float distanceMoved;

public:
	TranslateAnimation(glm::vec3 direction, float speed, float distanceToMove) : IAnimation(), direction(direction), speed(speed),
		distanceToMove(distanceToMove), distanceMoved(0.0f), isMoving(false) {};
	void Update(double elapsedSeconds);
	void Move() { isMoving = !isMoving; }
};