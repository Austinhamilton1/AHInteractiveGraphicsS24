#include "HighLightBehavior.h"
#include "GraphicsObject.h"

void HighLightBehavior::StoreDefaults() {
	if (object == nullptr) return;
	ambientIntensity = this->object->GetMaterial().ambientIntensity;
}

void HighLightBehavior::SetParameter(IParams& param) {
	this->params = reinterpret_cast<HighlightParams&>(params);
}

void HighLightBehavior::Update(double elapsedSeconds) {
	if (object == nullptr) return;
	if (object->IsIntersectingWithRay(*params.ray))
		object->GetMaterial().ambientIntensity = 1.0f;
	else
		object->GetMaterial().ambientIntensity = ambientIntensity;
}
