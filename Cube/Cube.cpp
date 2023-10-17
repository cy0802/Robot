#include "Cube.h"
float Cube::jointLength = 10.0f;
glm::vec3 Cube::bodyInitialPosition[] = {
	glm::vec3(0.0f, 135.0f, 0.0f),
	glm::vec3(0.0f, 20.0f, 0.0f),
	glm::vec3(-100.0f, 70.0f, 0.0f),
	glm::vec3(-200.0f, 70.0f, 0.0f),
	glm::vec3(100.0f, 70.0f, 0.0f),
	glm::vec3(200.0f, 70.0f, 0.0f),
	glm::vec3(-20.0f, -155.0f, 0.0f),
	glm::vec3(-20.0f, -280.0f, 0.0f),
	glm::vec3(20.0f, -155.0f, 0.0f),
	glm::vec3(20.0f, -280.0f, 0.0f)
};
glm::vec3 Cube::jointInitialPosition[] = {
	glm::vec3(0.0f, 120.0f, 0.0f), // head and torso
	glm::vec3(-50.0f, 70.0f, 0.0f), // torso and left upper arm
	glm::vec3(-150.0f, 70.0f, 0.0f), // left upper and lower arm
	glm::vec3(50.0f, 70.0f, 0.0f), // torso and right upper arm
	glm::vec3(150.0f, 70.0f, 0.0f), // right upper and lower arm
	glm::vec3(-20.0f, -80.0f, 0.0f), // torso and left upper leg
	glm::vec3(-20.0f, -230.0f, 0.0f), // left upper and lower leg
	glm::vec3(20.0f, -80.0f, 0.0f), // torso and right upper leg
	glm::vec3(20.0f, -230.0f, 0.0f)
};
Cube::Cube(glm::vec3 position, float height, float width, float depth, glm::vec4 color) {
	this->setPosition(position);
	this->color = color;
	this->setShape(height, width, depth);
	this->rotation = this->rotationX = this->rotationY = this->rotationZ = glm::mat4(1.0f);
	parent = NULL;
}
Cube::Cube(glm::vec3 position, float height, float width, float depth) {
	this->setPosition(position);
	this->color = glm::vec4(0.867f, 0.788f, 0.706f, 1.0f);
	this->setShape(height, width, depth);
	this->rotation = this->rotationX = this->rotationY = this->rotationZ = glm::mat4(1.0f);
	parent = NULL;
}
Cube::Cube() {
	this->setPosition(glm::vec3(0, 0, 0));
	this->color = glm::vec4(0, 0, 0, 0);
	this->setShape(0, 0, 0);
	this->rotation = this->rotationX = this->rotationY = this->rotationZ = glm::mat4(1.0f);
	parent = NULL;
}

void Cube::setShape(float height, float width, float depth) {
	this->height = height;
	this->width = width;
	this->depth = depth;
	this->scale = glm::scale(glm::mat4(1.0f), glm::vec3(width, height, depth));
}

void Cube::setParent(Cube* parent) {
	this->parent = parent;
	parent->childs.push_back({this, this->position - parent->position});
}

void Cube::setPosition(glm::vec3 pos) {
	this->position = pos;
	translation = glm::translate(glm::mat4(1.0f), position);
}

void Cube::_rotate(float angle, glm::vec3 rotateAxis) {
	if (abs(rotateAxis.x - 1.0f) < 0.1f) rotationX = glm::rotate(rotationX, glm::radians(angle), rotateAxis);
	else if (abs(rotateAxis.y - 1.0f) < 0.1f) rotationY = glm::rotate(rotationY, glm::radians(angle), rotateAxis);
	else if (abs(rotateAxis.z - 1.0f) < 0.1f) rotationZ = glm::rotate(rotationZ, glm::radians(angle), rotateAxis);
	rotation = rotationX * rotationY * rotationZ;
	for (int i = 0; i < childs.size(); i++) {
		glm::vec3 tmp = rotation * glm::vec4(childs[i].second, 0.0f);
		childs[i].first->setPosition(this->position + tmp);
		childs[i].first->_rotate(angle, rotateAxis);
	}
}
//
//// return texture id
//unsigned int Cube::useTexture() {
//	unsigned int texture;
//	glGenTextures(1, &texture);
//	glBindTexture(GL_TEXTURE_2D, texture);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	int width, height, nrChannels;
//	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
//	unsigned char* data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
//	if (data) {
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//		std::cout << "Successfully open texture image\n";
//		std::cout << width << " " << height << " " << nrChannels << "\n";
//	} else {
//		std::cout << "Failed to load texture" << std::endl;
//		std::cout << stbi_failure_reason() << std::endl;
//	}
//	stbi_image_free(data);
//	return texture;
//}