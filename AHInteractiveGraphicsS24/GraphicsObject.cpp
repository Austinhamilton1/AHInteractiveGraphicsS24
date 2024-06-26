#include "GraphicsObject.h"
#include "IAnimation.h"
#include <glm/gtc/matrix_transform.hpp>

GraphicsObject::GraphicsObject() : referenceFrame(1.0f), parent(nullptr), material({0.1f, 0.5f, 16.0f}), indexBuffer(nullptr) {
	CreateBoundingBox(1.0f, 1.0f, 1.0f);
}

GraphicsObject::~GraphicsObject()
{
}

const glm::mat4 GraphicsObject::GetReferenceFrame() const
{
	if (parent != nullptr) {
		return parent->referenceFrame * referenceFrame;
	}
	return referenceFrame;
}

void GraphicsObject::CreateVertexBuffer(unsigned int numberOfElementsPerVertex)
{
	buffer = std::make_shared<VertexBuffer>(numberOfElementsPerVertex);
}

void GraphicsObject::SetVertexBuffer(std::shared_ptr<VertexBuffer> buffer)
{
	this->buffer = buffer;
}

void GraphicsObject::AllocateBuffers()
{
	buffer->Select();
	if (buffer->IsDynamic())
		buffer->DynamicAllocate();
	else
		buffer->StaticAllocate();
	buffer->Deselect();
	if (indexBuffer != nullptr) {
		indexBuffer->SelectBuffer();
		indexBuffer->StaticAllocate();
		indexBuffer->DeselectBuffer();
	}
	for (auto& child : children) {
		child->AllocateBuffers();
	}
}

void GraphicsObject::AddChild(std::shared_ptr<GraphicsObject> child)
{
	children.push_back(child);
	child->parent = this;
}

void GraphicsObject::SetPosition(const glm::vec3& position)
{
	referenceFrame[3] = glm::vec4(position, 1.0f);
}

void GraphicsObject::ResetOrientation()
{
	glm::vec4 position = referenceFrame[3];
	referenceFrame = glm::mat4(1.0f);
	referenceFrame[3] = position;
}

void GraphicsObject::RotateLocalZ(float degrees)
{
	referenceFrame = glm::rotate(
		referenceFrame,
		glm::radians(degrees),
		glm::vec3(0.0f, 0.0f, 1.0f)
	);
}

void GraphicsObject::Update(double elapsedSeconds) {
	for (auto& it : behaviorMap) {
		it.second->Update(elapsedSeconds);
	}
}

void GraphicsObject::PointAt(glm::vec3 target) {
	glm::vec3 position = referenceFrame[3];
	glm::vec3 zAxis = glm::normalize(target - position);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 xAxis = glm::normalize(glm::cross(up, zAxis));
	glm::vec3 yAxis = glm::cross(zAxis, xAxis);
	referenceFrame[0] = glm::vec4(xAxis, 0.0f);
	referenceFrame[1] = glm::vec4(yAxis, 0.0f);
	referenceFrame[2] = glm::vec4(zAxis, 0.0f);
}

void GraphicsObject::CreateIndexBuffer() {
	indexBuffer = std::make_shared<IndexBuffer>();
}

void GraphicsObject::CreateBoundingBox(float width, float height, float depth) {
	boundingBox = std::make_shared<BoundingBox>();
	boundingBox->SetReferenceFrame(referenceFrame);
	boundingBox->Create(width, height, depth);
}

bool GraphicsObject::IsIntersectingWithRay(const Ray& ray) const {
	boundingBox->SetReferenceFrame(referenceFrame);
	return boundingBox->IsIntersectingWithRay(ray);
}

void GraphicsObject::AddBehavior(std::string name, std::shared_ptr<IBehavior> behavior) {
	behaviorMap[name] = behavior;
}

void GraphicsObject::SetBehaviorDefaults() {
	for (auto& it : behaviorMap) {
		it.second->StoreDefaults();
	}
}

void GraphicsObject::SetBehaviorParameters(std::string name, IParams& params) {
	behaviorMap[name]->SetParameter(params);
}
