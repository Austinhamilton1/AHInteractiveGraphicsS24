#include "GraphicsEnvironment.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Timer.h"
#include "RotateAnimation.h"
#include "GraphicsObject.h"

GraphicsEnvironment* GraphicsEnvironment::self;

GraphicsEnvironment::GraphicsEnvironment() {
	manager = std::make_shared<ObjectManager>();
	camera = Camera();
	self = this;
}

GraphicsEnvironment::~GraphicsEnvironment() {
	glfwTerminate();
}

void GraphicsEnvironment::Init(unsigned int majorVersion, unsigned int minorVersion) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);
}

bool GraphicsEnvironment::SetWindow(unsigned int width, unsigned int height, const std::string& title) {
	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (window == NULL) {
		this->log("Failed to create window.");
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);
	return true;
}

bool GraphicsEnvironment::InitGlad() {
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		this->log("Failed to initialize GLAD.");
		return false;
	}
	return true;
}

void GraphicsEnvironment::SetupGraphics() {
	glViewport(0, 0, 1200, 800); 
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Cull back faces and use counter-clockwise winding of front faces
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	// Enable depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0f, 1.0f);

	glEnable(GL_MULTISAMPLE);

	glfwSetFramebufferSizeCallback(window, GraphicsEnvironment::OnWindowSizeChanged);
	glfwSetCursorPosCallback(window, GraphicsEnvironment::OnMouseMove);
	glfwSetKeyCallback(window, GraphicsEnvironment::KeyCallback);
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 430");
}

void GraphicsEnvironment::OnWindowSizeChanged(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void GraphicsEnvironment::CreateRenderer(const std::string& name, std::shared_ptr<Shader> shader) {
	std::shared_ptr<Renderer> renderer = std::make_shared<Renderer>(shader);
	rendererMap[name] = renderer;
}

void GraphicsEnvironment::StaticAllocate() {
	for (auto& it : rendererMap) {
		std::shared_ptr<Renderer> renderer = it.second;
		renderer->StaticAllocate(renderer->GetScene()->GetObjects());
	}
}

void GraphicsEnvironment::Render() {
	for (auto& it : rendererMap) {
		it.second->RenderScene(camera);
	}
}

void GraphicsEnvironment::ProcessInput(double elapsedSeconds) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
		return;
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera.MoveForward(elapsedSeconds);
		return;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera.MoveBackwards(elapsedSeconds);
		return;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		camera.MoveLeft(elapsedSeconds);
		return;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		camera.MoveRight(elapsedSeconds);
		return;
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		camera.MoveUp(elapsedSeconds);
		return;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		camera.MoveDown(elapsedSeconds);
		return;
	}
}

void GraphicsEnvironment::OnMouseMove(GLFWwindow* window, double mouseX, double mouseY) {
	self->mouse.x = mouseX;
	self->mouse.y = mouseY;

	float xPercent = static_cast<float>(self->mouse.x / self->mouse.windowWidth);
	float yPercent = static_cast<float>(self->mouse.y / self->mouse.windowHeight);

	self->mouse.spherical.theta = 90.0f - (xPercent * 180); // left/right
	self->mouse.spherical.phi = 180.0f - (yPercent * 180); // up/down
}

void GraphicsEnvironment::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_F2 && action == GLFW_PRESS) {
		self->mouse.enabled = !self->mouse.enabled;
		return;
	}
	if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
		self->mouse.enabled = false;
		self->camera.SetPosition(glm::vec3(0, 5, 30));
		glm::mat4 lookFrame(1.0f);
		self->camera.SetLookFrame(lookFrame);
		return;
	}
	if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
		self->mouse.enabled = false;
		self->camera.SetPosition(glm::vec3(30, 5, 0));
		glm::mat4 lookFrame(1.0f);
		lookFrame = glm::rotate(lookFrame, glm::radians(90.0f), glm::vec3(0, 1, 0));
		self->camera.SetLookFrame(lookFrame);
		return;
	}
	if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
		self->mouse.enabled = false;
		self->camera.SetPosition(glm::vec3(0, 5, -30));
		glm::mat4 lookFrame(1.0f);
		lookFrame = glm::rotate(lookFrame, glm::radians(180.0f), glm::vec3(0, 1, 0));
		self->camera.SetLookFrame(lookFrame);
		return;
	}
	if (key == GLFW_KEY_4 && action == GLFW_PRESS) {
		self->mouse.enabled = false;
		self->camera.SetPosition(glm::vec3(-30, 5, 0));
		glm::mat4 lookFrame(1.0f);
		lookFrame = glm::rotate(lookFrame, glm::radians(-90.0f), glm::vec3(0, 1, 0));
		self->camera.SetLookFrame(lookFrame);
		return;
	}
}

const glm::mat4& GraphicsEnvironment::CreateViewMatrix(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& up) {
	glm::vec3 right = glm::cross(direction, up);
	right = glm::normalize(right);

	glm::vec3 vUp = glm::cross(right, direction);
	vUp = glm::normalize(vUp);

	glm::mat4 view(1.0f);
	view[0] = glm::vec4(right, 0.0f);
	view[1] = glm::vec4(up, 0.0f);
	view[2] = glm::vec4(direction, 0.0f);
	view[3] = glm::vec4(position, 1.0f);
	return glm::inverse(view);
}

