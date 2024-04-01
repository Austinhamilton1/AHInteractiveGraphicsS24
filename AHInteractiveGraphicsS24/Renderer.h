#pragma once
#include "BaseObject.h"
#include "Shader.h"
#include "GraphicsObject.h"
#include "Scene.h"
#include "Camera.h"
#include <glm/glm.hpp>

class Renderer : public BaseObject {
protected:
	std::shared_ptr<Shader> shader;
	unsigned int vaoId;
	std::shared_ptr<Scene> scene;
	glm::mat4 view;
	glm::mat4 projection;

public:
	Renderer(std::shared_ptr<Shader> shader);

	inline const std::shared_ptr<Shader>& GetShader() const { return shader; }
	inline const std::shared_ptr<Scene>& GetScene() const { return scene; }
	inline void SetScene(const std::shared_ptr<Scene>& scene) { this->scene = scene; }
	inline const glm::mat4& GetView() const { return view; }
	inline void SetView(const glm::mat4& view) { this->view = view; }
	inline void SetProjection(const glm::mat4& projection) { this->projection = projection; }

	void Allocate(const std::vector<std::shared_ptr<GraphicsObject>>& objects);

	void RenderObject(GraphicsObject& object);

	void RenderScene(Camera& camera);
};