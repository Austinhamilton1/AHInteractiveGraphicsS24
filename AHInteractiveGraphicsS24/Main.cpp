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
#include "Cloth.h"
#include "ParticleSystem.h"

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

static void SetUp3DScene1(GraphicsEnvironment& env, std::shared_ptr<Shader>& shader, std::shared_ptr<Scene>& scene) {
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
	env.AddObject("cuboid", object);
	std::shared_ptr<VertexBuffer> buffer = Generate::Cuboid(10.0f, 5.0f, 5.0f);

	
	buffer->SetTexture(tex);
	buffer->SelectTexture();
	object->SetVertexBuffer(buffer);
	object->SetPosition(glm::vec3(5, 5, 0));
	scene->AddObject(object);

	std::shared_ptr<Texture> crateTexture = std::make_shared<Texture>();
	crateTexture->LoadTextureDataFromFile("Crates/crate_texture.png");
	std::shared_ptr<GraphicsObject> crate = std::make_shared<GraphicsObject>();
	env.AddObject("crate", crate);
	std::shared_ptr<VertexBuffer> buffer2 = Generate::Cuboid(10.0f, 5.0f, 5.0f);
	
	buffer2->SetTexture(crateTexture);
	buffer->SelectTexture();
	crate->SetVertexBuffer(buffer2);
	crate->SetPosition(glm::vec3(-10, 5, 0));
	scene->AddObject(crate);

	std::shared_ptr<Texture> floorTexture = std::make_shared<Texture>();
	floorTexture->LoadTextureDataFromFile("Floors/floor.png");
	std::shared_ptr<GraphicsObject> floor = std::make_shared<GraphicsObject>();
	env.AddObject("floor", floor);
	std::shared_ptr<VertexBuffer> buffer3 = Generate::XZPlane(20, 20);

	buffer3->SetTexture(floorTexture);
	buffer3->SelectTexture();
	floor->SetVertexBuffer(buffer3);
	floor->SetPosition(glm::vec3(0,0,0));
	scene->AddObject(floor);
}

void SetUp3DScene2(GraphicsEnvironment& env, std::shared_ptr<Shader>& shader, std::shared_ptr<Scene>& scene) {
	TextFile vertSource("lighting.vert.glsl");
	TextFile fragSource("lighting.frag.glsl");
	if (!vertSource.ReadIn() || !fragSource.ReadIn()) return;
	shader = std::make_shared<Shader>(vertSource.GetData(), fragSource.GetData());
	shader->AddUniform("projection");
	shader->AddUniform("world");
	shader->AddUniform("view");
	shader->AddUniform("texUnit");
	shader->AddUniform("materialAmbientIntensity");
	shader->AddUniform("materialSpecularIntensity");
	shader->AddUniform("materialShininess");
	shader->AddUniform("globalLightPosition");
	shader->AddUniform("globalLightColor");
	shader->AddUniform("globalLightIntensity");
	shader->AddUniform("localLightPosition");
	shader->AddUniform("localLightColor");
	shader->AddUniform("localLightIntensity");
	shader->AddUniform("locoalLightAttenuationCoef");
	shader->AddUniform("viewPosition");

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
	env.AddObject("cuboid", object);
	std::shared_ptr<VertexBuffer> buffer = Generate::NormalCuboid(10.0f, 5.0f, 5.0f);


	buffer->SetTexture(tex);
	buffer->SelectTexture();
	object->SetVertexBuffer(buffer);
	object->SetPosition(glm::vec3(5, 5, 0));
	scene->AddObject(object);

	std::shared_ptr<Texture> crateTexture = std::make_shared<Texture>();
	crateTexture->LoadTextureDataFromFile("Crates/crate_texture.png");
	std::shared_ptr<GraphicsObject> crate = std::make_shared<GraphicsObject>();
	env.AddObject("crate", crate);
	std::shared_ptr<VertexBuffer> buffer2 = Generate::NormalCuboid(10.0f, 5.0f, 5.0f);

	buffer2->SetTexture(crateTexture);
	buffer->SelectTexture();
	crate->SetVertexBuffer(buffer2);
	crate->SetPosition(glm::vec3(-10, 5, 0));
	scene->AddObject(crate);

	std::shared_ptr<Texture> floorTexture = std::make_shared<Texture>();
	floorTexture->LoadTextureDataFromFile("Floors/floor.png");
	std::shared_ptr<GraphicsObject> floor = std::make_shared<GraphicsObject>();
	env.AddObject("floor", floor);
	std::shared_ptr<VertexBuffer> buffer3 = Generate::NormalXZPlane(20, 20);

	buffer3->SetTexture(floorTexture);
	buffer3->SelectTexture();
	floor->SetVertexBuffer(buffer3);
	floor->SetPosition(glm::vec3(0, 0, 0));
	scene->AddObject(floor);
}

