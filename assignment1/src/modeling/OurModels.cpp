#include "../Objects/geometry/Cube.h"
#include "../Objects/geometry/Model.h"
#include "../Objects/geometry/ModelContainer.h"
#include "../Opengl_a/Shader.h"
#include <glm/gtc/matrix_transform.hpp>

/* Static methods to create our Models */
static void createSeansModel(ModelContainer* modelContainer, Shader* shader)
{
	glm::mat4 scale;
	glm::mat4 rotate;
	
	// [Create A Model]
	Model* A = new Model(true, true, false, false, "a", shader, 5);
	
	Cube* cb1 = new Cube(glm::vec3(-1.0, 0.5, 0.0));
	Cube* cb2 = new Cube(glm::vec3(-2.0, 2.5, 0.0));
	Cube* cb3 = new Cube(glm::vec3(-2.0, 4.5, 0.0));
	Cube* cb4 = new Cube(glm::vec3(-3.0, 0.5, 0.0));

	// Create 1x4 columns
	scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 5.0f, 1.0f));
	cb1->transform(scale);
	cb4->transform(scale);

	A->addPolygon(cb1);
	A->addPolygon(cb2);
	A->addPolygon(cb3);
	A->addPolygon(cb4);
	
	// [Create 7 Model]
	Model* seven = new Model(true, true, false, false, "7", shader, 0);

	Cube * cb5 = new Cube(glm::vec3(1.0f, 2.0f, 0.0f));
	Cube * cb6 = new Cube(glm::vec3(2.0f, 4.5f, 0.0f));
	Cube * cb7 = new Cube(glm::vec3(3.0f, 0.5f, 0.0f));

	// Create 1x4 column
	scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 5.0f, 1.0f));
	cb7->transform(scale);

	// Create 1x2 column
	scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 2.0f, 1.0f));
	cb5->transform(scale);

	seven->addPolygon(cb5);
	seven->addPolygon(cb6);
	seven->addPolygon(cb7);

	// Set initial position
	rotate = glm::rotate(glm::mat4(1.0f), glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	A->transform(rotate);
	seven->transform(rotate);

	// Add to model container
	modelContainer->addModel(A);
	modelContainer->addModel(seven);
}

