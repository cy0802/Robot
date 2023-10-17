#include "Robot.h"
Robot::Robot() {
	// initialize all body parts
	body[HEAD] = Cube(Cube::bodyInitialPosition[HEAD], 30.0f, 50.0f, 40.0f);
	body[TORSO] = Cube(Cube::bodyInitialPosition[TORSO], 200.0f, 100.0f, 80.0f, glm::vec4(0.757f, 0.486f, 0.455f, 1.0f));
	body[UPPER_LEFT_ARM] = Cube(Cube::bodyInitialPosition[UPPER_LEFT_ARM], 30.0f, 100.0f, 30.0f);
	body[LOWER_LEFT_ARM] = Cube(Cube::bodyInitialPosition[LOWER_LEFT_ARM], 20.0f, 100.0f, 20.0f);
	body[UPPER_RIGHT_ARM] = Cube(Cube::bodyInitialPosition[UPPER_RIGHT_ARM], 30.0f, 100.0f, 30.0f);
	body[LOWER_RIGHT_ARM] = Cube(Cube::bodyInitialPosition[LOWER_RIGHT_ARM], 20.0f, 100.0f, 20.0f);
	body[UPPER_LEFT_LEG] = Cube(Cube::bodyInitialPosition[UPPER_LEFT_LEG], 150.0f, 30.0f, 30.0f);
	body[LOWER_LEFT_LEG] = Cube(Cube::bodyInitialPosition[LOWER_LEFT_LEG], 100.0f, 20.0f, 20.0f);
	body[UPPER_RIGHT_LEG] = Cube(Cube::bodyInitialPosition[UPPER_RIGHT_LEG], 150.0f, 30.0f, 30.0f);
	body[LOWER_RIGHT_LEG] = Cube(Cube::bodyInitialPosition[LOWER_RIGHT_LEG], 100.0f, 20.0f, 20.0f);
	
	// initialize all joints
	joint[HEAD_AND_TORSO] = Cube(Cube::jointInitialPosition[HEAD_AND_TORSO], Cube::jointLength, Cube::jointLength, Cube::jointLength);
	joint[TORSO_AND_LEFT_ARM] = Cube(Cube::jointInitialPosition[TORSO_AND_LEFT_ARM], Cube::jointLength, Cube::jointLength, Cube::jointLength);
	joint[LEFT_UPPER_AND_LOWER_ARM] = Cube(Cube::jointInitialPosition[LEFT_UPPER_AND_LOWER_ARM], Cube::jointLength, Cube::jointLength, Cube::jointLength);
	joint[TORSO_AND_RIGHT_ARM] = Cube(Cube::jointInitialPosition[TORSO_AND_RIGHT_ARM], Cube::jointLength, Cube::jointLength, Cube::jointLength);
	joint[RIGHT_UPPER_AND_LOWER_ARM] = Cube(Cube::jointInitialPosition[RIGHT_UPPER_AND_LOWER_ARM], Cube::jointLength, Cube::jointLength, Cube::jointLength);
	joint[TORSO_AND_LEFT_LEG] = Cube(Cube::jointInitialPosition[TORSO_AND_LEFT_LEG], Cube::jointLength, Cube::jointLength, Cube::jointLength);
	joint[LEFT_UPPER_AND_LOWER_LEG] = Cube(Cube::jointInitialPosition[LEFT_UPPER_AND_LOWER_LEG], Cube::jointLength, Cube::jointLength, Cube::jointLength);
	joint[TORSO_AND_RIGHT_LEG] = Cube(Cube::jointInitialPosition[TORSO_AND_RIGHT_LEG], Cube::jointLength, Cube::jointLength, Cube::jointLength);
	joint[RIGHT_UPPER_AND_LOWER_LEG] = Cube(Cube::jointInitialPosition[RIGHT_UPPER_AND_LOWER_LEG], Cube::jointLength, Cube::jointLength, Cube::jointLength);

	// setup parent and child
	body[HEAD].setParent(&joint[HEAD_AND_TORSO]);
	body[UPPER_LEFT_ARM].setParent(&joint[TORSO_AND_LEFT_ARM]);
	body[UPPER_RIGHT_ARM].setParent(&joint[TORSO_AND_RIGHT_ARM]);
	body[LOWER_LEFT_ARM].setParent(&joint[LEFT_UPPER_AND_LOWER_ARM]);
	body[LOWER_RIGHT_ARM].setParent(&joint[RIGHT_UPPER_AND_LOWER_ARM]);
	body[UPPER_LEFT_LEG].setParent(&joint[TORSO_AND_LEFT_LEG]);
	body[UPPER_RIGHT_LEG].setParent(&joint[TORSO_AND_RIGHT_LEG]);
	body[LOWER_LEFT_LEG].setParent(&joint[LEFT_UPPER_AND_LOWER_LEG]);
	body[LOWER_RIGHT_LEG].setParent(&joint[RIGHT_UPPER_AND_LOWER_LEG]);
	
	joint[HEAD_AND_TORSO].setParent(&body[TORSO]);
	joint[TORSO_AND_LEFT_ARM].setParent(&body[TORSO]);
	joint[TORSO_AND_LEFT_LEG].setParent(&body[TORSO]);
	joint[TORSO_AND_RIGHT_ARM].setParent(&body[TORSO]);
	joint[TORSO_AND_RIGHT_LEG].setParent(&body[TORSO]);
	joint[LEFT_UPPER_AND_LOWER_ARM].setParent(&body[UPPER_LEFT_ARM]);
	joint[RIGHT_UPPER_AND_LOWER_ARM].setParent(&body[UPPER_RIGHT_ARM]);
	joint[LEFT_UPPER_AND_LOWER_LEG].setParent(&body[UPPER_LEFT_LEG]);
	joint[RIGHT_UPPER_AND_LOWER_LEG].setParent(&body[UPPER_RIGHT_LEG]);
}


void Robot::draw(unsigned int VAO, Shader* shader) { // inside the rendering loop
	for (int i = 0; i < this->numOfBodyParts; i++) { // draw body part
		// int textureID = this->body[0].useTexture();
		// glActiveTexture(GL_TEXTURE0);
		// glBindTexture(GL_TEXTURE_2D, textureID);
		shader->use();
		// shader->setInt((char*)"_texture", textureID);
		shader->set4float((char*)"color", this->body[i].color.r, this->body[i].color.g, this->body[i].color.b, this->body[i].color.a);
		shader->setMat4((char*)"local", this->body[i].rotation * this->body[i].scale);
		shader->setMat4((char*)"view", this->body[i].translation);
		shader->setMat4((char*)"model", glm::mat4(1.0f));

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

void Robot::drawJoint(unsigned int VAO, Shader* shader) { // inside the rendering loop
	for (int i = 0; i < this->numOfJoints; i++) { // draw body part
		// int textureID = this->body[0].useTexture();
		// glActiveTexture(GL_TEXTURE0);
		// glBindTexture(GL_TEXTURE_2D, textureID);
		shader->use();
		// shader->setInt((char*)"_texture", textureID);
		shader->set4float((char*)"color", this->joint[i].color.r, this->joint[i].color.g, this->joint[i].color.b, this->joint[i].color.a);
		shader->setMat4((char*)"local", this->joint[i].rotation * this->joint[i].scale);
		shader->setMat4((char*)"view", this->joint[i].translation);
		shader->setMat4((char*)"model", glm::mat4(1.0f));

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}