#include "../Objects/geometry/Shape.h"
#include "../Objects/geometry/Model.h"
#include "../Objects/geometry/ModelContainer.h"
#include "../Objects/geometry/Shape.h"
#include "../Opengl_a/Shader.h"
#include <glm/gtc/matrix_transform.hpp>


static void createShape(Model * model,
	std::vector<glm::vec3> & in_vertices,
	std::vector<glm::vec2> & in_uvs,
	std::vector<glm::vec3> & in_normals) {
	Shape * loadedShape = new Shape(glm::vec3(0.0f, 0.0f, 0.0f), in_vertices, in_uvs, in_normals);
	model->addPolygon(loadedShape);
}

/* Static methods to create our Models */
static void createSeansModel(Model * model)
{
	Shape * cb1 = new Shape(glm::vec3(-3.0f, 0.5f, 0.0f));
	Shape * cb2 = new Shape(glm::vec3(-1.0f, 0.5f, 0.0f));
	Shape * cb3 = new Shape(glm::vec3(3.0f, 0.5f, 0.0f));
	Shape * cb4 = new Shape(glm::vec3(1.0f, 2.0f, 0.0f));
	Shape * cb5 = new Shape(glm::vec3(-2.0f, 2.5f, 0.0f));
	Shape * cb6 = new Shape(glm::vec3(-2.0f, 4.5f, 0.0f));
	Shape * cb7 = new Shape(glm::vec3(2.0f, 4.5f, 0.0f));

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
	Shape *cb1 = new Shape(glm::vec3(0.0f, 0.0f, 0.0f));
	glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(-3.5f, 0.5f, 0.0f));
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 1.0f, 1.0f));
	glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0));
	glm::mat4 transform = translate * rotate * scale;
	cb1->transform(transform);

	Shape *cb2 = new Shape(glm::vec3(0.0f, 0.0f, 0.0f));
	translate = glm::translate(glm::mat4(1.0f), glm::vec3(-3.5f, 1.5f, 0.0f));
	scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 3.0f, 1.0f));
	rotate = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0));
	transform = translate * rotate * scale;
	cb2->transform(transform);

	Shape *cb3 = new Shape(glm::vec3(0.0f, 0.0f, 0.0f));
	translate = glm::translate(glm::mat4(1.0f), glm::vec3(-2.85f, 3.5f, 0.0f));
	scale = glm::scale(glm::mat4(1.0f), glm::vec3(3.0f, 1.0f, 1.0f));
	rotate = glm::rotate(glm::mat4(1.0f), glm::radians(65.0f), glm::vec3(0.0f, 0.0f, 1.0));
	transform = translate * rotate * scale;
	cb3->transform(transform);

	Shape *cb4 = new Shape(glm::vec3(0.0f, 0.0f, 0.0f));
	translate = glm::translate(glm::mat4(1.0f), glm::vec3(-4.15f, 3.5f, 0.0f));
	scale = glm::scale(glm::mat4(1.0f), glm::vec3(3.0f, 1.0f, 1.0f));
	rotate = glm::rotate(glm::mat4(1.0f), glm::radians(-65.0f), glm::vec3(0.0f, 0.0f, 1.0));
	transform = translate * rotate * scale;
	cb4->transform(transform);

	Shape *cb5 = new Shape(glm::vec3(0.0f, 0.0f, 0.0f));
	translate = glm::translate(glm::mat4(1.0f), glm::vec3(-4.75f, 5.0f, 0.0f));
	scale = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 1.0f, 1.0f));
	rotate = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0));
	transform = translate * rotate * scale;
	cb5->transform(transform);

	Shape *cb6 = new Shape(glm::vec3(0.0f, 0.0f, 0.0f));
	translate = glm::translate(glm::mat4(1.0f), glm::vec3(-2.25f, 5.0f, 0.0f));
	scale = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 1.0f, 1.0f));
	rotate = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0));
	transform = translate * rotate * scale;
	cb6->transform(transform);

	// 7 model
	Shape *cb7 = new Shape(glm::vec3(0.0f, 0.0f, 0.0f));
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

	Shape *cb8 = new Shape(glm::vec3(0.0f, 0.0f, 0.0f));
	translate = glm::translate(glm::mat4(1.0f), glm::vec3(2.5f, 5.0f, 0.0f));
	scale = glm::scale(glm::mat4(1.0f), glm::vec3(4.0f, 1.0f, 1.0f));
	rotate = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0));
	transform = translate * rotate * scale;
	cb8->transform(transform);

	Shape *cb9 = new Shape(glm::vec3(0.0f, 0.0f, 0.0f));
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



