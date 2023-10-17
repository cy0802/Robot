#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <windows.h>

#include "Cube/Cube.h"
#include "Shader/Shader.h"
#include "_Robot/Robot.h"

const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 1200;
GLFWwindow* window;
void init();
void processInput(GLFWwindow* window);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, 
    GLsizei length, const GLchar* message, const void* userParam);
// Cube test = Cube(glm::vec3(0.0, 0.0, 0.0), 0.1, 0.4, 0.1, glm::vec4(0.757f, 0.486f, 0.455f, 1.0f));
Robot robot;

int main() {
    init();
    Shader shader((char*)"..\\Cube\\cube.vs", (char*)"..\\Cube\\cube.fs");

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(robot.vertices), robot.vertices, GL_STATIC_DRAW);
    
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(1);
    shader.use();
    shader.setMat4((char*)"projection", robot.projection);
    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        glClearColor(0.164706, 0.239216, 0.270588, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        robot.draw(VAO, &shader);
        robot.drawJoint(VAO, &shader);
        
        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            std::cout << "OpenGL Error: " << error << std::endl;
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void init() {
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Robot", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, keyCallback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
    glDebugMessageCallback(MessageCallback, 0);
    glEnable(GL_DEPTH_TEST);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    std::cout << "keyCallback()\n";
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        if (key == GLFW_KEY_F1) robot.body[TORSO]._rotate(1.0f, glm::vec3(0.0f, 1.0f, 0.0f)); // torso right and left
        else if (key == GLFW_KEY_F2) robot.body[TORSO]._rotate(-1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        
        else if (key == GLFW_KEY_F3) robot.joint[HEAD_AND_TORSO]._rotate(1.0f, glm::vec3(0.0f, 1.0f, 0.0f)); // head right and left
        else if (key == GLFW_KEY_F4) robot.joint[HEAD_AND_TORSO]._rotate(-1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        
        else if (key == GLFW_KEY_1) robot.joint[TORSO_AND_LEFT_ARM]._rotate(1.0f, glm::vec3(0.0f, 0.0f, 1.0f)); // left upper arm 
        else if (key == GLFW_KEY_2) robot.joint[TORSO_AND_LEFT_ARM]._rotate(-1.0f, glm::vec3(0.0f, 0.0f, 1.0f)); // xy plane
        else if (key == GLFW_KEY_3) robot.joint[TORSO_AND_LEFT_ARM]._rotate(1.0f, glm::vec3(0.0f, 1.0f, 0.0f)); // xz plane
        else if (key == GLFW_KEY_4) robot.joint[TORSO_AND_LEFT_ARM]._rotate(-1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        else if (key == GLFW_KEY_5) robot.joint[TORSO_AND_LEFT_ARM]._rotate(1.0f, glm::vec3(1.0f, 0.0f, 0.0f)); // yz plane
        else if (key == GLFW_KEY_6) robot.joint[TORSO_AND_LEFT_ARM]._rotate(-1.0f, glm::vec3(1.0f, 0.0f, 0.0f));

        else if (key == GLFW_KEY_Q) robot.joint[LEFT_UPPER_AND_LOWER_ARM]._rotate(1.0f, glm::vec3(0.0f, 0.0f, 1.0f)); //left lower arm
        else if (key == GLFW_KEY_W) robot.joint[LEFT_UPPER_AND_LOWER_ARM]._rotate(-1.0f, glm::vec3(0.0f, 0.0f, 1.0f)); // xy plane
        else if (key == GLFW_KEY_E) robot.joint[LEFT_UPPER_AND_LOWER_ARM]._rotate(1.0f, glm::vec3(0.0f, 1.0f, 0.0f)); // xz plane
        else if (key == GLFW_KEY_R) robot.joint[LEFT_UPPER_AND_LOWER_ARM]._rotate(-1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        else if (key == GLFW_KEY_T) robot.joint[LEFT_UPPER_AND_LOWER_ARM]._rotate(1.0f, glm::vec3(1.0f, 0.0f, 0.0f)); // yz plane
        else if (key == GLFW_KEY_Y) robot.joint[LEFT_UPPER_AND_LOWER_ARM]._rotate(-1.0f, glm::vec3(1.0f, 0.0f, 0.0f));
        
        else if (key == GLFW_KEY_A) robot.joint[TORSO_AND_LEFT_LEG]._rotate(1.0f, glm::vec3(0.0f, 0.0f, 1.0f)); // left upper leg 
        else if (key == GLFW_KEY_S) robot.joint[TORSO_AND_LEFT_LEG]._rotate(-1.0f, glm::vec3(0.0f, 0.0f, 1.0f)); // xy plane
        else if (key == GLFW_KEY_D) robot.joint[TORSO_AND_LEFT_LEG]._rotate(1.0f, glm::vec3(0.0f, 1.0f, 0.0f)); // xz plane
        else if (key == GLFW_KEY_F) robot.joint[TORSO_AND_LEFT_LEG]._rotate(-1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        else if (key == GLFW_KEY_G) robot.joint[TORSO_AND_LEFT_LEG]._rotate(1.0f, glm::vec3(1.0f, 0.0f, 0.0f)); // yz plane
        else if (key == GLFW_KEY_H) robot.joint[TORSO_AND_LEFT_LEG]._rotate(-1.0f, glm::vec3(1.0f, 0.0f, 0.0f));

        else if (key == GLFW_KEY_Z) robot.joint[LEFT_UPPER_AND_LOWER_LEG]._rotate(1.0f, glm::vec3(0.0f, 0.0f, 1.0f)); //left lower leg
        else if (key == GLFW_KEY_X) robot.joint[LEFT_UPPER_AND_LOWER_LEG]._rotate(-1.0f, glm::vec3(0.0f, 0.0f, 1.0f)); // xy plane
        else if (key == GLFW_KEY_C) robot.joint[LEFT_UPPER_AND_LOWER_LEG]._rotate(1.0f, glm::vec3(0.0f, 1.0f, 0.0f)); // xz plane
        else if (key == GLFW_KEY_V) robot.joint[LEFT_UPPER_AND_LOWER_LEG]._rotate(-1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        else if (key == GLFW_KEY_B) robot.joint[LEFT_UPPER_AND_LOWER_LEG]._rotate(1.0f, glm::vec3(1.0f, 0.0f, 0.0f)); // yz plane
        else if (key == GLFW_KEY_N) robot.joint[LEFT_UPPER_AND_LOWER_LEG]._rotate(-1.0f, glm::vec3(1.0f, 0.0f, 0.0f));
        
        // ======================================================================================================================

        else if (key == GLFW_KEY_7) robot.joint[TORSO_AND_RIGHT_ARM]._rotate(1.0f, glm::vec3(0.0f, 0.0f, 1.0f)); // right upper arm 
        else if (key == GLFW_KEY_8) robot.joint[TORSO_AND_RIGHT_ARM]._rotate(-1.0f, glm::vec3(0.0f, 0.0f, 1.0f)); // xy plane
        else if (key == GLFW_KEY_9) robot.joint[TORSO_AND_RIGHT_ARM]._rotate(1.0f, glm::vec3(0.0f, 1.0f, 0.0f)); // xz plane
        else if (key == GLFW_KEY_0) robot.joint[TORSO_AND_RIGHT_ARM]._rotate(-1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        else if (key == GLFW_KEY_MINUS) robot.joint[TORSO_AND_RIGHT_ARM]._rotate(1.0f, glm::vec3(1.0f, 0.0f, 0.0f)); // yz plane
        else if (key == GLFW_KEY_EQUAL) robot.joint[TORSO_AND_RIGHT_ARM]._rotate(-1.0f, glm::vec3(1.0f, 0.0f, 0.0f));

        else if (key == GLFW_KEY_U) robot.joint[RIGHT_UPPER_AND_LOWER_ARM]._rotate(1.0f, glm::vec3(0.0f, 0.0f, 1.0f)); // right lower arm
        else if (key == GLFW_KEY_I) robot.joint[RIGHT_UPPER_AND_LOWER_ARM]._rotate(-1.0f, glm::vec3(0.0f, 0.0f, 1.0f)); // xy plane
        else if (key == GLFW_KEY_O) robot.joint[RIGHT_UPPER_AND_LOWER_ARM]._rotate(1.0f, glm::vec3(0.0f, 1.0f, 0.0f)); // xz plane
        else if (key == GLFW_KEY_P) robot.joint[RIGHT_UPPER_AND_LOWER_ARM]._rotate(-1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        else if (key == GLFW_KEY_LEFT_BRACKET) robot.joint[RIGHT_UPPER_AND_LOWER_ARM]._rotate(1.0f, glm::vec3(1.0f, 0.0f, 0.0f)); // yz plane
        else if (key == GLFW_KEY_RIGHT_BRACKET) robot.joint[RIGHT_UPPER_AND_LOWER_ARM]._rotate(-1.0f, glm::vec3(1.0f, 0.0f, 0.0f));

        else if (key == GLFW_KEY_J) robot.joint[TORSO_AND_RIGHT_LEG]._rotate(1.0f, glm::vec3(0.0f, 0.0f, 1.0f)); // left upper leg 
        else if (key == GLFW_KEY_K) robot.joint[TORSO_AND_RIGHT_LEG]._rotate(-1.0f, glm::vec3(0.0f, 0.0f, 1.0f)); // xy plane
        else if (key == GLFW_KEY_L) robot.joint[TORSO_AND_RIGHT_LEG]._rotate(1.0f, glm::vec3(0.0f, 1.0f, 0.0f)); // xz plane
        else if (key == GLFW_KEY_SEMICOLON) robot.joint[TORSO_AND_RIGHT_LEG]._rotate(-1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        else if (key == GLFW_KEY_APOSTROPHE) robot.joint[TORSO_AND_RIGHT_LEG]._rotate(1.0f, glm::vec3(1.0f, 0.0f, 0.0f)); // yz plane
        else if (key == GLFW_KEY_ENTER) robot.joint[TORSO_AND_RIGHT_LEG]._rotate(-1.0f, glm::vec3(1.0f, 0.0f, 0.0f));

        else if (key == GLFW_KEY_M) robot.joint[RIGHT_UPPER_AND_LOWER_LEG]._rotate(1.0f, glm::vec3(0.0f, 0.0f, 1.0f)); //left lower leg
        else if (key == GLFW_KEY_COMMA) robot.joint[RIGHT_UPPER_AND_LOWER_LEG]._rotate(-1.0f, glm::vec3(0.0f, 0.0f, 1.0f)); // xy plane
        else if (key == GLFW_KEY_PERIOD) robot.joint[RIGHT_UPPER_AND_LOWER_LEG]._rotate(1.0f, glm::vec3(0.0f, 1.0f, 0.0f)); // xz plane
        else if (key == GLFW_KEY_SLASH) robot.joint[RIGHT_UPPER_AND_LOWER_LEG]._rotate(-1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        else if (key == GLFW_KEY_UP) robot.joint[RIGHT_UPPER_AND_LOWER_LEG]._rotate(1.0f, glm::vec3(1.0f, 0.0f, 0.0f)); // yz plane
        else if (key == GLFW_KEY_DOWN) robot.joint[RIGHT_UPPER_AND_LOWER_LEG]._rotate(-1.0f, glm::vec3(1.0f, 0.0f, 0.0f));
    }
}

void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id,
    GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
    std::cerr << "GL CALLBACK: " << message << std::endl;
}