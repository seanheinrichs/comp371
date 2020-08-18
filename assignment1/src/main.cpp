/*
	COMP 371 - Section CC
	Practical Assignment #3
	Written By:
		Benjamin Therien (40034572)
		Sean Heinrichs (40075789)
		Wayne Huras (40074423)
		Isabelle Gourchette (40008121)
		Ziming Wang (40041601)
	Due:  August 21st, 2020

sand: 	https://gallery.yopriceville.com/Backgrounds/Background_Beach_Sand#.XzsmF2hKiUk
*/

#define _SCL_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/config.h>

#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL

#include "utils/AssimpTranslation.h"
#include "Objects/geometry/Polygon.h"
#include "Objects/Grid.hpp"
#include "Objects/Terrain.hpp"
#include "Objects/Camera.h"
#include "Objects/lighting/Light.h"
#include "modeling/OurModels.cpp"
#include "utils/GL_Error.h"
#include "utils/objloader.cpp"
#include "utils/renderHelpers.h"
#include "Opengl_a/Shader.h"
#include "Opengl_a/Material.h"
#include "Common.h"

#include <GL/glew.h>    
#include <GLFW/glfw3.h> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform2.hpp>
#include <yaml-cpp/parser.h>
#include <yaml-cpp/yaml.h>
#include <yaml-cpp/node/parse.h>

// for Skybox
#include "utils/stb_image.h"
#include <vector>
#include <stdio.h>

#define GLFW_REFRESH_RATE 60
#define	GLFW_DOUBLEBUFFER GLFW_TRUE

/* Function Declarations */
void processInput(GLFWwindow *window, ModelContainer** models, Light** pointLights, bool collision);
void cursorPositionCallback(GLFWwindow * window, double xPos, double yPos);
void setupTextureMapping();
void RenderScene(Shader* shader, ModelContainer *ben, ModelContainer *sean, ModelContainer *isa, ModelContainer *ziming, ModelContainer *wayne, Model *terrain);
void RenderGrid(Shader* shader, unsigned int grid_VAOs[], Grid mainGrid);
void ShadowFirstPass(Shader* shader, ModelContainer *ben, ModelContainer *sean, ModelContainer *isa, ModelContainer *ziming, ModelContainer *wayne, unsigned int grid_VAOs[], Grid mainGrid, Model *terrain);
void ShadowSecondPass(Shader* shader, ModelContainer *ben, ModelContainer *sean, ModelContainer *isa, ModelContainer *ziming, ModelContainer *wayne, unsigned int grid_VAOs[], Grid mainGrid, Model *terrain);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
unsigned int loadTexture(const char *path);
unsigned int loadCubemap(std::vector<std::string> faces);
void loadSkybox(Shader &skyboxShader);
void drawSkybox(Shader &skyboxShader);
float distanceFromCamera(glm::vec3 cameraPos, AABB aabb);
bool checkCollision(ModelContainer** models);

/* Global Constants */
unsigned int WINDOW_WIDTH = 1024;
unsigned int WINDOW_HEIGHT = 768;
const unsigned int SHADOW_WIDTH = 1024;
const unsigned int SHADOW_HEIGHT = 1024;
float SENSITIVITY = 0.1f;

/* Camera Setup */
Camera camera = Camera(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, -2.0f), glm::vec3(0.0f, 1.0f, 0.0f));
float deltaTime = 0.0f;
float lastFrame = 0.0f;
bool collision = false;
glm::mat4 model, projection, view;
char prevKey;

// Initialize variables used for rotations
float previousXPos = WINDOW_WIDTH / 2.0f;
float previousYPos = WINDOW_HEIGHT / 2.0f;
float xOffset = 0.0f;
float yOffset = 0.0f;
float rX = 0.0f;
float rY = 0.0f;

glm::vec3 cameraJump = glm::vec3(0.0f, 2.0f, 0.0f);
int jumpCounter = 0;

bool firstMouse = true;

// Variables used for light and shadows
unsigned int depthMapFBO;
unsigned int depthMap;
float near_plane = 0.1f, far_plane = 100.0f;
glm::mat4 lightSpaceMatrix(1.0f);
glm::mat4 lightProjection(1.0f);
glm::mat4 lightView(1.0f);

// Variables used for Skybox
unsigned int skyboxVAO, skyboxVBO, cubemapTexture;

// Variables used for Fog / Sky Color (Fog/ClearColor)
const float RED = 0.84;
const float BLUE = 0.80;
const float GREEN = 0.7;

//globals used for selecting render mode and models
GLenum MODE = GL_TRIANGLES;
int selected = 0;
int useTextures = 1;
bool useShadows = true;
glm::vec3 activeLightSource(0.0f, 3.0f, -0.1f);