/* Static methods to create our Models */
static void createBensModel(ModelContainer* modelContainer, Shader* shader)
{

	Model* three = new Model(true, true, false, false, "3", shader, 0);

	three->addPolygon(new Shape(glm::vec3(6.0f, 3.5f, 0.0f)));
	three->addPolygon(new Shape(glm::vec3(6.5f, 3.5f, 0.0f)));
	three->addPolygon(new Shape(glm::vec3(7.0f, 3.5f, 0.0f)));
	three->addPolygon(new Shape(glm::vec3(6.0f, 2.0f, 0.0f)));
	three->addPolygon(new Shape(glm::vec3(6.5f, 2.0f, 0.0f)));
	three->addPolygon(new Shape(glm::vec3(7.0f, 2.0f, 0.0f)));
	three->addPolygon(new Shape(glm::vec3(6.0f, 0.5f, 0.0f)));
	three->addPolygon(new Shape(glm::vec3(6.5f, 0.5f, 0.0f)));
	three->addPolygon(new Shape(glm::vec3(7.0f, 0.5f, 0.0f)));
	three->addPolygon(new Shape(glm::vec3(7.5f, 1.0f, 0.0f)));
	three->addPolygon(new Shape(glm::vec3(7.5f, 3.0f, 0.0f)));
	three->transform(glm::translate(glm::mat4(1.0f), glm::vec3(-5.0f, 0.0f, 0.0f)));

	

	Shape *cb = new Shape(glm::vec3(9.125f, 0.5f, 0.0f));
	Shape *cb1 = new Shape(glm::vec3(6.825f, 0.5f, 0.0f));
	Shape *cb2 = new Shape(glm::vec3(1.0f, 0.0f, 0.0f));
	
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

static void createIsabellesModel(Model * model)
{
	//A
	Shape * Shape1 = new Shape(glm::vec3(-1.0f, 0.5f, 0.0f));
	Shape * Shape2 = new Shape(glm::vec3(-2.0f, 2.5f, 0.0f));
	Shape * Shape3 = new Shape(glm::vec3(-3.0f, 0.5f, 0.0f));
	Shape * Shape4 = new Shape(glm::vec3(-2.0f, 4.5f, 0.0f));

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 5.0f, 1.0f));
	Shape1->transform(scale);
	Shape3->transform(scale);
	model->addPolygon(Shape1);
	model->addPolygon(Shape2);
	model->addPolygon(Shape3);
	model->addPolygon(Shape4);

	//0
	Shape * Shape5 = new Shape(glm::vec3(1.0f , 0.5f, 0.0f));
	Shape * Shape6 = new Shape(glm::vec3(2.0f, 0.5f, 0.0f));
	Shape * Shape7 = new Shape(glm::vec3(3.0f, 0.5f, 0.0f));
	Shape * Shape8 = new Shape(glm::vec3(2.0f, 4.5f, 0.0f));

	Shape5->transform(scale);
	Shape7->transform(scale);
	model->addPolygon(Shape5);
	model->addPolygon(Shape6);
	model->addPolygon(Shape7);
	model->addPolygon(Shape8);

	// Set initial position
	glm::mat4 mat(1.0f);
	mat = glm::rotate(mat, glm::radians(225.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model->transform(mat);
}

static void createZimingsModel(Model * model)
{
	Shape * cb1 = new Shape(glm::vec3(-5.0f, 0.5f, 0.0f));
	Shape * cb2 = new Shape(glm::vec3(-5.0f, 1.5f, 0.0f));
	Shape * cb3 = new Shape(glm::vec3(-5.0f, 2.5f, 0.0f));
	Shape * cb4 = new Shape(glm::vec3(-5.0f, 3.5f, 0.0f));
	Shape * cb5 = new Shape(glm::vec3(-4.0f, 3.5f, 0.0f));
	Shape * cb6 = new Shape(glm::vec3(-3.0f, 0.5f, 0.0f));
	Shape * cb7 = new Shape(glm::vec3(-3.0f, 1.5f, 0.0f));
	Shape * cb8 = new Shape(glm::vec3(-3.0f, 2.5f, 0.0f));
	Shape * cb9 = new Shape(glm::vec3(-3.0f, 3.5f, 0.0f));
	Shape * cb10 = new Shape(glm::vec3(-2.0f, 3.5f, 0.0f));
	Shape * cb11 = new Shape(glm::vec3(-1.0f, 0.5f, 0.0f));
	Shape * cb12 = new Shape(glm::vec3(-1.0f, 1.5f, 0.0f));
	Shape * cb13 = new Shape(glm::vec3(-1.0f, 2.5f, 0.0f));
	Shape * cb14 = new Shape(glm::vec3(-1.0f, 3.5f, 0.0f));

	Shape * cb15 = new Shape(glm::vec3(1.0f, 1.5f, 0.0f));
	Shape * cb16 = new Shape(glm::vec3(1.0f, 2.5f, 0.0f));
	Shape * cb17 = new Shape(glm::vec3(1.0f, 3.5f, 0.0f));
	Shape * cb18 = new Shape(glm::vec3(2.0f, 1.5f, 0.0f));
	Shape * cb19 = new Shape(glm::vec3(3.0f, 0.5f, 0.0f));
	Shape * cb20 = new Shape(glm::vec3(3.0f, 1.5f, 0.0f));
	Shape * cb21 = new Shape(glm::vec3(3.0f, 2.5f, 0.0f));
	Shape * cb22 = new Shape(glm::vec3(3.0f, 3.5f, 0.0f));
	Shape * cb23 = new Shape(glm::vec3(4.0f, 1.5f, 0.0f));

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
	Shape * cb1 = new Shape(glm::vec3(0.0f, 0.0f, 0.0f));

	model->addPolygon(cb1);
}