static void createWaynesModel(ModelContainer* modelContainer, Shader* shader)
{
	// [Create Y Model]
	Model* Y = new Model(true, true, false, false, "y", shader, 6);

	Cube *cb1 = new Cube(glm::vec3(0.0f, 0.0f, 0.0f));
	glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(-3.5f, 0.5f, 0.0f));
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 1.0f, 1.0f));
	glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0));
	glm::mat4 transform = translate * rotate * scale;
	cb1->transform(transform);

	Cube *cb2 = new Cube(glm::vec3(0.0f, 0.0f, 0.0f));
	translate = glm::translate(glm::mat4(1.0f), glm::vec3(-3.5f, 1.5f, 0.0f));
	scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 3.0f, 1.0f));
	rotate = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0));
	transform = translate * rotate * scale;
	cb2->transform(transform);

	Cube *cb3 = new Cube(glm::vec3(0.0f, 0.0f, 0.0f));
	translate = glm::translate(glm::mat4(1.0f), glm::vec3(-2.85f, 3.5f, 0.0f));
	scale = glm::scale(glm::mat4(1.0f), glm::vec3(3.0f, 1.0f, 1.0f));
	rotate = glm::rotate(glm::mat4(1.0f), glm::radians(65.0f), glm::vec3(0.0f, 0.0f, 1.0));
	transform = translate * rotate * scale;
	cb3->transform(transform);

	Cube *cb4 = new Cube(glm::vec3(0.0f, 0.0f, 0.0f));
	translate = glm::translate(glm::mat4(1.0f), glm::vec3(-4.15f, 3.5f, 0.0f));
	scale = glm::scale(glm::mat4(1.0f), glm::vec3(3.0f, 1.0f, 1.0f));
	rotate = glm::rotate(glm::mat4(1.0f), glm::radians(-65.0f), glm::vec3(0.0f, 0.0f, 1.0));
	transform = translate * rotate * scale;
	cb4->transform(transform);

	Cube *cb5 = new Cube(glm::vec3(0.0f, 0.0f, 0.0f));
	translate = glm::translate(glm::mat4(1.0f), glm::vec3(-4.75f, 5.0f, 0.0f));
	scale = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 1.0f, 1.0f));
	rotate = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0));
	transform = translate * rotate * scale;
	cb5->transform(transform);

	Cube *cb6 = new Cube(glm::vec3(0.0f, 0.0f, 0.0f));
	translate = glm::translate(glm::mat4(1.0f), glm::vec3(-2.25f, 5.0f, 0.0f));
	scale = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 1.0f, 1.0f));
	rotate = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0));
	transform = translate * rotate * scale;
	cb6->transform(transform);

	Y->addPolygon(cb1);
	Y->addPolygon(cb2);
	Y->addPolygon(cb3);
	Y->addPolygon(cb4);
	Y->addPolygon(cb5);
	Y->addPolygon(cb6);

	// [Create 7 Model]
	Model* seven = new Model(true, true, false, false, "7", shader, 1);

	Cube *cb7 = new Cube(glm::vec3(0.0f, 0.0f, 0.0f));
	translate = glm::translate(glm::mat4(1.0f), glm::vec3(1.90f, 2.25f, 0.0f));
	scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 4.5f, 1.0f));
	rotate = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0));
	glm::mat4 skew(1.0f);
	skew = {
		1.0, 0.0, 0.0, 0.0,
		0.46630765, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0
	};
	transform = skew * translate * rotate * scale;
	cb7->transform(transform);

	Cube *cb8 = new Cube(glm::vec3(0.0f, 0.0f, 0.0f));
	translate = glm::translate(glm::mat4(1.0f), glm::vec3(2.5f, 5.0f, 0.0f));
	scale = glm::scale(glm::mat4(1.0f), glm::vec3(4.0f, 1.0f, 1.0f));
	rotate = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0));
	transform = translate * rotate * scale;
	cb8->transform(transform);

	Cube *cb9 = new Cube(glm::vec3(0.0f, 0.0f, 0.0f));
	translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 4.5f, 0.0f));
	scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 2.0f, 1.0f));
	rotate = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0));
	transform = translate * rotate * scale;
	cb9->transform(transform);

	// 7 model
	seven->addPolygon(cb7);
	seven->addPolygon(cb8);
	seven->addPolygon(cb9);

	// Set initial position
	rotate = glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	Y->transform(rotate);
	seven->transform(rotate);

	// Add to model container
	modelContainer->addModel(Y);
	modelContainer->addModel(seven);
}

static void createBensModel(ModelContainer* modelContainer, Shader* shader)
{
	Model* three = new Model(true, true, false, false, "3", shader, 2);

	three->addPolygon(new Cube(glm::vec3(6.0f, 3.5f, 0.0f)));
	three->addPolygon(new Cube(glm::vec3(6.5f, 3.5f, 0.0f)));
	three->addPolygon(new Cube(glm::vec3(7.0f, 3.5f, 0.0f)));
	three->addPolygon(new Cube(glm::vec3(6.0f, 2.0f, 0.0f)));
	three->addPolygon(new Cube(glm::vec3(6.5f, 2.0f, 0.0f)));
	three->addPolygon(new Cube(glm::vec3(7.0f, 2.0f, 0.0f)));
	three->addPolygon(new Cube(glm::vec3(6.0f, 0.5f, 0.0f)));
	three->addPolygon(new Cube(glm::vec3(6.5f, 0.5f, 0.0f)));
	three->addPolygon(new Cube(glm::vec3(7.0f, 0.5f, 0.0f)));

	three->addPolygon(new Cube(glm::vec3(7.5f, 1.0f, 0.0f)));
	three->addPolygon(new Cube(glm::vec3(7.5f, 3.0f, 0.0f)));
	three->transform(glm::translate(glm::mat4(1.0f), glm::vec3(-5.0f, 0.0f, 0.0f)));

	Cube *cb = new Cube(glm::vec3(9.125f, 0.5f, 0.0f));
	Cube *cb1 = new Cube(glm::vec3(6.825f, 0.5f, 0.0f));
	Cube *cb2 = new Cube(glm::vec3(1.0f, 0.0f, 0.0f));
	
	glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(7.2f, 1.5f, 0.0f));
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 4.0f, 1.0f));
	glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(35.0f), glm::vec3(0.0f, 0.0f, 1.0));
	glm::mat4 transform = translate * rotate * scale;

	cb->transform(scale);
	cb1->transform(scale);
	cb2->transform(transform);
	Model* N = new Model(true, true, false, false, "n", shader, 7);
	N->addPolygon(cb);
	N->addPolygon(cb1);
	N->addPolygon(cb2);
	N->transform(glm::translate(glm::mat4(1.0f), glm::vec3(-10.0f, 0.0f, 0.0f)));

	modelContainer->addModel(N);
	modelContainer->addModel(three);
}

