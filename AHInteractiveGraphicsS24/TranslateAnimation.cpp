#include "TranslateAnimation.h"
#include "GraphicsObject.h"

void TranslateAnimation::Update(double elapsedSeconds){
	if (object == nullptr) return;
	if (isMoving) {
		float deltaSpeed = static_cast<float>(speed * elapsedSeconds);
		glm::mat4& referenceFrame = object->GetLocalReferenceFrame();
		glm::vec4 deltaPosition = glm::vec4(deltaSpeed * direction, 0.0f);
		float deltaDistance = glm::length(deltaPosition);
		if (deltaDistance < distanceToMove) {
			referenceFrame[3] += deltaPosition;
			distanceToMove -= deltaDistance;
			distanceMoved += deltaDistance;
		}
		else {
			isMoving = false;
			direction *= -1.0f;
			distanceToMove = distanceMoved;
			distanceMoved = 0.0f;
		}
	}
}
 