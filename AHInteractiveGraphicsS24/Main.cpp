#include <Windows.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "VertexBuffer.h"
#include "GraphicsObject.h"
#include "Scene.h"
#include "Shader.h"
#include "Renderer.h"
#include "TextFile.h"
#include "GraphicsEnvironment.h"
#include "Generate.h"

static void SetUpScene(std::shared_ptr<Shader>& shader, std::shared_ptr<Scene>& scene) {
	TextFile vertSource("basic.vert.glsl");
	TextFile fragSource("basic.frag.glsl");
	if (!vertSource.ReadIn() || !fragSource.ReadIn()) return;

	shader = std::make_shared<Shader>(vertSource.GetData(), fragSource.GetData());
	shader->AddUniform("projection");
	shader->AddUniform("world");
	shader->AddUniform("view");
	
	scene = std::make_shared<Scene>();

	std::shared_ptr<GraphicsObject> square = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> buffer = std::make_shared<VertexBuffer>(6);
	buffer->AddVertexData(6, -5.0f, 5.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	buffer->AddVertexData(6, -5.0f, -5.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	buffer->AddVertexData(6, 5.0f, -5.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	buffer->AddVertexData(6, -5.0f, 5.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	buffer->AddVertexData(6, 5.0f, -5.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	buffer->AddVertexData(6, 5.0f, 5.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	buffer->AddVertexAttribute("position", 0, 3);
	buffer->AddVertexAttribute("color", 1, 3, 3);
	square->SetVertexBuffer(buffer);
	scene->AddObject(square);

	std::shared_ptr<GraphicsObject> triangle = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> buffer2 = std::make_shared<VertexBuffer>(6);
	buffer2->AddVertexData(6, -5.0f, 5.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	buffer2->AddVertexData(6, -5.0f, -5.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	buffer2->AddVertexData(6, 5.0f, -5.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	buffer2->AddVertexAttribute("position", 0, 3);
	buffer2->AddVertexAttribute("color", 1, 3, 3);
	triangle->SetVertexBuffer(buffer2);
	triangle->SetPosition(glm::vec3(30.0f, 0.0f, 0.0f));
	scene->AddObject(triangle);

	std::shared_ptr<GraphicsObject> line = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> buffer3 = std::make_shared<VertexBuffer>(6);
	buffer3->SetPrimitiveType(GL_LINES);
	buffer3->AddVertexData(6, 0.0f, 2.5f, 0.0f, 0.0f, 1.0f, 0.0f);
	buffer3->AddVertexData(6, 0.0f, -2.5f, 0.0f, 0.0f, 1.0f, 0.0f);
	buffer3->AddVertexAttribute("position", 0, 3);
	buffer3->AddVertexAttribute("color", 1, 3, 3);
	line->SetVertexBuffer(buffer3);
	line->SetPosition(glm::vec3(5.0f, -10.0f, 0.0f));
	triangle->AddChild(line);
}

static void SetUpTexturedScene(std::shared_ptr<Shader>& textureShader, std::shared_ptr<Scene>& textureScene) {
	TextFile vertSource("texture.vert.glsl");
	TextFile fragSource("texture.frag.glsl");
	if (!vertSource.ReadIn() || !fragSource.ReadIn()) return;
	textureShader = std::make_shared<Shader>(vertSource.GetData(), fragSource.GetData());
	textureShader->AddUniform("projection");
	textureShader->AddUniform("world");
	textureShader->AddUniform("view");
	textureShader->AddUniform("texUnit");
	std::shared_ptr<Texture> tex = std::make_shared<Texture>();
	tex->SetWidth(4);
	tex->SetHeight(4);
	//tex->SetWrapS(GL_CLAMP_TO_EDGE); tex->SetWrapT(GL_CLAMP_TO_EDGE);
	tex->SetMagFilter(GL_LINEAR);
	unsigned char data[64] = {
		255, 255, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255, 255, 255, 255, 255,
		0, 255, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 255, 0, 255,
		0, 255, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 255, 0, 255,
		255, 255, 255, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255, 255, 255, 255
	};
	tex->SetTextureData(64, data);
	textureScene = std::make_shared<Scene>();
	std::shared_ptr<GraphicsObject> object = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> buffer = std::make_shared<VertexBuffer>(8);
	buffer->AddVertexData(8, -50.0f, 50.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 3.0f);
	buffer->AddVertexData(8, -50.0f, -50.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f);
	buffer->AddVertexData(8, 50.0f, -50.0f, 0.0f, 1.0f, 1.0f, 1.0f, 3.0f, 0.0f);
	buffer->AddVertexData(8, -50.0f, 50.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 3.0f);
	buffer->AddVertexData(8, 50.0f, -50.0f, 0.0f, 1.0f, 1.0f, 1.0f, 3.0f, 0.0f);
	buffer->AddVertexData(8, 50.0f, 50.0f, 0.0f, 1.0f, 1.0f, 1.0f, 3.0f, 3.0f);
	buffer->AddVertexAttribute("position", 0, 3, 0);
	buffer->AddVertexAttribute("vertexColor", 1, 3, 3);
	buffer->AddVertexAttribute("texCoord", 2, 2, 6);
	buffer->SetTexture(tex);
	buffer->SelectTexture();
	object->SetVertexBuffer(buffer);
	object->SetPosition(glm::vec3(-75.0f, -30.0f, 0.0f));
	textureScene->AddObject(object);

	std::shared_ptr<Texture> tex2 = std::make_shared<Texture>();
	tex2->LoadTextureDataFromFile("Planets/planet00.png");
	std::shared_ptr<GraphicsObject> object2 = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> buffer2 = std::make_shared<VertexBuffer>(8);
	buffer2->AddVertexData(8, -50.0f, 50.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f);
	buffer2->AddVertexData(8, -50.0f, -50.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f);
	buffer2->AddVertexData(8, 50.0f, -50.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);
	buffer2->AddVertexData(8, -50.0f, 50.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f);
	buffer2->AddVertexData(8, 50.0f, -50.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);
	buffer2->AddVertexData(8, 50.0f, 50.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	buffer2->AddVertexAttribute("position", 0, 3, 0);
	buffer2->AddVertexAttribute("vertexColor", 1, 3, 3);
	buffer2->AddVertexAttribute("texCoord", 2, 2, 6);
	buffer2->SetTexture(tex2);
	buffer2->SelectTexture();
	object2->SetVertexBuffer(buffer2);
	object2->SetPosition(glm::vec3(50, 50, 0));
	textureScene->AddObject(object2);
}

static void SetUp3DScene1(std::shared_ptr<Shader>& shader, std::shared_ptr<Scene>& scene) {
	TextFile vertSource("texture.vert.glsl");
	TextFile fragSource("texture.frag.glsl");
	if (!vertSource.ReadIn() || !fragSource.ReadIn()) return;
	shader = std::make_shared<Shader>(vertSource.GetData(), fragSource.GetData());
	shader->AddUniform("projection");
	shader->AddUniform("world");
	shader->AddUniform("view");
	shader->AddUniform("texUnit");
	std::shared_ptr<Texture> tex = std::make_shared<Texture>();
	tex->SetWidth(4);
	tex->SetHeight(4);
	//tex->SetWrapS(GL_CLAMP_TO_EDGE); tex->SetWrapT(GL_CLAMP_TO_EDGE);
	//tex->SetMagFilter(GL_LINEAR);
	// Create the texture data
	unsigned char textureData[64] = {
		0, 0, 0, 255, 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 0, 255,
		0, 255, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 255, 0, 255,
		0, 255, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 255, 0, 255,
		0, 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 255, 0, 0, 0, 255
	};
	tex->SetTextureData(64, textureData);
	scene = std::make_shared<Scene>();
	std::shared_ptr<GraphicsObject> object = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> buffer = Generate::Cuboid(10.0f, 5.0f, 5.0f);

	
	buffer->SetTexture(tex);
	buffer->SelectTexture();
	object->SetVertexBuffer(buffer);
	object->SetPosition(glm::vec3(5, 5, 0));
	scene->AddObject(object);

	std::shared_ptr<Texture> crateTexture = std::make_shared<Texture>();
	crateTexture->LoadTextureDataFromFile("Crates/crate_texture.png");
	std::shared_ptr<GraphicsObject> crate = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> buffer2 = Generate::Cuboid(10.0f, 5.0f, 5.0f);
	
	buffer2->SetTexture(crateTexture);
	buffer->SelectTexture();
	crate->SetVertexBuffer(buffer2);
	crate->SetPosition(glm::vec3(-10, 5, 0));
	scene->AddObject(crate);

	std::shared_ptr<Texture> floorTexture = std::make_shared<Texture>();
	floorTexture->LoadTextureDataFromFile("Floors/floor.png");
	std::shared_ptr<GraphicsObject> floor = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> buffer3 = Generate::XZPlane(20, 20);

	buffer3->SetTexture(floorTexture);
	buffer3->SelectTexture();
	floor->SetVertexBuffer(buffer3);
	floor->SetPosition(glm::vec3(0,0,0));
	scene->AddObject(floor);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	GraphicsEnvironment glfw;
	glfw.Init(4, 3);

	bool created = glfw.SetWindow(1200, 800, "ETSU Computing Interactive Graphics");
	if (!created) return -1;

	bool loaded = glfw.InitGlad();
	if (!loaded) return -1;

	glfw.SetupGraphics();

	GLFWwindow* window = glfw.GetWindow();

	std::shared_ptr<Shader> shader;
	std::shared_ptr<Scene> scene;
	SetUp3DScene1(shader, scene);

	glfw.CreateRenderer("3d_scene", shader);
	glfw.GetRenderer("3d_scene")->SetScene(scene);

	glfw.StaticAllocate();

	glfw.Run3D();

	return 0;
}

