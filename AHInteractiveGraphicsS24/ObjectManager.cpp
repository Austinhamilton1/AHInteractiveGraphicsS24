#include "ObjectManager.h"

void ObjectManager::Update(double elapsedSeconds) {
	for (auto& it : objectMap) {
		it.second->Update(elapsedSeconds);
	}
}

void ObjectManager::SetBehaviorDefaults() {
	for (auto& it : objectMap) {
		it.second->SetBehaviorDefaults();
	}
}
