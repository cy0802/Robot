#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <vector>

class Cube {
public:
	static glm::vec3 bodyInitialPosition[10];
	static glm::vec3 jointInitialPosition[9];
	static float jointLength;
	glm::vec3 position;
	glm::vec4 color;
	glm::mat4 scale, translation, rotation;
	glm::mat4 rotationX, rotationY, rotationZ;
	unsigned int VBO = -1;
	Cube* parent;
	std::vector<std::pair<Cube*, glm::vec3>> childs; // child ptr and initial position
	float height, width, depth;
	Cube();
	Cube(glm::vec3 position, float height, float width, float depth);
	Cube(glm::vec3 position, float height, float width, float depth, glm::vec4 color);
	void setParent(Cube* parent);
	void setPosition(glm::vec3);
	void setShape(float, float, float);
	void _rotate(float angle, glm::vec3 rotateAxis);
	unsigned int useTexture();
};