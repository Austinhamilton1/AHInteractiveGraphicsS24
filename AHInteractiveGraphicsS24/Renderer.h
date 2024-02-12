#pragma once
#include "BaseObject.h"
#include "Shader.h"
#include "GraphicsObject.h"
#include "Scene.h"
#include <glm/glm.hpp>

class Renderer : public BaseObject {
protected:
	std::shared_ptr<Shader> shader;
	unsigned int vaoId;

public:
	Renderer(std::shared_ptr<Shader> shader);

	inline const std::shared_ptr<Shader>& GetShader() const { return shader; }

	void StaticAllocate(const std::vector<std::shared_ptr<GraphicsObject>>& objects);

	void RenderObject(const GraphicsObject& object);

	void RenderScene(std::shared_ptr<Scene> scene, const glm::mat4& view);
};