void GraphicsEnvironment::Run2D() {
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	float aspectRatio = width / (height * 1.0f);

	float left = -100.0f;
	float right = 100.0f;
	float bottom = -100.0f;
	float top = 100.0f;
	left *= aspectRatio;
	right *= aspectRatio;

	glm::vec3 clearColor = { 0.2f, 0.3f, 0.3f };

	float angle = 0, childAngle = 0;
	float cameraX = -10, cameraY = 0;
	glm::mat4 projection;
	glm::mat4 view;

	ImGuiIO& io = ImGui::GetIO();
	while (!glfwWindowShouldClose(window)) {
		GraphicsEnvironment::ProcessInput(0.0);

		glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		if (width >= height) {
			aspectRatio = width / (height * 1.0f);
		}
		else {
			aspectRatio = height / (width * 1.0f);
		}
		projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		GetRenderer("non_textured_scene")->SetProjection(projection);
		GetRenderer("textured_scene")->SetProjection(projection);

		view = GraphicsEnvironment::CreateViewMatrix(
			glm::vec3(cameraX, cameraY, 1.0f),
			glm::vec3(0.0f, 0.0f, -1.0f),
			glm::vec3(0.0f, 1.0f, 0.0f)
		);
		GetRenderer("non_textured_scene")->SetView(view);
		GetRenderer("textured_scene")->SetView(view);

		// Update the objects in the scene
		for (auto& object : GetRenderer("non_textured_scene")->GetScene()->GetObjects()) {
			object->ResetOrientation();
			object->RotateLocalZ(angle);
			for (auto& child : object->GetChildren()) {
				child->ResetOrientation();
				child->RotateLocalZ(childAngle);
			}
		}

		Render();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::Begin("Computing Interactive Graphics");
		ImGui::Text(GetLog().c_str());
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
			1000.0f / io.Framerate, io.Framerate);
		ImGui::ColorEdit3("Background color", (float*)&clearColor.r);
		ImGui::SliderFloat("Angle", &angle, 0, 360);
		ImGui::SliderFloat("Child Angle", &childAngle, 0, 360);
		ImGui::SliderFloat("Camera X", &cameraX, left, right);
		ImGui::SliderFloat("Camera Y", &cameraY, bottom, top);
		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
}

void GraphicsEnvironment::Run3D() {
	float cubeYAngle = 0;
	float cubeXAngle = 0;
	float cubeZAngle = 0;
	float left = -20.0f;
	float right = 20.0f;
	float bottom = -20.0f;
	float top = 20.0f;
	int width, height;

	float aspectRatio;
	float nearPlane = 1.0f;
	float farPlane = 50.0f;
	float fieldOfView = 60;

	float localIntensity = 0.5f;
	float globalIntensity = 0.05f;

	bool gammaCorrection = false;

	float localLightPosition[3] = { 0.0f, 5.0f, 8.0f };

	camera.SetPosition(glm::vec3(0.0f, 5.0f, 20.0f));
	glm::vec3 cameraTarget(0.0f, 0.0f, 0.0f);

	glm::mat4 view;
	glm::mat4 projection;
	glm::mat4 referenceFrame(1.0f);
	glm::vec3 clearColor = { 0.2f, 0.3f, 0.3f };

	ImGuiIO& io = ImGui::GetIO();
	Timer timer;
	double elapsedSeconds;
	while (!glfwWindowShouldClose(window)) {
		elapsedSeconds = timer.GetElapsedTimeInSeconds();
		ProcessInput(elapsedSeconds);
		glfwGetWindowSize(window, &width, &height);
		mouse.windowHeight = height;
		mouse.windowWidth = width;

		glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		if(mouse.enabled)
			camera.SetLookFrame(mouse.spherical.ToMat4());
		view = camera.LookForward();
		GetRenderer("3d_scene")->SetView(view);

		if (width >= height) {
			aspectRatio = width / (height * 1.0f);
		}
		else {
			aspectRatio = height / (width * 1.0f);
		}
		projection = glm::perspective(
			glm::radians(fieldOfView), aspectRatio, nearPlane, farPlane);
		GetRenderer("3d_scene")->SetProjection(projection);

		if (gammaCorrection)
			glEnable(GL_FRAMEBUFFER_SRGB);
		else
			glDisable(GL_FRAMEBUFFER_SRGB);

		manager->Update(elapsedSeconds);
		Render();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::Begin("Computing Interactive Graphics");
		ImGui::Text(GetLog().c_str());
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
			1000.0f / io.Framerate, io.Framerate);
		ImGui::ColorEdit3("Background color", (float*)&clearColor.r);
		ImGui::SliderFloat("Global Light Intensity", &globalIntensity, 0, 1);
		ImGui::SliderFloat("Local Light Intensity", &localIntensity, 0, 1);
		ImGui::Checkbox("Enable Gamma Correction", &gammaCorrection);
		ImGui::DragFloat3("Local Light Position", localLightPosition, 0.5f, -20.0f, 20.0f);
		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
}
