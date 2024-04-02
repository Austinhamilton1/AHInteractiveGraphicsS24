#pragma once
#include "BaseObject.h"
#include "GraphicsObject.h"
#include <unordered_map>
#include <memory>

class ObjectManager : public BaseObject {
protected:
	std::unordered_map<std::string, std::shared_ptr<GraphicsObject>> objectMap;

public:
	inline std::shared_ptr<GraphicsObject> Get(const std::string& key) { return objectMap[key]; }
	inline void Set(const std::string& key, std::shared_ptr<GraphicsObject> value) {
		objectMap[key] = value;
	}
	void Update(double elapsedSeconds);
	void SetBehaviorDefaults();
};