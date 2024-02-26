#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <unordered_map>
#include "BaseObject.h"
#include "Renderer.h"
#include "Shader.h"

class GraphicsEnvironment : public BaseObject {
protected:
	GLFWwindow* window;
	std::unordered_map < std::string, std::shared_ptr<Renderer>> rendererMap;

public:
	~GraphicsEnvironment();
	inline GLFWwindow* GetWindow() const { return window; }
	inline std::shared_ptr<Renderer> GetRenderer(const std::string& name) { return rendererMap[name]; }

	void Init(unsigned int majorVersion, unsigned int minorVersion);
	bool SetWindow(unsigned int width, unsigned int height, const std::string& title);
	bool InitGlad();
	void SetupGraphics();
	static void OnWindowSizeChanged(GLFWwindow* window, int width, int height);
	void CreateRenderer(const std::string& name, std::shared_ptr<Shader> shader);
	void StaticAllocate();
	void Render();
	static void ProcessInput(GLFWwindow* window);
	static const glm::mat4& CreateViewMatrix(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& up);
	void Run2D();
	void Run3D();
};