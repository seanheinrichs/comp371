/*
	COMP 371 - Section CC
	Practical Assignment #2
	Written By:
		Benjamin Therien (40034572)
		Sean Heinrichs (40075789)
		Wayne Huras (40074423)
		Isabelle Gourchette (40008121)
		Ziming Wang (40041601)
	Due:  July 27th, 2020
*/


/*
Info for spheres
place Assets/Models/planet.obj is same directory as solutions file
add
_SCL_SECURE_NO_WARNINGS
_CRT_SECURE_NO_WARNINGS
in properties/ C/C++ / Prepocessor / Proprocessor Definitions
Info for shear:
in main: #include <glm/gtx/transform2.hpp>
*/

#define _SCL_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>

#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL

#include "Objects/geometry/Polygon.h"
#include "Objects/Grid.hpp"
#include "Objects/Camera.h"
#include "Objects/PointLight.h"
#include "modeling/OurModels.cpp"
#include "utils/GL_Error.h"
#include "utils/objloader.cpp"
#include "Opengl_a/Shader.h"
#include "Common.h"

#include <GL/glew.h>    
#include <GLFW/glfw3.h> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform2.hpp>

#define GLFW_REFRESH_RATE 60
#define	GLFW_DOUBLEBUFFER GLFW_TRUE

/* Function Declarations */
void processInput(GLFWwindow *window, ModelContainer** models, PointLight** pointLights);
void setModelColor(int modelIndex, Shader* modelShader);
void cursorPositionCallback(GLFWwindow * window, double xPos, double yPos);
void setupTextureMapping();
void setModelColor(int modelIndex, Shader * modelShader);
float RandomFloat(float a, float b);
void RenderScene(Shader* shader, ModelContainer *ben, ModelContainer *sean, ModelContainer *isa, ModelContainer *ziming, ModelContainer *wayne, Model* sphereModel);
void RenderGrid(Shader* shader, unsigned int grid_VAOs[], Grid mainGrid);
void RenderAxes(Shader* shader, unsigned int grid_VAOs[], Model *light);
void ShadowFirstPass(Shader* shader, ModelContainer *ben, ModelContainer *sean, ModelContainer *isa, ModelContainer *ziming, ModelContainer *wayne, Model* sphereModel, unsigned int grid_VAOs[], Grid mainGrid);
void ShadowSecondPass(Shader* shader, ModelContainer *ben, ModelContainer *sean, ModelContainer *isa, ModelContainer *ziming, ModelContainer *wayne, Model* sphereModel, unsigned int grid_VAOs[], Grid mainGrid);

/* Global Constants */
const unsigned int WINDOW_WIDTH = 1024;
const unsigned int WINDOW_HEIGHT = 768;
const unsigned int SHADOW_WIDTH = 1024;
const unsigned int SHADOW_HEIGHT = 1024;

/* Camera Setup */
Camera camera = Camera(glm::vec3(0.0f, 0.3f, 2.0f), glm::vec3(0.0f, 0.0f, -2.0f), glm::vec3(0.0f, 1.0f, 0.0f));
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Initialize variables used for rotations
float previousXPos = WINDOW_WIDTH / 2.0f;
float previousYPos = WINDOW_HEIGHT / 2.0f;
float xOffset = 0.0f;
float yOffset = 0.0f;
float rX = 0.0f;
float rY = 0.0f;

// Variables used for light and shadows
unsigned int depthMapFBO;
unsigned int depthMap;
float near_plane = 0.1f, far_plane = 100.0f;
glm::mat4 lightSpaceMatrix(1.0f);
glm::mat4 lightProjection(1.0f);
glm::mat4 lightView(1.0f);

//globals used for selecting render mode and models
GLenum MODE = GL_TRIANGLES;
int selected = 0;
int useTextures = 1;
bool useShadows = true;
glm::vec3 activeLightSource(0.0f, 3.0f, -0.1f);

/* External linkage for global varibles */
GLenum* g_texLocations = new GLenum[32];
Texture* g_textures = new Texture[32];
float *g_shininess = new float[32];
glm::vec3 *g_specularStrength = new glm::vec3[32];