static void createIsabellesModel(ModelContainer* modelContainer, Shader* shader)
{
	glm::mat4 scale;
	glm::mat4 rotate;
	
	// [Create A Model]
	Model* A = new Model(true, true, false, false, "a", shader, 8);

	Cube * cube1 = new Cube(glm::vec3(-1.0f, 0.5f, 0.0f));
	Cube * cube2 = new Cube(glm::vec3(-2.0f, 2.5f, 0.0f));
	Cube * cube3 = new Cube(glm::vec3(-3.0f, 0.5f, 0.0f));
	Cube * cube4 = new Cube(glm::vec3(-2.0f, 4.5f, 0.0f));

	scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 5.0f, 1.0f));
	cube1->transform(scale);
	cube3->transform(scale);

	A->addPolygon(cube1);
	A->addPolygon(cube2);
	A->addPolygon(cube3);
	A->addPolygon(cube4);

	// [Create 0 Model]
	Model* zero = new Model(true, true, false, false, "0", shader, 3);

	Cube * cube5 = new Cube(glm::vec3(1.0f , 0.5f, 0.0f));
	Cube * cube6 = new Cube(glm::vec3(2.0f, 0.5f, 0.0f));
	Cube * cube7 = new Cube(glm::vec3(3.0f, 0.5f, 0.0f));
	Cube * cube8 = new Cube(glm::vec3(2.0f, 4.5f, 0.0f));

	cube5->transform(scale);
	cube7->transform(scale);

	zero->addPolygon(cube5);
	zero->addPolygon(cube6);
	zero->addPolygon(cube7);
	zero->addPolygon(cube8);

	// Set initial position
	rotate = glm::rotate(glm::mat4(1.0f), glm::radians(225.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	A->transform(rotate);
	zero->transform(rotate);

	// Add to model container
	modelContainer->addModel(A);
	modelContainer->addModel(zero);
}

static void createZimingsModel(ModelContainer* modelContainer, Shader* shader)
{
	glm::mat4 scale;
	glm::mat4 rotate;
	
	// [Create M Model]
	Model* M = new Model(true, true, false, false, "m", shader, 9);

	Cube * cb1 = new Cube(glm::vec3(-5.0f, 0.5f, 0.0f));
	Cube * cb2 = new Cube(glm::vec3(-4.0f, 3.5f, 0.0f));
	Cube * cb3 = new Cube(glm::vec3(-3.0f, 0.5f, 0.0f));
	Cube * cb4 = new Cube(glm::vec3(-2.0f, 3.5f, 0.0f));
	Cube * cb5 = new Cube(glm::vec3(-1.0f, 0.5f, 0.0f));

	// Create 1x4 columns
	scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 4.0f, 1.0f));
	cb1->transform(scale);
	cb3->transform(scale);
	cb5->transform(scale);

	M->addPolygon(cb1);
	M->addPolygon(cb2);
	M->addPolygon(cb3);
	M->addPolygon(cb4);
	M->addPolygon(cb5);

	// [Create 4 Model]
	Model* four = new Model(true, true, false, false, "4", shader, 4);

	Cube * cb6 = new Cube(glm::vec3(1.0f, 0.83f, 0.0f)); 
	Cube * cb7 = new Cube(glm::vec3(2.0f, 1.5f, 0.0f));
	Cube * cb8 = new Cube(glm::vec3(3.0f, 0.5f, 0.0f)); 
	Cube * cb9 = new Cube(glm::vec3(4.0f, 1.5f, 0.0f));

	// Create 1x3 columns
	scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 3.0f, 1.0f));
	cb6->transform(scale);

	// Create 1x4 columns
	scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 4.0f, 1.0f));
	cb8->transform(scale);

	four->addPolygon(cb6);
	four->addPolygon(cb7);
	four->addPolygon(cb8);
	four->addPolygon(cb9);

	// Set initial position
	rotate = glm::rotate(glm::mat4(1.0f), glm::radians(-225.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	M->transform(rotate);
	four->transform(rotate);

	// Add to model container
	modelContainer->addModel(M);
	modelContainer->addModel(four);
}

static void createLightModel(Model * model) {
	Cube * cb1 = new Cube(glm::vec3(0.0f, 0.0f, 0.0f));

	model->addPolygon(cb1);
}