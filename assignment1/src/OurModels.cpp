#include "Objects/geometry/Cube.h"
#include "Objects/geometry/Model.h"
#include <glm/gtc/matrix_transform.hpp>

/* Static methods to create our Models */
static void createSeansModel(Model * model)
{
	Cube * cb1 = new Cube(glm::vec3(-3.0f, 0.5f, 0.0f));
	Cube * cb2 = new Cube(glm::vec3(-1.0f, 0.5f, 0.0f));
	Cube * cb3 = new Cube(glm::vec3(3.0f, 0.5f, 0.0f));
	Cube * cb4 = new Cube(glm::vec3(1.0f, 2.0f, 0.0f));
	Cube * cb5 = new Cube(glm::vec3(-2.0f, 2.5f, 0.0f));
	Cube * cb6 = new Cube(glm::vec3(-2.0f, 4.5f, 0.0f));
	Cube * cb7 = new Cube(glm::vec3(2.0f, 4.5f, 0.0f));

	// Create 1x4 columns
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 5.0f, 1.0f));

	cb1->transform(scale);
	cb2->transform(scale);
	cb3->transform(scale);

	// Create 1x2 column
	scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 2.0f, 1.0f));

	cb4->transform(scale);

	model->addPolygon(cb1);
	model->addPolygon(cb2);
	model->addPolygon(cb3);
	model->addPolygon(cb4);
	model->addPolygon(cb5);
	model->addPolygon(cb6);
	model->addPolygon(cb7);

	// Set initial position
	glm::mat4 mat(1.0f);
	mat = glm::rotate(mat, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model->transform(mat);
}

static void createWaynesModel(Model * model)
{
	// Y model
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

	// 7 model
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

	Model * waynesModel = new Model(true, false, false);

	// Y model
	model->addPolygon(cb1);
	model->addPolygon(cb2);
	model->addPolygon(cb3);
	model->addPolygon(cb4);
	model->addPolygon(cb5);
	model->addPolygon(cb6);

	// 7 model
	model->addPolygon(cb7);
	model->addPolygon(cb8);
	model->addPolygon(cb9);

	// Set initial position
	glm::mat4 mat(1.0f);
	mat = glm::rotate(mat, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model->transform(mat);
}

static void createBensModel(Model* model)
{

	Model* three = new Model(true, false, false, true);

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
	Model* N = new Model(true, false, false, true);
	N->addPolygon(cb);
	N->addPolygon(cb1);
	N->addPolygon(cb2);
	N->transform(glm::translate(glm::mat4(1.0f), glm::vec3(-10.0f, 0.0f, 0.0f)));


	model->addPolygon(N);
	model->addPolygon(three);
}

static void createIsabellesModel(Model * model)
{
	//A
	Cube * cube1 = new Cube(glm::vec3(-1.0f, 0.5f, 0.0f));
	Cube * cube2 = new Cube(glm::vec3(-2.0f, 2.5f, 0.0f));
	Cube * cube3 = new Cube(glm::vec3(-3.0f, 0.5f, 0.0f));
	Cube * cube4 = new Cube(glm::vec3(-2.0f, 4.5f, 0.0f));

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 5.0f, 1.0f));
	cube1->transform(scale);
	cube3->transform(scale);
	model->addPolygon(cube1);
	model->addPolygon(cube2);
	model->addPolygon(cube3);
	model->addPolygon(cube4);

	//0
	Cube * cube5 = new Cube(glm::vec3(1.0f , 0.5f, 0.0f));
	Cube * cube6 = new Cube(glm::vec3(2.0f, 0.5f, 0.0f));
	Cube * cube7 = new Cube(glm::vec3(3.0f, 0.5f, 0.0f));
	Cube * cube8 = new Cube(glm::vec3(2.0f, 4.5f, 0.0f));

	cube5->transform(scale);
	cube7->transform(scale);
	model->addPolygon(cube5);
	model->addPolygon(cube6);
	model->addPolygon(cube7);
	model->addPolygon(cube8);

	// Set initial position
	glm::mat4 mat(1.0f);
	mat = glm::rotate(mat, glm::radians(225.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model->transform(mat);
}

static void createZimingsModel(Model * model)
{
	Cube * cb1 = new Cube(glm::vec3(-5.0f, 0.5f, 0.0f));
	Cube * cb2 = new Cube(glm::vec3(-5.0f, 1.5f, 0.0f));
	Cube * cb3 = new Cube(glm::vec3(-5.0f, 2.5f, 0.0f));
	Cube * cb4 = new Cube(glm::vec3(-5.0f, 3.5f, 0.0f));
	Cube * cb5 = new Cube(glm::vec3(-4.0f, 3.5f, 0.0f));
	Cube * cb6 = new Cube(glm::vec3(-3.0f, 0.5f, 0.0f));
	Cube * cb7 = new Cube(glm::vec3(-3.0f, 1.5f, 0.0f));
	Cube * cb8 = new Cube(glm::vec3(-3.0f, 2.5f, 0.0f));
	Cube * cb9 = new Cube(glm::vec3(-3.0f, 3.5f, 0.0f));
	Cube * cb10 = new Cube(glm::vec3(-2.0f, 3.5f, 0.0f));
	Cube * cb11 = new Cube(glm::vec3(-1.0f, 0.5f, 0.0f));
	Cube * cb12 = new Cube(glm::vec3(-1.0f, 1.5f, 0.0f));
	Cube * cb13 = new Cube(glm::vec3(-1.0f, 2.5f, 0.0f));
	Cube * cb14 = new Cube(glm::vec3(-1.0f, 3.5f, 0.0f));

	Cube * cb15 = new Cube(glm::vec3(1.0f, 1.5f, 0.0f));
	Cube * cb16 = new Cube(glm::vec3(1.0f, 2.5f, 0.0f));
	Cube * cb17 = new Cube(glm::vec3(1.0f, 3.5f, 0.0f));
	Cube * cb18 = new Cube(glm::vec3(2.0f, 1.5f, 0.0f));
	Cube * cb19 = new Cube(glm::vec3(3.0f, 0.5f, 0.0f));
	Cube * cb20 = new Cube(glm::vec3(3.0f, 1.5f, 0.0f));
	Cube * cb21 = new Cube(glm::vec3(3.0f, 2.5f, 0.0f));
	Cube * cb22 = new Cube(glm::vec3(3.0f, 3.5f, 0.0f));
	Cube * cb23 = new Cube(glm::vec3(4.0f, 1.5f, 0.0f));

	model->addPolygon(cb1);
	model->addPolygon(cb2);
	model->addPolygon(cb3);
	model->addPolygon(cb4);
	model->addPolygon(cb5);
	model->addPolygon(cb6);
	model->addPolygon(cb7);
	model->addPolygon(cb8);
	model->addPolygon(cb9);
	model->addPolygon(cb10);
	model->addPolygon(cb11);
	model->addPolygon(cb12);
	model->addPolygon(cb13);
	model->addPolygon(cb14);
	model->addPolygon(cb15);
	model->addPolygon(cb16);
	model->addPolygon(cb17);
	model->addPolygon(cb18);
	model->addPolygon(cb19);
	model->addPolygon(cb20);
	model->addPolygon(cb21);
	model->addPolygon(cb22);
	model->addPolygon(cb23);

	// Set initial position
	glm::mat4 mat(1.0f);
	mat = glm::rotate(mat, glm::radians(-225.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model->transform(mat);
}

static void createLightModel(Model * model) {
	Cube * cb1 = new Cube(glm::vec3(0.0f, 0.0f, 0.0f));

	model->addPolygon(cb1);
}