static void SetUpLightbulb(GraphicsEnvironment& env, std::shared_ptr<Shader>& shader, std::shared_ptr<Scene>& scene) {
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
	tex->LoadTextureDataFromFile("Lightbulb/lightbulb.png");
	scene = std::make_shared<Scene>();
	std::shared_ptr<GraphicsObject> lightbulb = std::make_shared<GraphicsObject>();
	env.AddObject("lightbulb", lightbulb);
	std::shared_ptr<VertexBuffer> buffer = Generate::XYPlane(2.0f, 2.0f);


	buffer->SetTexture(tex);
	buffer->SelectTexture();
	lightbulb->SetVertexBuffer(buffer);
	lightbulb->SetPosition(glm::vec3(0, 5, 8));
	scene->AddObject(lightbulb);
}

void SetUp3DScene3(GraphicsEnvironment& env, std::shared_ptr<Shader>& shader, std::shared_ptr<Scene>& scene) {
	TextFile vertSource("lighting.vert.glsl");
	TextFile fragSource("lighting.frag.glsl");
	if (!vertSource.ReadIn() || !fragSource.ReadIn()) return;
	shader = std::make_shared<Shader>(vertSource.GetData(), fragSource.GetData());
	shader->AddUniform("projection");
	shader->AddUniform("world");
	shader->AddUniform("view");
	shader->AddUniform("texUnit");
	shader->AddUniform("materialAmbientIntensity");
	shader->AddUniform("materialSpecularIntensity");
	shader->AddUniform("materialShininess");
	shader->AddUniform("globalLightPosition");
	shader->AddUniform("globalLightColor");
	shader->AddUniform("globalLightIntensity");
	shader->AddUniform("localLightPosition");
	shader->AddUniform("localLightColor");
	shader->AddUniform("localLightIntensity");
	shader->AddUniform("locoalLightAttenuationCoef");
	shader->AddUniform("viewPosition");

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
	object->CreateBoundingBox(10.0f, 5.0f, 5.0f);
	std::shared_ptr<HighLightBehavior> objectHighlight = std::make_shared<HighLightBehavior>();
	objectHighlight->SetObject(object);
	object->AddBehavior("highlight", objectHighlight);

	env.AddObject("cuboid", object);
	std::shared_ptr<VertexBuffer> buffer = Generate::NormalCuboid(10.0f, 5.0f, 5.0f);

	buffer->SetTexture(tex);
	buffer->SelectTexture();
	object->SetVertexBuffer(buffer);
	object->SetPosition(glm::vec3(5, 5, 0));
	scene->AddObject(object);

	std::shared_ptr<Texture> crateTexture = std::make_shared<Texture>();
	crateTexture->LoadTextureDataFromFile("Crates/crate_texture.png");
	std::shared_ptr<GraphicsObject> crate = std::make_shared<GraphicsObject>();
	crate->CreateBoundingBox(10.0f, 5.0f, 5.0f);
	std::shared_ptr<HighLightBehavior> crateHighLight = std::make_shared<HighLightBehavior>();
	crateHighLight->SetObject(object);
	crate->AddBehavior("highlight", crateHighLight);
	env.AddObject("crate", crate);
	std::shared_ptr<VertexBuffer> buffer2 = Generate::NormalCuboid(10.0f, 5.0f, 5.0f);

	buffer2->SetTexture(crateTexture);
	buffer->SelectTexture();
	crate->SetVertexBuffer(buffer2);
	crate->SetPosition(glm::vec3(-10, 5, 0));
	scene->AddObject(crate);

	std::shared_ptr<Texture> floorTexture = std::make_shared<Texture>();
	floorTexture->LoadTextureDataFromFile("Floors/floor.png");
	std::shared_ptr<GraphicsObject> floor = std::make_shared<GraphicsObject>();
	env.AddObject("floor", floor);
	std::shared_ptr<VertexBuffer> buffer3 = Generate::NormalXZPlane(20, 20);

	buffer3->SetTexture(floorTexture);
	buffer3->SelectTexture();
	floor->SetVertexBuffer(buffer3);
	floor->SetPosition(glm::vec3(0, 0, 0));
	scene->AddObject(floor);
}

