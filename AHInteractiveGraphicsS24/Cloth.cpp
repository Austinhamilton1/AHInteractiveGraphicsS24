#include "Cloth.h"

Cloth::Cloth(int rows, int columns, float density) : rows(rows), columns(columns), massMatrix(1.0f) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			Particle p;
			float xPercentage = j / columns;
			float yPercentage = i / rows;
			p.position = glm::vec3(-20 + xPercentage * 40, 20 - xPercentage * 30, 0);
			p.velocity = glm::vec3(0, 0, 0);
			particles.push_back(p);
		}
	}
}
