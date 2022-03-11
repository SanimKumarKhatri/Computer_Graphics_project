#include "includes/renderer_user.h"
#include <iostream>

int Renderer::width = 1000;
int Renderer::height = 900;

float Renderer::previousX = 500;
float Renderer::previousY = 450;

void mouseCallback(GLFWwindow* window, double xPos, double yPos) {
    UIcontext* context = (UIcontext*)glfwGetWindowUserPointer(window);

    Renderer* renderer = context->renderer;
    if (renderer->firstMouse)
    {
        Renderer::previousX = xPos;
        Renderer::previousY = yPos;
        context->renderer->firstMouse = false;
    }
    float xOffset = xPos - Renderer::previousX;
    float yOffset = Renderer::previousY - yPos;

    const float sensitivity = context->sensitivity;

    Renderer::previousX = xPos;
    Renderer::previousY = yPos;

    renderer->camera.processMouseEvent(xOffset, yOffset, false);

    glfwSetWindowUserPointer(window, context);
}

void scrollCallBack(GLFWwindow* window, double xoffset, double yoffset) {
    UIcontext* context = (UIcontext*)glfwGetWindowUserPointer(window);
    float fov = context->fov;

    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 150.0f)
        fov = 150.0f;

    context->fov = fov;
    glfwSetWindowUserPointer(window, context);
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    UIcontext* context = (UIcontext*)glfwGetWindowUserPointer(window);
    Renderer::width = width;
    Renderer::height = height;
}

//renderer
void Renderer::clear(unsigned int bits) const {
    glClear(bits);
}

void Renderer::clear(float r, float g, float b, float a, unsigned int bits) const {
    glClearColor(r, g, b, a);
    glClear(bits);
}

void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {
    shader.Bind();
    va.bind();
    ib.bind();

    GLCall(glDrawElements(GL_TRIANGLES, ib.count, GL_UNSIGNED_INT, NULL));
}

void Renderer::draw(const VertexArray& va, const Shader& shader, unsigned int vertexCount) const {
    va.bind();
    shader.Bind();

    GLCall(glDrawArrays(GL_TRIANGLES, 0, vertexCount));
}

void Renderer::processKeyboardInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, 1);
    }
    UIcontext* context = (UIcontext*)glfwGetWindowUserPointer(window);

    float currentTime = glfwGetTime();
    deltaTime = currentTime - lastFrame;
    lastFrame = currentTime;

    // std::cout << "FPS->" << 1 / (deltaTime) << std::endl;

    float cameraSpeed = context->sensitivity * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.cameraPosition += cameraSpeed * glmath::normalize(camera.cameraFront);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.cameraPosition -= cameraSpeed * glmath::normalize(glmath::cross(camera.cameraFront, camera.cameraUp));
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.cameraPosition -= cameraSpeed * glmath::normalize(camera.cameraFront);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.cameraPosition += cameraSpeed * glmath::normalize(glmath::cross(camera.cameraFront, camera.cameraUp));
    }
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
        context->isNightMode = true;
    }
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
        context->isNightMode = false;
    }

    //for log mode
    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {
        context->logMode = false;
    }
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
        context->logMode = true;
    }

    //increase the speed of camera
    if (glfwGetKey(window, GLFW_KEY_LEFT_BRACKET) == GLFW_PRESS && context->sensitivity > 0.5) {
        context->sensitivity -= 0.5;
        if (context->logMode)
            std::cout << "Sensitivity: " << context->sensitivity << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT_BRACKET) == GLFW_PRESS && context->sensitivity < 10.0) {
        context->sensitivity += 0.5;
        if (context->logMode)
            std::cout << "Sensitivity: " << context->sensitivity << std::endl;
    }

    glfwSetWindowUserPointer(window, context);
}