static void SetUpPCObjectsScene(GraphicsEnvironment& env, std::shared_ptr<Shader>& shader, std::shared_ptr<Scene>& scene) {
	TextFile vertSource("basic.vert.glsl");
	TextFile fragSource("basic.frag.glsl");
	if (!vertSource.ReadIn() || !fragSource.ReadIn()) return;
	shader = std::make_shared<Shader>(vertSource.GetData(), fragSource.GetData());
	shader->AddUniform("projection");
	shader->AddUniform("view");
	shader->AddUniform("world");

	std::shared_ptr<GraphicsObject> pcLinesCircle = std::make_shared<GraphicsObject>();
	env.AddObject("cirlce", pcLinesCircle);
	std::shared_ptr<VertexBuffer> buffer = Generate::XZLineCircle(5, glm::vec3(1.0f, 0.0f, 0.0f));
	pcLinesCircle->SetVertexBuffer(buffer);
	pcLinesCircle->CreateIndexBuffer();
	Generate::LineCircleIndexes(pcLinesCircle->GetIndexBuffer());
	buffer->SetPrimitiveType(GL_LINES);

	std::shared_ptr<GraphicsObject> pcLinesCylinder = std::make_shared<GraphicsObject>();
	env.AddObject("cylinder", pcLinesCylinder);
	std::shared_ptr<VertexBuffer> buffer2 = Generate::LineCylinder(5, 5, glm::vec3(0.0f, 0.0f, 1.0f));
	pcLinesCylinder->SetVertexBuffer(buffer2);
	pcLinesCylinder->CreateIndexBuffer();
	Generate::LineCylinderIndexes(pcLinesCylinder->GetIndexBuffer());
	buffer2->SetPrimitiveType(GL_LINES);

	scene = std::make_shared<Scene>();
	pcLinesCircle->SetPosition(glm::vec3(0.0f, 1.0f, 7.0f));
	pcLinesCylinder->SetPosition(glm::vec3(4.0f, 2.5f, 5.0f));
	scene->AddObject(pcLinesCircle);
	scene->AddObject(pcLinesCylinder);
}

