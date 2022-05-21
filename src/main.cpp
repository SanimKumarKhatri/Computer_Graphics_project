#include <iostream>
#include "includes/Init.h"

int main(){

	//aspect ratio
float aspectratio = float(width) / float(height);

//glfw window creation
  GLFWwindow *window;
  std::cout << "window and renderer initialized" << std::endl;

  /* Initialize the library */
  if (!glfwInit())
  {
	  fprintf(stderr, "Failed to initialize GLFW\n");
	  //getchar();
	  return -1;
  }
  std::cout << "glfw initialized" << std::endl;

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(width, height, "Graphics Project", NULL, NULL);
  if (!window)
  {
	  std::cout << "Failed to create window" << std::endl;
	  glfwTerminate();
	  return -1;
  }

  //disable cursor
  glfwSetInputMode(window, GLFW_CURSOR,GLFW_CURSOR_DISABLED);

  //mouse movement call back
  //glfwSetCursorPosCallback(window, mouseCallback);

  //scroll callback
 // glfwSetScrollCallback(window, scrollCallBack);

  //window resize call back
 // glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);



  /* Make the window's context current */
  glfwWindowHint(GLFW_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_VERSION_MINOR, 4);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  /*To initialize glew*/
  GLenum err = glewInit();
  if (GLEW_OK != err)
  {
	  std::cout << "Error " << glewGetErrorString(err) << std::endl;
  }


  //for color of the background
  glClearColor(0.7f, 0.13f, 0.8f, 0.4f);

  //global opengl state
  glEnable(GL_DEPTH_TEST);

  //version of opengl being used
  const GLubyte* vendor = glGetString(GL_VENDOR); // Returns the vendor
  const GLubyte* rendererData = glGetString(GL_RENDERER); // Returns a hint to the model
  std::cout << "Vendor:" << vendor << "   " << "Graphics card:" << rendererData << std::endl;
  std::cout << glGetString(GL_VERSION) << std::endl;


  static const float g_vertex[] = {
	-1.0f,-1.0f,-1.0f, // triangle 1 : begin
	-1.0f,-1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, // triangle 1 : end
	1.0f, 1.0f,-1.0f, // triangle 2 : begin
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f, // triangle 2 : end
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f
  };

  Shader skyboxShader("resources/shaders/skyboxVS.glsl", "resources/shaders/skyboxFS.glsl");
  Shader groundShader("resources/shaders/groundVS.glsl", "resources/shaders/groundFS.glsl");
  Shader lightCubeShader("resources/shaders/lightCubeVS.glsl", "resources/shaders/lightCubeFS.glsl");
  Shader lightingShader("resources/shaders/lightVS.glsl", "resources/shaders/lightFS.glsl");

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window))
  {
	  /* Render here */
	  glClear(GL_COLOR_BUFFER_BIT);

	  //glDepthMask(GL_FALSE);
	  
	  /*skyBoxShader.Bind();
	  glmath::mat4 view = glmath::mat4(glmath::mat3(renderer.camera.GetLookAtMatrix()));
	  skyBoxShader.setUniform("view", view);
	  skyBoxShader.setUniform("projection", projection);
	  skyBox.bind();

	  glDepthMask(GL_TRUE);
	  skyBoxShader.Unbind();

	  //setting for models
	  float angle = 0.0f;
	  float timeValue = (float)glfwGetTime();
	  view = renderer.camera.GetLookAtMatrix();

	  projection = glmath::perspective(to_radians(context.fov), aspectratio, 0.1f, 1000.0f);
	  glmath::mat4 trans = glmath::mat4(1.0f);
	  glmath::mat4 model = glmath::mat4(1.0f);

	  model = glmath::mat4(1.0f);
	  model = glmath::rotate(model, to_radians(angle), glmath::vec3(0.5f, -0.5f, 0.5f));
	  angle = 0.0f;
	  trans = glmath::mat4(1.0f);
	  trans = glmath::translate(trans, glmath::vec3(0.0f, -2.5f, -2.0f));

	  float pt = int(timeValue) % 45 * 4;//converted 45 sec tie value to 180 degree to be use in light direction
	  model = glmath::translate(model, glmath::vec3(0.0f, 3.0f, 0.0f));

	  modelShader.setUniform("model", model);
	  modelShader.setUniform("proejection", projection);
	  modelShader.setUniform("trans", trans);
	  modelShader.setUniform("view", view);
	  //stadium.render(modelShader, true);*/
	  glActiveTexture(GL_TEXTURE0);
	  glfwSwapBuffers(window);
	  glfwPollEvents();

  }

  //disablevertexattrixarray
  glDisableVertexAttribArray(0);

  //destroy window to end
  glfwDestroyWindow(window);

  //terminate glfw
  glfwTerminate();

  return 0;
}