/* External linkage for global varibles */
GLenum* g_texLocations = new GLenum[32];
Material* g_materials = new Material[32];
Texture* g_textures = new Texture[32];
float *g_shininess = new float[32];
glm::vec3 *g_specularStrength = new glm::vec3[32];

int main(void)
{
	YAML::Node config = YAML::LoadFile("comp371/assignment1/src/Config/config.yaml");

	for (std::size_t i = 0; i < config["Variables"].size(); i++) {
		std::cout << config["Variables"][i]["name"].as<std::string>() << " = " << config["Variables"][i]["value"].as<std::string>() << "\n";
	}

	time_t startTime = time(new time_t());
	std::cout << "cpp version: "<< __cplusplus << std::endl;


	/* Initialize GLFW */
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	GLFWwindow* window;

	// Create a window and its OpenGL context 
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "COMP 371 - Assignment 1", NULL, NULL);
	if (!window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwMakeContextCurrent(window);
	glfwSetCursorPosCallback(window, cursorPositionCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Initialize GLEW 
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	//enable blending for correct texture rendering effects
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	// Enable depth test for 3D rendering 
	GLCall(glEnable(GL_DEPTH_TEST));

	//Enable Culling
	GLCall(glEnable(GL_CULL_FACE));
	GLCall(glCullFace(GL_BACK));
	GLCall(glFrontFace(GL_CCW));

	// Build and Compile Shader Program 
	Shader modelShader("comp371/assignment1/src/Shaders/assimp.modelShader.vertex", "comp371/assignment1/src/Shaders/assimp.modelShader.fragment");
	Shader lightShader("comp371/assignment1/src/Shaders/lightShader.vertex", "comp371/assignment1/src/Shaders/lightShader.fragment");
	Shader depthShader("comp371/assignment1/src/Shaders/shadow_mapping_depth.vertex", "comp371/assignment1/src/Shaders/shadow_mapping_depth.fragment");
	Shader skyboxShader("comp371/assignment1/src/Shaders/skyboxShader.vertex", "comp371/assignment1/src/Shaders/skyboxShader.fragment");
	setupTextureMapping();

	// [Models]

	//obj loader
	//these vectors will store the extracted data from the obj file through the objloader 
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	//extracting data from obj files
	bool extraction = loadOBJ("../Assets/Models/planet.obj", vertices, uvs, normals);


	/*
	ModelContainer* ben = loadModel("../Assets/Models/palmtree/palmtree.obj");
	std::cout << ben->models.size() << std::endl;
	ben->optimizeModels();
	ben->setVertexController(true, true, false, true);

	for (std::vector<Model *>::iterator it = ben->models.begin(); it < ben->models.end(); it++)
		(*it)->textureIndex = 11; 
		std::cout << ben->models.size() << std::endl;
	*/
	//ben->print();
	
	ModelContainer* ben = new ModelContainer();
	createBensModel(ben, &modelShader);

	ben->bindArrayBuffer();

	ModelContainer* sean = new ModelContainer();
	createSeansModel(sean, &modelShader);
	sean->bindArrayBuffer();

	ModelContainer* isa = new ModelContainer();
	createIsabellesModel(isa, &modelShader);
	isa->bindArrayBuffer();

	ModelContainer* ziming = new ModelContainer();
	createZimingsModel(ziming, &modelShader);
	ziming->bindArrayBuffer();

	ModelContainer* wayne = new ModelContainer();
	createWaynesModel(wayne, &modelShader);
	wayne->bindArrayBuffer();

	Model* light = new Model(true, false, false, true, "light", &lightShader, -1);
	createLightModel(light);
	light->bindArrayBuffer(true, light);

	// [Terrain] - vertex grid && indices from example: https://www.youtube.com/watch?v=l6PEfzQVpvM&fbclid=IwAR0TkM569m6FsOe30NcF_5qdPV8wGODo2qeTYbzT2rkkLCjqLWWu-2J0VXI
	Terrain * t = new Terrain();
	Shape * loadedShape = new Shape(glm::vec3(0.0f, 0.0f, 0.0f), t->vertices, t->textureCoords, t->normals);

	Model* terrain = new Model(true, true, false, true, "terrain", &modelShader, 0);
	terrain->addPolygon(loadedShape);
	terrain->bindArrayBuffer(true, terrain);

	// [Point Lights]

	Light* bensPL = new Light(light, glm::vec3(0.0f, 3.0f, -0.1f), true);
	Light* seansPL = new Light(light, glm::vec3(3.5f, 3.0f, -4.0f), false);
	Light* waynesPL = new Light(light, glm::vec3(-4.0f, 3.0f, -4.0f), false);
	Light* isasPL = new Light(light, glm::vec3(3.5f, 3.0f, 4.0f), false);
	Light* zimingsPL = new Light(light, glm::vec3(-4.0f, 3.0f, 4.0f), false);

	Light* spotLight = new Light(light, glm::vec3(0.0f, 1.0f, -8.0f), false);

	// [Grid]

	Grid mainGrid = Grid();

	unsigned int grid_VAOs[3], grid_VBOs[3], grid_EBO;
	GLCall(glGenVertexArrays(3, grid_VAOs));
	GLCall(glGenBuffers(3, grid_VBOs));
	GLCall(glGenBuffers(1, &grid_EBO));

	// [Grid Floor] 
	GLCall(glBindVertexArray(grid_VAOs[1]));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, grid_VBOs[1]));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(mainGrid.floorVertices), mainGrid.floorVertices, GL_STATIC_DRAW));
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0));
	GLCall(glEnableVertexAttribArray(0));  // Position
	GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))));
	GLCall(glEnableVertexAttribArray(1));  // Texture
	GLCall(glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float))));
	GLCall(glEnableVertexAttribArray(2));  // Normals

	Light** pointLights = new Light*[5];
	pointLights[0] = bensPL;
	pointLights[1] = seansPL;
	pointLights[2] = isasPL;
	pointLights[3] = zimingsPL;
	pointLights[4] = waynesPL;

	ModelContainer** models = new ModelContainer*[6];
	models[0] = ben;
	models[1] = sean;
	models[2] = isa;
	models[3] = ziming;
	models[4] = wayne;

	terrain->addScale(glm::vec3(3.0f, 3.0f, 3.0f));
	terrain->addTranslation(glm::vec3(0.0f - 5, 0.1f, 0.0f - 5));

	ben->addScale(glm::vec3(1.2f, 1.2f, 1.2f));
	ben->addTranslation(glm::vec3(0.0f, 0.4f, 0.0f));
	ben->addRotation(90, glm::vec3(1.0f, 0.0f, 0.0f));

	sean->addScale(glm::vec3(0.2f, 0.2f, 0.2f));
	sean->addTranslation(glm::vec3(3.5f, 0.0f, -4.0f));

	wayne->addScale(glm::vec3(0.2f, 0.2f, 0.2f));
	wayne->addTranslation(glm::vec3(-4.0f, 0.0f, -4.0f));
	wayne->addRotation(90, glm::vec3(1.0f, 0.0f, 0.0f));

	isa->addScale(glm::vec3(0.2f, 0.2f, 0.2f));
	isa->addTranslation(glm::vec3(3.5f, 0.0f, 4.0f));

	ziming->addScale(glm::vec3(0.2f, 0.2f, 0.2f));
	ziming->addTranslation(glm::vec3(-4.0f, 0.0f, 4.0f));

	light->addScale(glm::vec3(0.1f, 0.1f, 0.1f));
	light->addTranslation(glm::vec3(0.0f, 0.50f, -1.0f));

	// Skybox load
	loadSkybox(skyboxShader);

	// [Configure Depth Map FBO]

	glGenFramebuffers(1, &depthMapFBO);
	// create depth texture
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// attach depth texture as FBO's depth buffer
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	modelShader.use();
	modelShader.setInt("shadowMap", 11);	// Must be unused texture slot

	// Fog
	modelShader.setVec3("skyColor", RED, BLUE, GREEN);

	bindTextures();

	std::cout << "it took " << difftime(time(new time_t), startTime) << " seconds to reach rendering" << std::endl;

	// Main Loop 
	while (!glfwWindowShouldClose(window))
	{
		// Set frame for Camera (taken from LearnOpenGL)
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check Collision
		collision = false;
		collision = checkCollision(models);

		// Set camera y value
		float terrainHeight;
		terrainHeight = t->getHeightOfTerrain(camera.position.x, camera.position.z, terrain);
		camera.position.y = terrainHeight + 1.0f;

		// Event Handling
		processInput(window, models, pointLights, collision);

		// Render
		//GLCall(glClearColor(RED, BLUE, GREEN, 1.0f));
		GLCall(glClearColor(0, 0, 0, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		// Start Using Model Shader
		modelShader.use();
		modelShader.setInt("useTextures", useTextures);
		modelShader.setBool("useShadows", useShadows);
		modelShader.setVec3("viewPos", camera.position);


		// Set Light Properties
		spotLight->setShaderValues(&modelShader, true);

		for (int i = 0; i < 5; i++)
		{
			if (pointLights[i]->getActive())
			{
				pointLights[i]->setShaderValues(&modelShader, false);
			}
		}

		// Recompute Camera Pipeline
		modelShader.setMat4("model", model);

		projection = glm::perspective(glm::radians(camera.fieldOfViewAngle), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
		modelShader.setMat4("projection", projection);

		view = camera.calculateViewMatrix();
		view = glm::rotate(view, glm::radians(rX), glm::vec3(0.0f, 0.0f, -1.0f));
		view = glm::rotate(view, glm::radians(rY), glm::vec3(-1.0f, 0.0f, 0.0f));
		modelShader.setMat4("view", view);

		// Render Scene with shadowmap to calculate shadows with depthShader (1ST PASS)
		ShadowFirstPass(&depthShader, ben, sean, isa, ziming, wayne, grid_VAOs, mainGrid, terrain);

		// Reset Viewport
		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Render Scene as normal using the generated depth/shadowmap with modelShader(2ND PASS)
		ShadowSecondPass(&modelShader, ben, sean, isa, ziming, wayne, grid_VAOs, mainGrid, terrain);

		// [Objects Not Affected by Light Source Go Below]

		// Start Using Lighting Shader
		lightShader.use();
		lightShader.setMat4("projection", projection);
		lightShader.setMat4("view", view);

		// [Point Lights]
		lightShader.setInt("fill", -1);
		for (int i = 0; i < 5; i++)
		{
			if (pointLights[i]->getActive())
			{
				pointLights[i]->getModel()->bind();
				model = pointLights[i]->getModel()->getModelMatrix();
				model = glm::mat4(1.0f);
				model = glm::translate(model, pointLights[i]->getPosition());
				model = glm::scale(model, glm::vec3(0.1f));
				lightShader.setMat4("model", model);
				GLCall(glDrawArrays(GL_TRIANGLES, 0, pointLights[i]->getModel()->getVAVertexCount()));
			}
		}

		// Draw Skybox as last item
		drawSkybox(skyboxShader);

		// Swap Buffers and Poll for Events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	// De-allocate resources 
	ben->deallocate();
	sean->deallocate();
	wayne->deallocate();
	isa->deallocate();
	ziming->deallocate();
	light->deallocate();
	terrain->deallocate();
	glDeleteVertexArrays(1, &skyboxVAO);
	glDeleteBuffers(1, &skyboxVAO);

	// Terminate Program 
	glfwTerminate();
	return 0;
}

// Event handling functions
void processInput(GLFWwindow *window, ModelContainer** models, Light** pointLights, bool collision)
{

	float cameraSpeed = 1.0 * deltaTime;

	// [Render Mode]

	// Press "SHIFT + P" to change rendering to POINTS
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
	{
		MODE = GL_POINTS;
	}

	// Press "SHIFT + L" to change rendering to LINES
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS && (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
	{
		MODE = GL_LINES;
	}

	// Press "SHIFT + T" to change rendering to TRIANGLES
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS && (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
	{
		MODE = GL_TRIANGLES;
	}

	// [Model Selection]

	// Press "W" to move FORWARD
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && (!collision || (collision && prevKey != 'W')))
	{
		prevKey = 'W';
		camera.moveForward(cameraSpeed);
	}

	// Press "S" to move BACKWARD
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && (!collision || (collision && prevKey != 'S')))
	{
		prevKey == 'S';
		camera.moveBackward(cameraSpeed);
	}

	// Press "A" to move LEFT
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && (!collision || (collision && prevKey != 'A')))
	{
		prevKey = 'A';
		camera.moveLeft(cameraSpeed);
	}

	// Press "D" to move RIGHT
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && (!collision || (collision && prevKey != 'D')))
	{
		prevKey = 'D';
		camera.moveRight(cameraSpeed);
	}
	
	// Press "6" to select terrain
	if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS && (selected != 5))
	{
		selected = 5;
		for (int i = 0; i < 5; i++)
		{
			if (i == selected) {
				pointLights[i]->setActive(true);
				activeLightSource = pointLights[i]->getPosition();
			}
			else {
				pointLights[i]->setActive(false);
			}
		}
	}

	//Press "SPACE" to JUMP
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		camera.position += cameraJump * cameraSpeed;
		jumpCounter++;
	}

	else if (jumpCounter > 0)
	{
		camera.position -= cameraJump * cameraSpeed;
		jumpCounter--;
	}

	// Press "SHIFT + W" to move FORWARD faster
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
	{
		if (!collision) 
		{
			camera.moveForward(cameraSpeed * 1.5);
		}
	}

	// Press "SHIFT + S" to move BACKWARD faster
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
	{
		camera.moveBackward(cameraSpeed * 1.5);
	}

	// Press "SHIFT + D" to move RIGHT faster
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
	{
		camera.moveRight(cameraSpeed * 1.5);
	}

	// Press "SHIFT + A" to move LEFT faster
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
	{
		camera.moveLeft(cameraSpeed * 1.5);
	}

	// [Rotation]

	// Press 'SHIFT + A' to rotate the model to the left 5 degrees about y-axis
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
	{
		models[selected]->addRotation(5.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	// Press 'SHIFT + D' to rotate the model to the right 5 degrees about y-axis
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
	{
		models[selected]->addRotation(-5.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	}
	

	//TRANSLATE

	// Press "SHIFT + A" to move the selected model to the LEFT
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS && (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
	{
		if ((glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
			models[selected]->addTranslation(glm::vec3(0.8f, 0.0f, 0.0f));
		else
			models[selected]->addTranslation(glm::vec3(0.1f, 0.0f, 0.0f));
	}

	// Press "SHIFT + D" to move the selected model to the RIGHT
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS && (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
	{
		if ((glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
			models[selected]->addTranslation(glm::vec3(-0.8f, 0.0f, 0.0f));
		else
			models[selected]->addTranslation(glm::vec3(-0.1f, 0.0f, 0.0f));
	}

	// Press "SHIFT + W" to move the selected model UP
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS && (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
	{
		if ((glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
			models[selected]->addTranslation(glm::vec3(0.0f, 0.8f, 0.0f));
		else
			models[selected]->addTranslation(glm::vec3(0.0f, 0.1f, 0.0f));
	}

	// Press "SHIFT + S" to move the selected model DOWN
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS && (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
	{
		if ((glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
			models[selected]->addTranslation(glm::vec3(0.0f,  -0.8f, 0.0f ));
		else
			models[selected]->addTranslation(glm::vec3(0.0f, -0.1f, 0.0f));
	}

	// Press "SHIFT + Q" to move the selected model DOWN
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS && (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
	{
		if ((glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
			models[selected]->addTranslation(glm::vec3(0.0f, 0.0f, -0.8f));
		else
			models[selected]->addTranslation(glm::vec3(0.0f, 0.0f, -0.1f));
	}

	// Press "SHIFT + E" to move the selected model DOWN
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
	{
		if ((glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
			models[selected]->addTranslation(glm::vec3(0.0f, 0.0f, 0.8f));
		else
			models[selected]->addTranslation(glm::vec3(0.0f, 0.0f, 0.1f));

	}
	//TRANSLATE




	// [Scale]

	// Press 'U' to scale UP the model
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
	{
		models[selected]->addScale(glm::vec3(0.1f, 0.1f, 0.1f));
	}

	// Press 'J' to scale DOWN the model
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
	{
		models[selected]->addScale(glm::vec3(-0.0001f, -0.0001f, -0.0001f));
	}

	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS && !(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
	{
		models[selected]->resetShear();
	}

	
	
	// [Texture Toggle]

	// Press 'X' to turn textures OFF
	if ((useTextures != 1) && glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS && (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
	{
		useTextures = 1;
	}

	// Press 'SHIFT + X' to turn textures ON
	if ((useTextures != 0) && glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS && !(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
	{
		useTextures = 0;
	}

	// [Shadow Toggle]

	// Press 'M' to turn shadows OFF
	if (!useShadows && glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS && (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
	{
		useShadows = true;
	}

	// Press 'SHIFT + M' to turn shadows ON
	if (useShadows && glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS && !(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
	{
		useShadows = false;
	}
}

void cursorPositionCallback(GLFWwindow * window, double xPos, double yPos)
{
	if (firstMouse)
	{
		previousXPos = xPos;
		previousYPos = yPos;
		firstMouse = false;
	}

	float xoffset = xPos - previousXPos * SENSITIVITY;
	float yoffset = previousYPos - yPos * SENSITIVITY;

	previousXPos = xPos;
	previousYPos = yPos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}
//map textures to a global data structure
void setupTextureMapping()
{
	g_texLocations[0] = GL_TEXTURE0;
	g_texLocations[1] = GL_TEXTURE1;
	g_texLocations[2] = GL_TEXTURE2;
	g_texLocations[3] = GL_TEXTURE3;
	g_texLocations[4] = GL_TEXTURE4;
	g_texLocations[5] = GL_TEXTURE5;
	g_texLocations[6] = GL_TEXTURE6;
	g_texLocations[7] = GL_TEXTURE7;
	g_texLocations[8] = GL_TEXTURE8;
	g_texLocations[9] = GL_TEXTURE9;
	g_texLocations[10] = GL_TEXTURE10;
	g_texLocations[11] = GL_TEXTURE11; // used by shadow map
	g_texLocations[12] = GL_TEXTURE12; // used by skybox
	g_texLocations[13] = GL_TEXTURE13;
	g_texLocations[14] = GL_TEXTURE14;
	g_texLocations[15] = GL_TEXTURE15;
	g_texLocations[16] = GL_TEXTURE16;
	g_texLocations[17] = GL_TEXTURE17;
	g_texLocations[18] = GL_TEXTURE18;
	g_texLocations[19] = GL_TEXTURE19;
	g_texLocations[20] = GL_TEXTURE20;
	g_texLocations[21] = GL_TEXTURE21;
	g_texLocations[22] = GL_TEXTURE22;
	g_texLocations[23] = GL_TEXTURE23;
	g_texLocations[24] = GL_TEXTURE24;
	g_texLocations[25] = GL_TEXTURE25;
	g_texLocations[26] = GL_TEXTURE26;
	g_texLocations[27] = GL_TEXTURE27;
	g_texLocations[28] = GL_TEXTURE28;
	g_texLocations[29] = GL_TEXTURE29;
	g_texLocations[30] = GL_TEXTURE30;
	g_texLocations[31] = GL_TEXTURE31;

	g_textures[0] = Texture("comp371/assignment1/src/Resources/sand.jpg");
	g_textures[1] = Texture("comp371/assignment1/src/Resources/cast_iron.png");
	g_textures[2] = Texture("comp371/assignment1/src/Resources/chrome.png");
	g_textures[3] = Texture("comp371/assignment1/src/Resources/speaker_holes.png");
	g_textures[4] = Texture("comp371/assignment1/src/Resources/shiny_metal.png");
	g_textures[5] = Texture("comp371/assignment1/src/Resources/box1.png");
	g_textures[6] = Texture("comp371/assignment1/src/Resources/box2.png");
	g_textures[7] = Texture("comp371/assignment1/src/Resources/box3.png");
	g_textures[8] = Texture("comp371/assignment1/src/Resources/box4.png");
	g_textures[9] = Texture("comp371/assignment1/src/Resources/box5.png");
	g_textures[10] = Texture("comp371/assignment1/src/Resources/water.jpg");
	//g_textures[13] = Texture("C:\\Users\\Benjamin Therien\\Documents\\comp371\\models\\backpack\\diffuse.jpg");
	//g_textures[11] // used by shadow map
	//g_textures[12] // used by skybox


	g_shininess[0] = 2.0f;
	g_shininess[1] = 2.0f;
	g_shininess[2] = 2.0f;
	g_shininess[3] = 2.0f;
	g_shininess[4] = 2.0f;
	g_shininess[5] = 256.0f;
	g_shininess[6] = 256.0f;
	g_shininess[7] = 256.0f;
	g_shininess[8] = 256.0f;
	g_shininess[9] = 256.0f;
	g_shininess[10] = 64.0f;
	g_shininess[13] = 64.0f;
	g_shininess[11] = 64.0f;// used by shadow map
	g_shininess[12] = 64.0f; // used by skybox

	g_specularStrength[0] = glm::vec3(1.0f, 1.0f, 1.0f);
	g_specularStrength[1] =	glm::vec3(1.0f, 1.0f, 1.0f);
	g_specularStrength[2] =	glm::vec3(1.0f, 1.0f, 1.0f);
	g_specularStrength[3] =	glm::vec3(1.0f, 1.0f, 1.0f);
	g_specularStrength[4] =	glm::vec3(1.0f, 1.0f, 1.0f);
	g_specularStrength[5] = glm::vec3(0.1f, 0.1f, 0.1f);
	g_specularStrength[6] = glm::vec3(0.1f, 0.1f, 0.1f);
	g_specularStrength[7] = glm::vec3(0.1f, 0.1f, 0.1f);
	g_specularStrength[8] = glm::vec3(0.1f, 0.1f, 0.1f);
	g_specularStrength[9] = glm::vec3(0.1f, 0.1f, 0.1f);
	g_specularStrength[10] = glm::vec3(0.5f, 0.5f, 0.5f);
	g_specularStrength[11] = glm::vec3(0.5f, 0.5f, 0.5f);
	g_specularStrength[12] = glm::vec3(0.5f, 0.5f, 0.5f);
	g_specularStrength[13] = glm::vec3(0.5f, 0.5f, 0.5f);
	//g_specularStrength[11] // used by shadow map
	//g_specularStrength[12] // used by skybox

	g_materials[0] = Material(g_specularStrength[0], g_textures[0], g_shininess[0]);
	g_materials[1] = Material(g_specularStrength[1], g_textures[1], g_shininess[1]);
	g_materials[2] = Material(g_specularStrength[2], g_textures[2], g_shininess[2]);
	g_materials[3] = Material(g_specularStrength[3], g_textures[3], g_shininess[3]);
	g_materials[4] = Material(g_specularStrength[4], g_textures[4], g_shininess[4]);
	g_materials[5] = Material(g_specularStrength[5], g_textures[5], g_shininess[5]);
	g_materials[6] = Material(g_specularStrength[6], g_textures[6], g_shininess[6]);
	g_materials[7] = Material(g_specularStrength[7], g_textures[7], g_shininess[7]);
	g_materials[8] = Material(g_specularStrength[8], g_textures[8], g_shininess[8]);
	g_materials[9] = Material(g_specularStrength[9], g_textures[9], g_shininess[9]);
	g_materials[10] = Material(g_specularStrength[10], g_textures[10], g_shininess[10]);
	g_materials[11] = Material(g_specularStrength[11], g_textures[11], g_shininess[11]);
	g_materials[12] = Material(g_specularStrength[12], g_textures[12], g_shininess[12]);
}

void RenderScene(Shader* shader, ModelContainer *ben, ModelContainer *sean, ModelContainer *isa, ModelContainer *ziming, ModelContainer *wayne, Model *terrain)
{
	bindTextures();
	shader->use();

	ben->draw(MODE, shader);
	sean->draw(MODE, shader);

	isa->draw(MODE, shader);


	ziming->draw(MODE, shader);

	wayne->draw(MODE, shader);

	terrain->draw(MODE, shader);

	wayne->draw(MODE, shader);
}

void DrawSphere(Model* sphereModel, ModelContainer *modelInnerSoccerBall, Shader* shader)
{
	sphereModel->bind();
	//	model = ben->getModelMatrix(false)*ben->getTranslationSphere();;
	glm::mat4 model = modelInnerSoccerBall->getModelMatrix();
	model = glm::scale(model, glm::vec3(1.25f, 1.25f, 1.25f));
	model = glm::translate(model, glm::vec3(0.0f, 4.0f, 0.0f));
	shader->setMat4("model", model);
	GLCall(glDrawArrays(GL_LINES, 0, sphereModel->getVAVertexCount()));
}

void RenderGrid(Shader* shader, unsigned int grid_VAOs[], Grid mainGrid)
{
	// [Grid Floor]

	GLCall(glBindVertexArray(grid_VAOs[1]));
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0005f));
	g_textures[10].bind(g_texLocations[10]);
	shader->setFloat("material.shininess", g_shininess[10]);
	shader->setVec3("material.specular", g_specularStrength[10]);
	shader->setInt("material.diffuse", 10);
	shader->setMat4("model", model);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glDrawArrays(GL_TRIANGLES, 0, 6);

}

void ShadowFirstPass(Shader* shader, ModelContainer *ben, ModelContainer *sean, ModelContainer *isa, ModelContainer *ziming, ModelContainer *wayne, unsigned int grid_VAOs[], Grid mainGrid, Model *terrain)
{
	// Render Depth of Scene to Texture (from the light's perspective)
	lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
	lightView = glm::lookAt(activeLightSource, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
	lightSpaceMatrix = lightProjection * lightView;
	
	// Start Using Depth Shader
	shader->use();
	shader->setMat4("lightSpaceMatrix", lightSpaceMatrix);
	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);
	
	// Rendering Models and Grid with the DepthShader
	RenderScene(shader, ben, sean, isa, ziming, wayne, terrain);
	RenderGrid(shader, grid_VAOs, mainGrid);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ShadowSecondPass(Shader* shader, ModelContainer *ben, ModelContainer *sean, ModelContainer *isa, ModelContainer *ziming, ModelContainer *wayne, unsigned int grid_VAOs[], Grid mainGrid, Model *terrain)
{
	// Render Scene as Normal using the Generated Depth/Shadow map  
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Set the Light Uniforms
	shader->use();
	shader->setVec3("viewPos", camera.position);
	shader->setVec3("lightPos", activeLightSource);
	shader->setMat4("lightSpaceMatrix", lightSpaceMatrix);
	glActiveTexture(GL_TEXTURE11);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	
	// Rendering Models and Grid with modelShader
	RenderScene(shader, ben, sean, isa, ziming, wayne,terrain);
	RenderGrid(shader, grid_VAOs, mainGrid);
	glActiveTexture(GL_TEXTURE11);
	glBindTexture(GL_TEXTURE_2D, depthMap);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	WINDOW_WIDTH = width;
	WINDOW_HEIGHT = height;
	glViewport(0, 0, width, height);
}


// utility function for loading a 2D texture from file CREDIT - https://learnopengl.com/Advanced-OpenGL/Cubemaps
// ---------------------------------------------------
unsigned int loadTexture(char const * path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

unsigned int loadCubemap(std::vector<std::string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}

void loadSkybox(Shader &skyboxShader)
{
	// skybox START // Credit - https://learnopengl.com/Advanced-OpenGL/Cubemaps
	float skyboxVertices[] = {
		// positions          
		-35.7f,  35.7f, -35.7f,
		-35.7f, -35.7f, -35.7f,
		 35.7f, -35.7f, -35.7f,
		 35.7f, -35.7f, -35.7f,
		 35.7f,  35.7f, -35.7f,
		-35.7f,  35.7f, -35.7f,

		-35.7f, -35.7f,  35.7f,
		-35.7f, -35.7f, -35.7f,
		-35.7f,  35.7f, -35.7f,
		-35.7f,  35.7f, -35.7f,
		-35.7f,  35.7f,  35.7f,
		-35.7f, -35.7f,  35.7f,

		 35.7f, -35.7f, -35.7f,
		 35.7f, -35.7f,  35.7f,
		 35.7f,  35.7f,  35.7f,
		 35.7f,  35.7f,  35.7f,
		 35.7f,  35.7f, -35.7f,
		 35.7f, -35.7f, -35.7f,

		-35.7f, -35.7f,  35.7f,
		-35.7f,  35.7f,  35.7f,
		 35.7f,  35.7f,  35.7f,
		 35.7f,  35.7f,  35.7f,
		 35.7f, -35.7f,  35.7f,
		-35.7f, -35.7f,  35.7f,

		-35.7f,  35.7f, -35.7f,
		 35.7f,  35.7f, -35.7f,
		 35.7f,  35.7f,  35.7f,
		 35.7f,  35.7f,  35.7f,
		-35.7f,  35.7f,  35.7f,
		-35.7f,  35.7f, -35.7f,

		-35.7f, -35.7f, -35.7f,
		-35.7f, -35.7f,  35.7f,
		 35.7f, -35.7f, -35.7f,
		 35.7f, -35.7f, -35.7f,
		-35.7f, -35.7f,  35.7f,
		 35.7f, -35.7f,  35.7f
	};
	// skybox VAO

	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	// load textures
	// -------------
	stbi_set_flip_vertically_on_load(false);

	std::vector<std::string> faces
	{
		"comp371/assignment1/src/Resources/skybox/desert_1/right.png",
		"comp371/assignment1/src/Resources/skybox/desert_1/left.png",
		"comp371/assignment1/src/Resources/skybox/desert_1/top.png",
		"comp371/assignment1/src/Resources/skybox/desert_1/bottom.png",
		"comp371/assignment1/src/Resources/skybox/desert_1/front.png",
		"comp371/assignment1/src/Resources/skybox/desert_1/back.png"
	};
	cubemapTexture = loadCubemap(faces);

	skyboxShader.use();
	skyboxShader.setInt("skybox", 0);

	// skybox END
}

void drawSkybox(Shader &skyboxShader)
{
	// draw skybox as last
	glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
	skyboxShader.use();
	view = glm::mat4(glm::mat3(camera.calculateViewMatrix())); // remove translation from the view matrix
	skyboxShader.setMat4("view", view);
	skyboxShader.setMat4("projection", projection);
	// skybox cube
	glBindVertexArray(skyboxVAO);
	glActiveTexture(GL_TEXTURE12);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS); // set depth function back to default
}

float distanceFromCamera(glm::vec3 cameraPos, AABB aabb)
{
	float sqDist = 0.0f;
	float cameraPositions[3] = { cameraPos.x, cameraPos.y, cameraPos.z };

	for (int i = 0; i < 3; i++)
	{
		// For each axis, count any excess distance outside box extents
		float cameraVector = cameraPositions[i];

		if (cameraVector < aabb.min[i])
		{
			sqDist += (aabb.min[i] - cameraVector) * (aabb.min[i] - cameraVector);
		}
		else if (cameraVector > aabb.max[i])
		{
			sqDist += (cameraVector - aabb.max[i]) * (cameraVector - aabb.max[i]);
		}
	}

	return glm::sqrt(sqDist);
}

// TODO: If performance is taking a hit after all additional models are added. This method should only calculate collision for models close to the camera
// TODO: Check asimp imports
bool checkCollision(ModelContainer** models)
{
	bool collisionDetected = false;

	// Check our models (letters and numbers)
	for (int i = 0; i < 5; i++)
	{
		// Check if Number has collision
		collisionDetected ? true : collisionDetected = distanceFromCamera(camera.position, models[i]->models[0]->getAABB()) < 0.2f ? true : false;

		// Check if Letter has collision
		collisionDetected ? true : collisionDetected = distanceFromCamera(camera.position, models[i]->models[1]->getAABB()) < 0.2f ? true : false;
	}

	return collisionDetected;
}