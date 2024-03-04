#include "ObjectManager.h"

void ObjectManager::Update(double elapsedSeconds) {
	for (auto& it : objectMap) {
		it.second->Update(elapsedSeconds);
	}
}