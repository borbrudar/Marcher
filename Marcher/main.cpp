#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "Camera.h"
#include "Shader.h"
#include "Sphere.h"

//function prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void processInput(GLFWwindow *window, Camera &camera, float deltaTime);

//global variables
const int scrwidth = 800, scrheight = 600;
bool firstMouse = 1;
float lastX = scrwidth / 2, lastY = scrheight / 2;
float lastFrame = 0, deltaTime = 0;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

int main() {
	//initialize the window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(scrwidth, scrheight, "Marcher", NULL, NULL);
	if (window == NULL){
		std::cout << "Failed to create GLFW window" << 
std::endl;
		glfwTerminate();
		return -1;
	}

	//set callback functions
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);

	//initialize glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//some other opengl settings
	glEnable(GL_DEPTH_TEST);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//shader compilation
	Shader shader("res/shaders/vertex.vs", "res/shaders/fragment.fs");

	Sphere s(shader);

	//matrices
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)scrwidth / (float)scrheight, 0.1f, 100.0f);
	glm::mat4 model = glm::mat4(1.f);
	//render loop
	while (!glfwWindowShouldClose(window)) {
		//calculate time
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//view matrix (updated every frame)
		glm::mat4 view = camera.GetViewMatrix();

		shader.setMat4("view", view);
		shader.setMat4("projection", projection);
		shader.setMat4("model", model);
		// draw here ----------------------------------------------------------------------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		processInput(window, camera, deltaTime);

		s.draw(shader);
		//----------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//exit
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {

	if (firstMouse)
	{
		lastX = (float)xpos;
		lastY = (float)ypos;
		firstMouse = false;
	}

	float xoffset = (float)xpos - lastX;
	float yoffset = lastY - (float)ypos; // reversed since y-coordinates go from bottom to top

	lastX = (float)xpos;
	lastY = (float)ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void processInput(GLFWwindow *window, Camera &camera, float deltaTime) {

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}
