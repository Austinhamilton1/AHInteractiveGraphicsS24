#pragma once
#include "IBehavior.h"
#include "GraphicsStructures.h"

class HighLightBehavior : public IBehavior {
protected:
	HighlightParams params;
	float ambientIntensity = 0.0f;

public:
	void StoreDefaults() override;
	void SetParameter(IParams& param) override;
	void Update(double elapsedSeconds) override;
};