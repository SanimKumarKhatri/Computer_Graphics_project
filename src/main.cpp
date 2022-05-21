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


  /*static const float g_vertex[] = {
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
  };*/

  //shaders
  Shader skyboxShader("../../../src/resources/shaders/skyboxVS.glsl", "../../../src/resources/shaders/skyboxFS.glsl");
  Shader groundShader("../../../src/resources/shaders/groundVS.glsl", "../../../src/resources/shaders/groundFS.glsl");
  Shader lightCubeShader("../../../src/resources/shaders/lightCubeVS.glsl", "../../../src/resources/shaders/lightCubeFS.glsl");
  Shader lightingShader("../../../src/resources/shaders/lightVS.glsl", "../../../src/resources/shaders/lightFS.glsl");

  //lights
  Light light;

  //skybox
  unsigned int skyboxVAO, skyboxVBO;
  glGenVertexArrays(1, &skyboxVAO);
  glGenBuffers(1, &skyboxVBO);
  glBindVertexArray(skyboxVAO);
  glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  unsigned int cubemapTexture = loadCubemap(faces);
  skyboxShader.use();
  skyboxShader.setInt("skybox", 0);
  //ground plane
  unsigned int groundPlaneVBO, groundPlaneVAO, groundPlaneEBO;
  glGenVertexArrays(1, &groundPlaneVAO);
  glGenBuffers(1, &groundPlaneVBO);
  glGenBuffers(1, &groundPlaneEBO);
  glBindVertexArray(groundPlaneVAO);
  glBindBuffer(GL_ARRAY_BUFFER, groundPlaneVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(groundPlaneVertices), groundPlaneVertices, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, groundPlaneEBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(groundPlaneIndices), groundPlaneIndices, GL_STATIC_DRAW);
  //position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  //texture coord attribute
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  // load and create ground texture 
  unsigned int groundTexture;
  glGenTextures(1, &groundTexture);
  glBindTexture(GL_TEXTURE_2D, groundTexture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
  // set the texture wrapping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // load image, create texture and generate mipmaps
  int width, height, nrChannels;
  // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
  unsigned char* data = stbi_load("../../../src/resources/grass.jfif", &width, &height, &nrChannels, 0);
  if (data)
  {
	  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	  glGenerateMipmap(GL_TEXTURE_2D);
	  std::cout << "../../../src/resources/grass.jfif texture loaded" << std::endl;
  }
  else
  {
	  std::cout << "Failed to load texture" << std::endl;
  }
  stbi_image_free(data);
  //groundMatrix
  glm::mat4 groundModelMatrix = glm::translate(glm::mat4(1.f), glm::vec3(10.f, -1.5f, 0.f));
  groundModelMatrix = glm::scale(groundModelMatrix, glm::vec3(500.f));
  groundShader.use();
  groundShader.setMat4("model", groundModelMatrix);
  groundShader.setInt("g_texture", 0);

  //lightCube
  unsigned int lightCubeVBO, lightCubeVAO;
  glGenVertexArrays(1, &lightCubeVAO);
  glGenBuffers(1, &lightCubeVBO);
  glBindBuffer(GL_ARRAY_BUFFER, lightCubeVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(lightCubeVertices), lightCubeVertices, GL_STATIC_DRAW);
  glBindVertexArray(lightCubeVAO);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  //load model here


  // shader configuration
  lightingShader.use();
  lightingShader.setInt("material.diffuse", 0);
  lightingShader.setInt("material.specular", 1);


  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window))
  {
	  //time frame 
	  float currentFrame = glfwGetTime();
	  deltaTime = currentFrame - lastFrame;
	  lastFrame = currentFrame;

	  // input
	  processInput(window);

	  /* Render here */
	  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


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
