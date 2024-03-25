#pragma once
#include "GraphicsObject.h"
#include "GraphicsStructures.h"
#include <vector>

class Cloth : public GraphicsObject {
private:
	int rows, columns;
	std::vector<float> massMatrix;
	std::vector<Spring> springs;
	std::vector<Particle> particles;
	//std::vector<Triangle> triangleMesh;

public:
	Cloth(int rows, int columns, float density);

	inline std::vector<Particle> GetParticles() { return particles; }
	inline int GetRows() { return rows; }
	inline int GetColumns() { return columns; }
	inline bool IsCloth() { return true; }
};