int main(void)
{
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

	glfwMakeContextCurrent(window);
	glfwSetCursorPosCallback(window, cursorPositionCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);

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
	Shader modelShader("comp371/assignment1/src/Shaders/modelShader.vertex", "comp371/assignment1/src/Shaders/modelShader.fragment");
	Shader lightShader("comp371/assignment1/src/Shaders/lightShader.vertex", "comp371/assignment1/src/Shaders/lightShader.fragment");
	Shader depthShader("comp371/assignment1/src/Shaders/shadow_mapping_depth.vertex", "comp371/assignment1/src/Shaders/shadow_mapping_depth.fragment");

	setupTextureMapping();
	
	// [Models]

	//obj loader
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs; //not used yet?
	std::vector<glm::vec3> normals; // not used?
	bool res = loadOBJ("../Assets/Models/planet.obj", vertices, uvs, normals);

	Model * sphereModel = new Model(true, false, false, false, "sphere");
	createShape(sphereModel, vertices, uvs, normals);
	sphereModel->bindArrayBuffer(true, sphereModel);

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

	// [Point Light]

	PointLight* bensPL = new PointLight(light, glm::vec3(0.0f, 3.0f, -0.1f), true);
	PointLight* seansPL = new PointLight(light, glm::vec3(3.5f, 3.0f, -4.0f), false);
	PointLight* waynesPL = new PointLight(light, glm::vec3(-4.0f, 3.0f, -4.0f), false);
	PointLight* isasPL = new PointLight(light, glm::vec3(3.5f, 3.0f, 4.0f), false);
	PointLight* zimingsPL = new PointLight(light, glm::vec3(-4.0f, 3.0f, 4.0f), false);

	// [Grid]

	Grid mainGrid = Grid();

	unsigned int grid_VAOs[3], grid_VBOs[3], grid_EBO;
	GLCall(glGenVertexArrays(3, grid_VAOs));
	GLCall(glGenBuffers(3, grid_VBOs));
	GLCall(glGenBuffers(1, &grid_EBO));

	// [Grid Mesh] 
	GLCall(glBindVertexArray(grid_VAOs[0]));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, grid_VBOs[0]));
	GLCall(glBufferData(GL_ARRAY_BUFFER, mainGrid.meshVertices.size() * sizeof(glm::vec3), &mainGrid.meshVertices.front(), GL_STATIC_DRAW));
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
	GLCall(glEnableVertexAttribArray(0));

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

	// [Coordinate Axis]
	GLCall(glBindVertexArray(grid_VAOs[2]));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, grid_VBOs[2]));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(mainGrid.axisVertices), mainGrid.axisVertices, GL_STATIC_DRAW));
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0));
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))));
	GLCall(glEnableVertexAttribArray(1));

	PointLight** pointLights = new PointLight*[5];
	pointLights[0] = bensPL;
	pointLights[1] = seansPL;
	pointLights[2] = isasPL;
	pointLights[3] = zimingsPL;
	pointLights[4] = waynesPL;

	ModelContainer** models = new ModelContainer*[5];
	models[0] = ben;
	models[1] = sean;
	models[2] = isa;
	models[3] = ziming;
	models[4] = wayne;

	ben->addScale(glm::vec3(0.2f, 0.2f, 0.2f));
	ben->addTranslation(glm::vec3(0.0f, 0.0f, 0.0f));

	sean->addScale(glm::vec3(0.2f, 0.2f, 0.2f));
	sean->addTranslation(glm::vec3(3.5f, 0.0f, -4.0f));

	wayne->addScale(glm::vec3(0.2f, 0.2f, 0.2f));
	wayne->addTranslation(glm::vec3(-4.0f, 0.0f, -4.0f));

	isa->addScale(glm::vec3(0.2f, 0.2f, 0.2f));
	isa->addTranslation(glm::vec3(3.5f, 0.0f, 4.0f));

	ziming->addScale(glm::vec3(0.2f, 0.2f, 0.2f));
	ziming->addTranslation(glm::vec3(-4.0f, 0.0f, 4.0f));

	light->addScale(glm::vec3(0.1f, 0.1f, 0.1f));
	light->addTranslation(glm::vec3(0.0f, 3.0f, -1.0f));

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

	// Main Loop 
	while (!glfwWindowShouldClose(window))
	{
		// Set frame for Camera (taken from LearnOpenGL)
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Event Handling
		processInput(window, models, pointLights);

		// Render
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		// Start Using Model Shader
		modelShader.use();
		modelShader.setInt("useTextures", useTextures);
		modelShader.setBool("useShadows", useShadows);
		modelShader.setVec3("viewPos", camera.position);

		// Set Light Properties
		for (int i = 0; i < 5; i++)
		{
			if (pointLights[i]->getActive())
			{
				pointLights[i]->setShaderValues(&modelShader);
			}
		}

		// Recompute Camera Pipeline
		glm::mat4 model;
		modelShader.setMat4("model", model);

		glm::mat4 projection = glm::perspective(glm::radians(camera.fieldOfViewAngle), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
		modelShader.setMat4("projection", projection);

		glm::mat4 view = camera.calculateViewMatrix();
		view = glm::rotate(view, glm::radians(rX), glm::vec3(0.0f, 0.0f, -1.0f));
		view = glm::rotate(view, glm::radians(rY), glm::vec3(-1.0f, 0.0f, 0.0f));
		modelShader.setMat4("view", view);



		// Render Scene with shadowmap to calculate shadows with depthShader (1ST PASS)
		ShadowFirstPass(&depthShader, ben, sean, isa, ziming, wayne, sphereModel, grid_VAOs, mainGrid);
		
		// Reset Viewport
		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Render Scene as normal using the generated depth/shadowmap with modelShader(2ND PASS)
		ShadowSecondPass(&modelShader, ben, sean, isa, ziming, wayne, sphereModel, grid_VAOs, mainGrid);

		// [Objects Not Affected by Light Source]

		// Start Using Lighting Shader
		lightShader.use();
		lightShader.setMat4("projection", projection);
		lightShader.setMat4("view", view);
		
		// [Lamps]
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

		// Rendering 5x5 XYZ Axes
		RenderAxes(&lightShader, grid_VAOs, light);

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
	sphereModel->deallocate();

	// Terminate Program 
	glfwTerminate();
	return 0;
}

// Event handling functions
void processInput(GLFWwindow *window, ModelContainer** models, PointLight** pointLights)
{

	float cameraSpeed = 1.0 * deltaTime;

	// [Camera FPS Movement]

	// Press "G" to move FORWARD
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
	{
		camera.moveForward(cameraSpeed);
	}

	// Press "V" to move BACKWARDS
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
	{
		camera.moveBackward(cameraSpeed);
	}

	// Press "C" to move LEFT
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
	{
		camera.moveLeft(cameraSpeed);
	}

	// // Press "B" to move RIGHT
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
	{
		camera.moveRight(cameraSpeed);
	}

	// [World Rotation]

	// Press "LEFT ARROW" to rotate about the positive x-axis in a anti-clockwise direction
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		rX += 0.5f;
	}

	// Press "RIGHT ARROW" to rotate about the negative x-axis in a anti-clockwise direction
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		rX -= 0.5f;
	}

	// Press "UP ARROW" to rotate about the positive y-axis in a anti-clockwise direction
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		rY -= 0.5f;
	}

	// Press "DOWN ARROW" to rotate about the negative y-axis in a anti-clockwise direction
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		rY += 0.5f;
	}

	// Press "HOME" to reset to initial world position
	if (glfwGetKey(window, GLFW_KEY_HOME) == GLFW_PRESS)
	{
		rY = 0;
		rX = 0;
	}

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

	// Press "1" to select MODEL 0 (N 3)
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && (selected != 0 ))
	{
		selected = 0;
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
	
	// Press "2" to select MODEL 1 (A 7)
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS && (selected != 1))
	{
		selected = 1;
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
	
	// Press "3" to select MODEL 2 (A 0)
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS && (selected != 2))
	{
		selected = 2;
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
	
	// Press "4" to select MODEL 3 (M 4)
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS && (selected != 3))
	{
		selected = 3;
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
	
	// Press "5" to select MODEL 4 (Y 7)
	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS && (selected != 4))
	{
		selected = 4;
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

	// [Translation]
	
	// Press "SHIFT + A" to move the selected model to the LEFT
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
	{	
		models[selected]->addTranslation(glm::vec3(-0.1f,0.0f,0.0f));
	}

	// Press "SHIFT + D" to move the selected model to the RIGHT
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
	{
		models[selected]->addTranslation(glm::vec3(0.1f, 0.0f, 0.0f));
	}

	// Press "SHIFT + W" to move the selected model UP
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
	{
		models[selected]->addTranslation(glm::vec3(0.0f, 0.1f, 0.0f));
	}

	// Press "SHIFT + S" to move the selected model DOWN
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
	{
		models[selected]->addTranslation(glm::vec3(0.0f, -0.1f, 0.0f));
	}

	// Press "SHIFT + S" to move the selected model DOWN
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS && (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
	{
		models[selected]->addTranslation(glm::vec3(0.0f, 0.0f, -0.1f));
	}

	// Press "SHIFT + S" to move the selected model DOWN
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS && (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
	{
		models[selected]->addTranslation(glm::vec3(0.0f, 0.0f, 0.1f));
	}

	// [Rotation]
	
	// Press 'A' to rotate the model to the left 5 degrees about y-axis
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && !(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
	{
		models[selected]->addRotation(5.0f,glm::vec3(0.0f, 1.0f, 0.0f));
	}

	// Press 'D' to rotate the model to the right 5 degrees about y-axis
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && !(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
	{
		models[selected]->addRotation(-5.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	// [Scale]
	
	// Press 'U' to scale UP the model
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
	{
		models[selected]->addScale(glm::vec3(0.1f, 0.1f, 0.1f));
	}

	// Press 'J' to scale DOWN the model
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
	{
		models[selected]->addScale(glm::vec3(-0.01f, -0.01f, -0.01f));
	}

	// [Shearing]

	// Press 'P' to shear
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && !(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
	{
		models[selected]->addShearX(glm::vec2(0.0f,0.02f));
		models[selected]->addRotation(0, glm::vec3(0.0f, 0.0f, 0.0f));
		//models[selected]->addScale(glm::vec3(0.01f, 0.0f, 0.0f));
	}

	// Press 'O' to shear
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS && !(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
	{
		models[selected]->addShearX(glm::vec2(-0.00f,-0.02f));
		//models[selected]->addScale(glm::vec3(-0.01f, 0.0f, 0.0f));
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
	if (!useShadows && glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS && (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
	{
		useShadows = true;
	}

	// Press 'SHIFT + X' to turn textures ON
	if (useShadows && glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS && !(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
	{
		useShadows = false;
	}
  
	// Press 'SPACE' to re-position the model at a random location on the grid
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		float a = -5.0f;
		float b = 5.0f;
		float x = RandomFloat(a, b);
		float z = RandomFloat(a, b);
		models[selected]->Reposition(glm::vec3(x, 0.0f, z));
	}

	// Press 'BACKSPACE' to reset to original position
	if (glfwGetKey(window, GLFW_KEY_BACKSPACE) == GLFW_PRESS)
	{
		if (selected == 0) {
			models[selected]->Reposition(glm::vec3(0.0f, 0.0f, -1.0f));
		}
		else if (selected == 1) {
			models[selected]->Reposition(glm::vec3(3.5f, 0.0f, -4.0f));
		}
		else if (selected == 2) {
			models[selected]->Reposition(glm::vec3(3.5f, 0.0f, 4.0f));
		}
		else if (selected == 3) {
			models[selected]->Reposition(glm::vec3(-4.0f, 0.0f, 4.0f));
		}
		else if (selected == 4) {
			models[selected]->Reposition(glm::vec3(-4.0f, 0.0f, -4.0f));
		}
	}
}

//Method to generate random float between a & b
float RandomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

void setModelColor(int modelIndex, Shader* modelShader)
{
	selected == modelIndex ? modelShader->setVec3("modelColor", 0.6f, 0.0f, 0.8f) : modelShader->setVec3("modelColor", 0.75f, 0.75f, 0.75f);
}

void cursorPositionCallback(GLFWwindow * window, double xPos, double yPos)
{
	const float SENSITIVITY = 0.05f;

	xOffset = xPos - previousXPos;
	yOffset = previousYPos - yPos;

	previousXPos = xPos;
	previousYPos = yPos;

	// Limit speed of camera movement
	xOffset *= SENSITIVITY;
	yOffset *= SENSITIVITY;

	// Pan camera when holding the right mouse button
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		camera.panCamera(xOffset);
	}

	// Tilt camera when holding the middle mouse button
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS)
	{
		camera.tiltCamera(yOffset);
	}

	// Zoom camera when holding the left mouse button
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		camera.zoomCamera(yOffset);
	}
}

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
	//g_texLocations[11] = GL_TEXTURE11; // used by shadow map

	g_textures[0] = Texture("comp371/assignment1/src/Resources/bmv_2.png");
	g_textures[1] = Texture("comp371/assignment1/src/Resources/cast_iron.png");
	g_textures[2] = Texture("comp371/assignment1/src/Resources/chrome.png");
	g_textures[3] = Texture("comp371/assignment1/src/Resources/speaker_holes.png");
	g_textures[4] = Texture("comp371/assignment1/src/Resources/shiny_metal.png");
	g_textures[5] = Texture("comp371/assignment1/src/Resources/box1.png");
	g_textures[6] = Texture("comp371/assignment1/src/Resources/box2.png");
	g_textures[7] = Texture("comp371/assignment1/src/Resources/box3.png");
	g_textures[8] = Texture("comp371/assignment1/src/Resources/box4.png");
	g_textures[9] = Texture("comp371/assignment1/src/Resources/box5.png");
	g_textures[10] = Texture("comp371/assignment1/src/Resources/grid_floor.jpg");
	//g_textures[11] // used by shadow map

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
	//g_shininess[11] // used by shadow map

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
	//g_specularStrength[11] // used by shadow map
}

void RenderScene(Shader* shader, ModelContainer *ben, ModelContainer *sean, ModelContainer *isa, ModelContainer *ziming, ModelContainer *wayne, Model* sphereModel)
{
  //ben sphere
  sphereModel->bind();
  //	model = ben->getModelMatrix(false)*ben->getTranslationSphere();;
  glm:: mat4 model = ben->getModelMatrix();
  model = glm::scale(model, glm::vec3(1.25f, 1.25f, 1.25f));
  model = glm::translate(model, glm::vec3(0.0f, 4.0f, 0.0f));
  shader->setMat4("model", model);
  GLCall(glDrawArrays(GL_LINES, 0, sphereModel->getVAVertexCount()));
  
	ben->draw(MODE, shader);
	sean->draw(MODE, shader);
	isa->draw(MODE, shader);
	ziming->draw(MODE, shader);
	wayne->draw(MODE, shader);	
}

void RenderGrid(Shader* shader, unsigned int grid_VAOs[], Grid mainGrid)
{
	// [Grid Floor]

	GLCall(glBindVertexArray(grid_VAOs[1]));
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
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

void RenderAxes(Shader* shader, unsigned int grid_VAOs[], Model *light)
{
	// [Coordinate Axis]

	glLineWidth(5.0f);
	glBindVertexArray(grid_VAOs[2]);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.05f, 1.0f));
	shader->setMat4("model", model);
	shader->setInt("fill", 0);
	glDrawArrays(GL_LINES, 0, 6);
	glLineWidth(1.0f);
}

void ShadowFirstPass(Shader* shader, ModelContainer *ben, ModelContainer *sean, ModelContainer *isa, ModelContainer *ziming, ModelContainer *wayne, Model* sphereModel, unsigned int grid_VAOs[], Grid mainGrid)
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
	RenderScene(shader, ben, sean, isa, ziming, wayne, sphereModel);
	RenderGrid(shader, grid_VAOs, mainGrid);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ShadowSecondPass(Shader* shader, ModelContainer *ben, ModelContainer *sean, ModelContainer *isa, ModelContainer *ziming, ModelContainer *wayne, Model* sphereModel, unsigned int grid_VAOs[], Grid mainGrid)
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
	RenderScene(shader, ben, sean, isa, ziming, wayne, sphereModel);
	RenderGrid(shader, grid_VAOs, mainGrid);
	glActiveTexture(GL_TEXTURE11);
	glBindTexture(GL_TEXTURE_2D, depthMap);
}