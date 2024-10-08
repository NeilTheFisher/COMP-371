/*
 * Neil Fisher (40240320)
 * Jei Wen Wu (40246641)
 * Allan Wu (40188455)
 */

#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <iostream>
#include <vector>
#include <string>
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

struct Model {
	std::vector<glm::vec3> vertices;
	std::vector<unsigned int> indices;
};

static Model loadObj(const std::string& path) {
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string err;

	if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path.c_str(), ".", true)) {
		std::cerr << "Failed to load OBJ file: " << err << std::endl;
		exit(1);
	}

	Model model;

	for (const auto& shape : shapes) {
		for (const auto& index : shape.mesh.indices) {
			glm::vec3 vertex(
				attrib.vertices[3 * index.vertex_index + 0],
				attrib.vertices[3 * index.vertex_index + 1],
				attrib.vertices[3 * index.vertex_index + 2]
			);
			model.vertices.push_back(vertex);

			model.indices.push_back(model.indices.size());
		}
	}

	return model;
}

static void processInput(GLFWwindow* window, glm::mat4& transform)
{
	const float TRANSLATION_DISTANCE = 0.01f;
	const float ROTATION_ANGLE = 2.0f;
	const float SCALING_FACTOR = 1.1f;

	static glm::vec3 position(0.0f);
	static float rotationX = 0.0f;
	static float rotationY = 0.0f;
	static float rotationZ = 0.0f;
	static float scale = 1.0f;

	// Close window
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	transform = glm::mat4(1.0f);

	// Scaling
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		scale *= SCALING_FACTOR;
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		scale /= SCALING_FACTOR;

	transform = glm::scale(transform, glm::vec3(scale, scale, scale));

	// Translation
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		position.y += TRANSLATION_DISTANCE;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		position.y -= TRANSLATION_DISTANCE;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		position.x -= TRANSLATION_DISTANCE;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		position.x += TRANSLATION_DISTANCE;

	transform = glm::translate(transform, position);

	// Rotation
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		rotationY += ROTATION_ANGLE;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		rotationY -= ROTATION_ANGLE;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		rotationX += ROTATION_ANGLE;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		rotationX -= ROTATION_ANGLE;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		rotationZ += ROTATION_ANGLE;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		rotationZ -= ROTATION_ANGLE;

	transform = glm::rotate(transform, glm::radians(rotationX), glm::vec3(1.0f, 0.0f, 0.0f));
	transform = glm::rotate(transform, glm::radians(rotationY), glm::vec3(0.0f, 1.0f, 0.0f));
	transform = glm::rotate(transform, glm::radians(rotationZ), glm::vec3(0.0f, 0.0f, 1.0f));
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

const char* vertexShaderSource = R"(
#version 330 core

layout(location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
)";

const char* fragmentShaderSource = R"(
#version 330 core

out vec4 FragColor;

void main() {
    FragColor = vec4(0.2, 0.5, 1.0, 1.0);
}
)";

static GLuint compileShader(GLenum shaderType, const char* source) {
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);

	return shader;
}

static GLuint createShaderProgram(const char* vertexSource, const char* fragmentSource) {
	GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexSource);
	GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

	// Link shaders
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// Delete the shaders since they're now linked into
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}


const char* modelPath = R"(D:\1 Important files\Neil Stuff\1 School\Concordia\s6\COMP 371\COMP-371\A3\OpenGLBlender\OpenGLBlender\WaterBottle.obj)";

const float windowWidth = 800;
const float windowHeight = 600;

int main() {
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(800, 600, "Blender Model", nullptr, nullptr);
	if (!window) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	glViewport(0, 0, windowWidth, windowHeight);

	//glEnable(GL_DEPTH_TEST);

	// Enable wireframe mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Load the model
	Model model = loadObj(modelPath);

	GLuint shaderProgram = createShaderProgram(vertexShaderSource, fragmentShaderSource);

	GLuint VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, model.vertices.size() * sizeof(glm::vec3), &model.vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(unsigned int), &model.indices[0], GL_STATIC_DRAW);

	// aPos attribute in the shader (location = 0)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
	glEnableVertexAttribArray(0);

	// Unbind vertex array
	glBindVertexArray(0);

	glm::mat4 modelMatrix = glm::mat4(1.0f);
	float* modelMatrixPtr = glm::value_ptr(modelMatrix);

	glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), windowWidth / windowHeight, 0.0001f, 1000.0f);
	float* projectionMatrixPtr = glm::value_ptr(projectionMatrix);

	glm::mat4 cameraMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));
	float* cameraMatrixPtr = glm::value_ptr(cameraMatrix);

	while (!glfwWindowShouldClose(window)) {
		// process input, the model is the only thing that is moved in the scene
		processInput(window, modelMatrix);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(shaderProgram);

		// Set the transformation uniforms of the shader
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, modelMatrixPtr);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, projectionMatrixPtr);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, cameraMatrixPtr);

		// Render the model
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, model.indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Deallocate resources
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	// Terminate GLFW
	glfwTerminate();

	return 0;
}
