#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main(){
const int width = 1000;
const int height = 800;

float aspectratio = float(width) / float(height);
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
  window = glfwCreateWindow(width, height, "Project", NULL, NULL);
  if (!window)
  {
	  std::cout << "Failed to create window" << std::endl;
	  glfwTerminate();
	  return -1;
  }

  //disable cursor
  //glfwSetInputMode(window, GLFW_CURSOR,GLFW_CURSOR_NORMAL);

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

  //version of opengl being used
  const GLubyte* vendor = glGetString(GL_VENDOR); // Returns the vendor
  const GLubyte* rendererData = glGetString(GL_RENDERER); // Returns a hint to the model
  std::cout << "Vendor:" << vendor << "   " << "Graphics card:" << rendererData << std::endl;
  std::cout << glGetString(GL_VERSION) << std::endl;

  //vertices for skybox
  float skyboxVertices[] = {
	  // positions          
	  -1.0f,  1.0f, -1.0f,
	  -1.0f, -1.0f, -1.0f,
	  1.0f, -1.0f, -1.0f,
	  1.0f, -1.0f, -1.0f,
	  1.0f,  1.0f, -1.0f,
	  -1.0f,  1.0f, -1.0f,

	  -1.0f, -1.0f,  1.0f,
	  -1.0f, -1.0f, -1.0f,
	  -1.0f,  1.0f, -1.0f,
	  -1.0f,  1.0f, -1.0f,
	  -1.0f,  1.0f,  1.0f,
	  -1.0f, -1.0f,  1.0f,

	  1.0f, -1.0f, -1.0f,
	  1.0f, -1.0f,  1.0f,
	  1.0f,  1.0f,  1.0f,
	  1.0f,  1.0f,  1.0f,
	  1.0f,  1.0f, -1.0f,
	  1.0f, -1.0f, -1.0f,

	  -1.0f, -1.0f,  1.0f,
	  -1.0f,  1.0f,  1.0f,
	  1.0f,  1.0f,  1.0f,
	  1.0f,  1.0f,  1.0f,
	  1.0f, -1.0f,  1.0f,
	  -1.0f, -1.0f,  1.0f,

	  -1.0f,  1.0f, -1.0f,
	  1.0f,  1.0f, -1.0f,
	  1.0f,  1.0f,  1.0f,
	  1.0f,  1.0f,  1.0f,
	  -1.0f,  1.0f,  1.0f,
	  -1.0f,  1.0f, -1.0f,

	  -1.0f, -1.0f, -1.0f,
	  -1.0f, -1.0f,  1.0f,
	  1.0f, -1.0f, -1.0f,
	  1.0f, -1.0f, -1.0f,
	  -1.0f, -1.0f,  1.0f,
	  1.0f, -1.0f,  1.0f
  };

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

  /*VertexBuffer cube_vertex(g_vertex, sizeof(g_vertex));
  VertexBufferLayout cube_vertex_layout;
  cube_vertex_layout.AddFloat(3);
  VertexArray cube_VA;
  cube_VA.addBuffer(cube_vertex, cube_vertex_layout);

  //cubemap
  const CubeMap skyBox(std::vector<std::string>{
	  "../../../src/resources/skybox/right.jpg",
		  "../../../src/resources/skybox/left.jpg",
		  "../../../src/resources/skybox/top.jpg",
		  "../../../src/resources/skybox/bottom.jpg",
		  "../../../src/resources/skybox/front.jpg",
		  "../../../src/resources/skybox/back.jpg"});

  Shader skyBoxShader("../../../src/resources/shaders/cubeMap.glsl");
  skyBoxShader.Bind();
  VertexBuffer skyBoxVB(skyboxVertices, sizeof(skyboxVertices));
  VertexBufferLayout skyBoxLayout;
  skyBoxLayout.AddFloat(3);
  VertexArray skyBoxVA;
  skyBoxVA.addBuffer(skyBoxVB, skyBoxLayout);
  
  //projection matrix
  glmath::mat4 projection;
  float fov = 45.0f;
  projection = glmath::perspective(to_radians(fov), (float)width / (float)height, 0.00000001f, 100.0f);

  //reflection matrix
  glmath::mat4 reflect(1.0f);


  //skybox shader uniform
  skyBoxShader.Bind();

  //camera
  glmath::vec3 cameraPos = glmath::vec3(0.0f, -60.0f, -100.0f);
  // glmath::vec3 cameraPos = glmath::vec3(54.11,3.92044,-55.4537);
  glmath::vec3 cameraFront = glmath::vec3(0.0f, 0.0f, -1.0f);
  glmath::vec3 cameraUp = glmath::vec3(0.0f, 1.0f, 0.0f);
  Camera camera(cameraPos, cameraFront, cameraUp);
  renderer.camera = camera;

  glEnable(GL_DEPTH_TEST);

  context.renderer = &renderer;
  context.fov = fov;
  glfwSetWindowUserPointer(window, &context);

  Shader modelShader("../../../src/resources/shaders/model.glsl");

  //std::cout << "Started loading stadium model\n";
 // Model stadium("../../../src/resources/model/Stadium.obj");
  //std::cout << "Finished loading stadium model" << std::endl;

  //bool renderToTextureFlag;
  //float moveFactor = 0.0f;


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