static void SetUpClothScene(GraphicsEnvironment& env, std::shared_ptr<Shader>& shader, std::shared_ptr<Scene>& scene) {
	TextFile vertSource("lighting.vert.glsl");
	TextFile fragSource("lighting.frag.glsl");
	if (!vertSource.ReadIn() || !fragSource.ReadIn()) return;
	shader = std::make_shared<Shader>(vertSource.GetData(), fragSource.GetData());
	shader->AddUniform("projection");
	shader->AddUniform("world");
	shader->AddUniform("view");
	shader->AddUniform("texUnit");
	shader->AddUniform("materialAmbientIntensity");
	shader->AddUniform("materialSpecularIntensity");
	shader->AddUniform("materialShininess");
	shader->AddUniform("globalLightPosition");
	shader->AddUniform("globalLightColor");
	shader->AddUniform("globalLightIntensity");
	shader->AddUniform("localLightPosition");
	shader->AddUniform("localLightColor");
	shader->AddUniform("localLightIntensity");
	shader->AddUniform("locoalLightAttenuationCoef");
	shader->AddUniform("viewPosition");

	std::shared_ptr<ParticleSystem> cloth = std::make_shared<ParticleSystem>(glm::vec3(0.0f, 5.0f, 0.0f), 10, 10);
	cloth->SetPosition({ 0.0f, 0.0f, 0.0f });
	env.AddObject("cloth", cloth);
	std::shared_ptr<VertexBuffer> clothBuffer = Generate::ParticleSystemBuffer(cloth, {1.0f, 1.0f, 1.0f });
	std::shared_ptr<Texture> clothTexture = std::make_shared<Texture>();
	clothTexture->LoadTextureDataFromFile("Cloths/cloth_texture.png");
	clothBuffer->SetTexture(clothTexture);
	clothBuffer->SelectTexture();
	cloth->SetVertexBuffer(clothBuffer);

	std::shared_ptr<GraphicsObject> ground = std::make_shared<GraphicsObject>();
	ground->SetPosition({ 0.0f, -2.0f, 0.0f });
	env.AddObject("ground", ground);
	std::shared_ptr<VertexBuffer> groundBuffer = Generate::NormalXZPlane(50.0f, 50.0f);
	std::shared_ptr<Texture> groundTexture = std::make_shared<Texture>();
	groundTexture->LoadTextureDataFromFile("Floors/grass.jpg");
	groundBuffer->SetTexture(groundTexture);
	groundBuffer->SelectTexture();
	ground->SetVertexBuffer(groundBuffer);

	std::shared_ptr<GraphicsObject> pole1 = std::make_shared<GraphicsObject>();
	pole1->SetPosition({ -7.0f, 4.0f, 0.0f });
	env.AddObject("pole1", pole1);
	std::shared_ptr<GraphicsObject> pole2 = std::make_shared<GraphicsObject>();
	pole2->SetPosition({ 7.0f, 4.0f, 0.0f });
	env.AddObject("pole2", pole2);
	std::shared_ptr<VertexBuffer> poleBuffer = Generate::NormalCuboid(1.0f, 10.0f, 1.0f);
	std::shared_ptr<Texture> poleTexture = std::make_shared<Texture>();
	poleTexture->LoadTextureDataFromFile("Wood/wood.jpg");
	poleBuffer->SetTexture(poleTexture);
	poleBuffer->SelectTexture();
	pole1->SetVertexBuffer(poleBuffer);
	pole2->SetVertexBuffer(poleBuffer);

	scene = std::make_shared<Scene>();
	scene->AddObject(cloth);
	scene->AddObject(ground);
	scene->AddObject(pole1);
	scene->AddObject(pole2);
}

static void SetUpClothesLineScene(GraphicsEnvironment& env, std::shared_ptr<Shader>& shader, std::shared_ptr<Scene>& scene) {
	TextFile vertSource("basic.vert.glsl");
	TextFile fragSource("basic.frag.glsl");
	if (!vertSource.ReadIn() || !fragSource.ReadIn()) return;
	shader = std::make_shared<Shader>(vertSource.GetData(), fragSource.GetData());
	shader->AddUniform("projection");
	shader->AddUniform("view");
	shader->AddUniform("world");

	std::shared_ptr<GraphicsObject> clothesLine = std::make_shared<GraphicsObject>();
	env.AddObject("clothesLine", clothesLine);
	std::shared_ptr<VertexBuffer> clothesLineBuffer = Generate::Line({ -7.0f, 9.0f, 0.0f }, { 7.0f, 9.0f, 0.0f }, { 0.0f, 0.0f, 0.0f });
	clothesLine->SetVertexBuffer(clothesLineBuffer);
	clothesLine->CreateIndexBuffer();
	Generate::LineIndexes(clothesLine->GetIndexBuffer());
	clothesLineBuffer->SetPrimitiveType(GL_LINES);

	scene = std::make_shared<Scene>();
	scene->AddObject(clothesLine);
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
	SetUpClothScene(glfw, shader, scene);

	std::shared_ptr<Shader> clothesLineShader;
	std::shared_ptr<Scene> clothesLineScene;
	SetUpClothesLineScene(glfw, clothesLineShader, clothesLineScene);

	glfw.CreateRenderer("cloth_scene", shader);
	glfw.GetRenderer("cloth_scene")->SetScene(scene);

	glfw.CreateRenderer("clothes_line_scene", clothesLineShader);
	glfw.GetRenderer("clothes_line_scene")->SetScene(clothesLineScene);

	glfw.StaticAllocate();

	glfw.Run3D();

	return 0;
}

