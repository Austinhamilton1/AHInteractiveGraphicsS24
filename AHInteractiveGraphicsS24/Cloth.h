#pragma once
#include <vector>
#include <unordered_set>
#include <glm/glm.hpp>
#include "GraphicsObject.h"

enum SpringType {
	SHEAR,
	BEND,
	STRETCH
};

struct Spring {
	SpringType type;
	float k;
	float length;
	unsigned int i;
	unsigned int j;
};

struct Triangle {
	unsigned int a;
	unsigned int b;
	unsigned int c;
	float GetArea(std::vector<glm::vec3>& positions) const {
		glm::vec3 A = positions[a];
		glm::vec3 B = positions[b];
		glm::vec3 C = positions[c];
		return 0.5f * glm::length(glm::cross(B - A, C - A));
	};
};

class Cloth : public GraphicsObject {
protected:
	unsigned int rows, columns;
	float density, dampingFactor;
	glm::vec3 color;
	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> velocities;
	std::vector<Triangle> triangleMesh;
	std::vector<glm::vec2> textureMapping;
	std::vector<float> massMatrix;
	std::unordered_set<unsigned int> pins;
	std::vector<Spring> springs;
	std::vector<glm::vec3> forceAccum;

public:
	Cloth(glm::vec3 position = {0.0f, 0.0f, 0.0f}, unsigned int rows = 50, unsigned int columns = 50, float width = 10, float height = 10, float density = 0.1f, float dampingFactor = 0.1f);
	inline unsigned int GetRows() { return rows; }
	inline unsigned int GetColumns() { return columns; }
	inline std::vector<glm::vec3>& GetPositions() { return positions; }
	inline std::vector<glm::vec3>& GetVelocities() { return velocities; }
	inline std::vector<float>& GetMassMatrix() { return massMatrix; }
	inline void SetColor(glm::vec3 color) { this->color = color; }

	void Pin(unsigned int vertex);
	void Pin(unsigned int row, unsigned int col);
	void AddForce(glm::vec3 force);
	void ClearAccum();
	void ClearMass();
	void CalculateMass();
	void Update(double elapsedTime);

	void SetBendFactor(float factor);
	void SetShearFactor(float factor);
	void SetStretchFactor(float factor);
	void SetDampingFactor(float factor);

	std::vector<glm::vec3> GetTriangleMeshForRendering();
	std::vector<glm::vec2> GetTextureMappingForRendering();
};