#pragma once
#include "indexbuffer.h"
#include "vertexarray.h"
#include "shader.h"
#include "camera.h"
#include "vec.h"

#include <GLFW/glfw3.h>

//callback functions
void mouseCallback(GLFWwindow* window, double xPos, double yPos);

void scrollCallBack(GLFWwindow* window, double xoffset, double yoffset);

void framebufferSizeCallback(GLFWwindow* window, int width, int height);

//renderer class
struct Renderer {
	static int width, height;

	//variables for time between last frame and current frame and last frame
	float deltaTime, lastFrame;

	//for previous x and y
	static float previousX, previousY;

	bool firstMouse;

	//camera object
	Camera camera;

	//methods
	void clear(unsigned int bits = GL_COLOR_BUFFER_BIT) const;
	void clear(float r, float g, float b, float a, unsigned int bits = GL_COLOR_BUFFER_BIT) const;

	void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;

	void draw(const VertexArray& va, const Shader& shader, unsigned int vertexCount) const;

	void processKeyboardInput(GLFWwindow* window);
};

//userui
struct UIcontext {
	Renderer* renderer;
	float fov;
	bool isNightMode;
	bool logMode;
	float sensitivity;
};