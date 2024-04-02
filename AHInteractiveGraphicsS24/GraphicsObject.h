#pragma once
#include <glm/glm.hpp>
#include <memory>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "GraphicsStructures.h"
#include "BoundingBox.h"
#include "IBehavior.h"

class IAnimation;

class GraphicsObject
{
protected:
	glm::mat4 referenceFrame;
	std::shared_ptr<VertexBuffer> buffer;
	std::shared_ptr<IndexBuffer> indexBuffer;
	GraphicsObject* parent;
	std::vector<std::shared_ptr<GraphicsObject>> children;
	std::shared_ptr<IAnimation> animation = nullptr;
	Material material;
	std::shared_ptr<BoundingBox> boundingBox = nullptr;
	std::unordered_map<std::string, std::shared_ptr<IBehavior>> behaviorMap;

public:
	GraphicsObject();
	virtual ~GraphicsObject();

	const glm::mat4 GetReferenceFrame() const;
	glm::mat4& GetLocalReferenceFrame() { return referenceFrame; }
	Material& GetMaterial() { return material; }

	void CreateVertexBuffer(unsigned int numberOfElementsPerVertex);
	void SetVertexBuffer(std::shared_ptr<VertexBuffer> buffer);
	inline const std::shared_ptr<VertexBuffer>& GetVertexBuffer() const {
		return buffer;
	}
	inline void SetReferenceFrame(const glm::mat4& referenceFrame) {
		this->referenceFrame = referenceFrame;
	}
	void StaticAllocateBuffers();

	void AddChild(std::shared_ptr<GraphicsObject> child);
	inline const std::vector<std::shared_ptr<GraphicsObject>>& GetChildren() const {
		return children;
	}

	void SetPosition(const glm::vec3& position);
	void ResetOrientation();
	void RotateLocalZ(float degrees);

	inline void SetAnimation(std::shared_ptr<IAnimation> animation) {
		this->animation = animation;
	};

	void Update(double elapsedSeconds);

	void PointAt(glm::vec3 target);

	void CreateIndexBuffer();
	inline std::shared_ptr<IndexBuffer>& GetIndexBuffer() { return indexBuffer; }

	bool IsIndexed() const { return indexBuffer != nullptr; }

	void CreateBoundingBox(float width, float height, float depth);
	inline const BoundingBox& GetBoundingBox() const { return *boundingBox.get(); }
	bool IsIntersectingWithRay(const Ray& ray) const;

	void AddBehavior(std::string name, std::shared_ptr<IBehavior> behavior);
	void SetBehaviorDefaults();
	void SetBehaviorParameters(std::string name, IParams& params);
};


