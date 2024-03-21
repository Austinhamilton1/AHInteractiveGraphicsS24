#include "Scene.h"

Scene::Scene() : globalLight({ glm::vec3(100.0f, 100.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.05f }),
localLight({glm::vec3(0.0f, 5.0f, 8.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.5f, 0.0f}) {}

void Scene::AddObject(std::shared_ptr<GraphicsObject> object)
{
	objects.push_back(object);
}
