#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <unordered_map>
#include "BaseObject.h"
#include "Renderer.h"
#include "Shader.h"
#include "ObjectManager.h"
#include "Camera.h"
#include "GraphicsStructures.h"
#include "Ray.h"

class GraphicsEnvironment : public BaseObject {
protected:
	GLFWwindow* window;
	std::unordered_map < std::string, std::shared_ptr<Renderer>> rendererMap;
	std::shared_ptr<ObjectManager> manager;
	Camera camera;
	static GraphicsEnvironment* self;
	MouseParams mouse;
	Ray mouseRay;

public:
	GraphicsEnvironment();
	~GraphicsEnvironment();
	inline GLFWwindow* GetWindow() const { return window; }
	inline std::shared_ptr<Renderer> GetRenderer(const std::string& name) { return rendererMap[name]; }
	inline Ray GetMouseRay() const { return mouseRay; }
	
	void AddObject(const std::string& name, std::shared_ptr<GraphicsObject> object) {
		manager->Set(name, object);
	}
	inline std::shared_ptr<ObjectManager> GetManager() { return manager; }
	void Init(unsigned int majorVersion, unsigned int minorVersion);
	bool SetWindow(unsigned int width, unsigned int height, const std::string& title);
	bool InitGlad();
	void SetupGraphics();
	static void OnWindowSizeChanged(GLFWwindow* window, int width, int height);
	void CreateRenderer(const std::string& name, std::shared_ptr<Shader> shader);
	void StaticAllocate();
	void Render();
	void ProcessInput(double elapsedSeconds);
	static void OnMouseMove(GLFWwindow* window, double mouseX, double mouseY);
	Ray GetMouseRay(const glm::mat4& projection, const glm::mat4& view);
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void OnMouseClick(GLFWwindow* window, int button, int action, int mods);
	static const glm::mat4& CreateViewMatrix(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& up);
	void Run2D();
	void Run3D();
};