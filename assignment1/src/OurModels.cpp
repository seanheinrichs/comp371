#include "Objects/geometry/Cube.h"
#include "Objects/geometry/Model.h"
#include <glm/gtc/matrix_transform.hpp>



/* Static methods to create our Models */
static Model * createSeansModel()
{
	Cube * cb1 = new Cube(glm::vec3(0.0f, 0.5f, 0.0f));
	Cube * cb2 = new Cube(glm::vec3(0.0f, 1.5f, 0.0f));
	Cube * cb3 = new Cube(glm::vec3(0.0f, 2.5f, 0.0f));
	Cube * cb4 = new Cube(glm::vec3(0.0f, 3.5f, 0.0f));
	Cube * cb5 = new Cube(glm::vec3(1.0f, 1.5f, 0.0f));
	Cube * cb6 = new Cube(glm::vec3(1.0f, 3.5f, 0.0f));
	Cube * cb7 = new Cube(glm::vec3(2.0f, 0.5f, 0.0f));
	Cube * cb8 = new Cube(glm::vec3(2.0f, 1.5f, 0.0f));
	Cube * cb9 = new Cube(glm::vec3(2.0f, 2.5f, 0.0f));
	Cube * cb10 = new Cube(glm::vec3(2.0f, 3.5f, 0.0f));
	Cube * cb11 = new Cube(glm::vec3(4.0f, 2.5f, 0.0f));
	Cube * cb12 = new Cube(glm::vec3(4.0f, 3.5f, 0.0f));
	Cube * cb13 = new Cube(glm::vec3(5.0f, 3.5f, 0.0f));
	Cube * cb14 = new Cube(glm::vec3(6.0f, 3.5f, 0.0f));
	Cube * cb15 = new Cube(glm::vec3(6.0f, 2.5f, 0.0f));
	Cube * cb16 = new Cube(glm::vec3(6.0f, 1.5f, 0.0f));
	Cube * cb17 = new Cube(glm::vec3(6.0f, 0.5f, 0.0f));

	Model * seansModel = new Model(true, false, false);
	seansModel->addPolygon(cb1);
	seansModel->addPolygon(cb2);
	seansModel->addPolygon(cb3);
	seansModel->addPolygon(cb4);
	seansModel->addPolygon(cb5);
	seansModel->addPolygon(cb6);
	seansModel->addPolygon(cb7);
	seansModel->addPolygon(cb8);
	seansModel->addPolygon(cb9);
	seansModel->addPolygon(cb10);
	seansModel->addPolygon(cb11);
	seansModel->addPolygon(cb12);
	seansModel->addPolygon(cb13);
	seansModel->addPolygon(cb14);
	seansModel->addPolygon(cb15);
	seansModel->addPolygon(cb16);
	seansModel->addPolygon(cb17);

	return seansModel;
}


static Model * createWaynesModel()
{
	Cube * cb1 = new Cube(glm::vec3(0.0f, 3.0f, 0.0f));
	Cube * cb2 = new Cube(glm::vec3(0.0f, 4.0f, 0.0f));
	Cube * cb3 = new Cube(glm::vec3(1.0f, 0.0f, 0.0f));
	Cube * cb4 = new Cube(glm::vec3(1.0f, 1.0f, 0.0f));
	Cube * cb5 = new Cube(glm::vec3(1.0f, 2.0f, 0.0f));
	Cube * cb6 = new Cube(glm::vec3(1.0f, 3.0f, 0.0f));
	Cube * cb7 = new Cube(glm::vec3(2.0f, 3.0f, 0.0f));
	Cube * cb8 = new Cube(glm::vec3(2.0f, 4.0f, 0.0f));

	Cube * cb9 = new Cube(glm::vec3(4.0f, 3.0f, 0.0f));
	Cube * cb10 = new Cube(glm::vec3(4.0f, 4.0f, 0.0f));
	Cube * cb11 = new Cube(glm::vec3(5.0f, 4.0f, 0.0f));
	Cube * cb12 = new Cube(glm::vec3(6.0f, 0.0f, 0.0f));
	Cube * cb13 = new Cube(glm::vec3(6.0f, 1.0f, 0.0f));
	Cube * cb14 = new Cube(glm::vec3(6.0f, 2.0f, 0.0f));
	Cube * cb15 = new Cube(glm::vec3(6.0f, 3.0f, 0.0f));
	Cube * cb16 = new Cube(glm::vec3(6.0f, 4.0f, 0.0f));


	Model * waynesModel = new Model(true, false, false);
	waynesModel->addPolygon(cb1);
	waynesModel->addPolygon(cb2);
	waynesModel->addPolygon(cb3);
	waynesModel->addPolygon(cb4);
	waynesModel->addPolygon(cb5);
	waynesModel->addPolygon(cb6);
	waynesModel->addPolygon(cb7);
	waynesModel->addPolygon(cb8);

	waynesModel->addPolygon(cb9);
	waynesModel->addPolygon(cb10);
	waynesModel->addPolygon(cb11);
	waynesModel->addPolygon(cb12);
	waynesModel->addPolygon(cb13);
	waynesModel->addPolygon(cb14);
	waynesModel->addPolygon(cb15);
	waynesModel->addPolygon(cb16);

	glm::mat4 mat(1.0f);
	mat = glm::translate(mat, glm::vec3(10.0f, 0.0f, 10.0f));

	waynesModel->transform(mat);

	return waynesModel;

}


/* Static methods to create our Models */
static void createBensModel(Model* model)
{

	model->addPolygon(new Cube(glm::vec3(0.0f, 0.5f, 0.0f)));
	model->addPolygon(new Cube(glm::vec3(0.0f, 1.5f, 0.0f)));
	model->addPolygon(new Cube(glm::vec3(0.0f, 2.5f, 0.0f)));
	model->addPolygon(new Cube(glm::vec3(0.0f, 3.5f, 0.0f)));
	model->addPolygon(new Cube(glm::vec3(0.75f, 3.5f, 0.0f)));
	model->addPolygon(new Cube(glm::vec3(1.25f, 2.5f, 0.0f)));
	model->addPolygon(new Cube(glm::vec3(1.75f, 1.5f, 0.0f)));
	model->addPolygon(new Cube(glm::vec3(2.25f, 0.5f, 0.0f)));
	model->addPolygon(new Cube(glm::vec3(3.0f, 0.5f, 0.0f)));
	model->addPolygon(new Cube(glm::vec3(3.0f, 1.5f, 0.0f)));
	model->addPolygon(new Cube(glm::vec3(3.0f, 2.5f, 0.0f)));
	model->addPolygon(new Cube(glm::vec3(3.0f, 3.5f, 0.0f)));



	model->addPolygon(new Cube(glm::vec3(5.0f, 3.5f, 0.0f)));
	model->addPolygon(new Cube(glm::vec3(5.5f, 3.5f, 0.0f)));
	model->addPolygon(new Cube(glm::vec3(6.0f, 3.5f, 0.0f)));
	model->addPolygon(new Cube(glm::vec3(5.0f, 2.0f, 0.0f)));
	model->addPolygon(new Cube(glm::vec3(5.5f, 2.0f, 0.0f)));
	model->addPolygon(new Cube(glm::vec3(6.0f, 2.0f, 0.0f)));
	model->addPolygon(new Cube(glm::vec3(5.0f, 0.5f, 0.0f)));
	model->addPolygon(new Cube(glm::vec3(5.5f, 0.5f, 0.0f)));
	model->addPolygon(new Cube(glm::vec3(6.0f, 0.5f, 0.0f)));

	model->addPolygon(new Cube(glm::vec3(6.5f, 1.0f, 0.0f)));
	model->addPolygon(new Cube(glm::vec3(6.5f, 3.0f, 0.0f)));


	/*
	Cube *cb = new Cube(glm::vec3(8.5f, 3.0f, 0.0f));
	glm::mat4 warp = glm::mat4(
		1.0f, 0.0f, 5.0f, 0.0f,
		0.0f, 1.0f, 5.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);

	warp = glm::translate(warp, glm::vec3(0.0f, 0.0f, -40.0f));
	warp = glm::rotate(warp, glm::radians(45.0f), glm::vec3(1.0f, 1.0f, 1.0));

	cb->transform(warp);
	model->addPolygon(cb);
	*/



	glm::mat4 mat(1.0f);
	mat = glm::translate(mat, glm::vec3(20.0f, 0.0f, 0.0f));

	model->transform(mat);

}


static Model * createIsabellesModel()
{
	//A0
	float originX = 20.0f;
	float originY = 0.5f;
	float originZ = 0.0f;
	float cubeOffset = 1.0f;
	float letterOffset = cubeOffset * 5;
	//drawing A
	//left 
	Cube * cube1 = new Cube(glm::vec3(originX, originY, originZ));
	Cube * cube2 = new Cube(glm::vec3(originX, originY + cubeOffset, originZ));
	Cube * cube3 = new Cube(glm::vec3(originX, originY + cubeOffset * 2, originZ));
	Cube * cube4 = new Cube(glm::vec3(originX, originY + cubeOffset * 3, originZ));
	Cube * cube5 = new Cube(glm::vec3(originX, originY + cubeOffset * 4, originZ));
	Cube * cube6 = new Cube(glm::vec3(originX, originY + cubeOffset * 5, originZ));
	//right
	Cube * cube7 = new Cube(glm::vec3(originX + cubeOffset * 3, originY, originZ));
	Cube * cube8 = new Cube(glm::vec3(originX + cubeOffset * 3, originY + cubeOffset, originZ));
	Cube * cube9 = new Cube(glm::vec3(originX + cubeOffset * 3, originY + cubeOffset * 2, originZ));
	Cube * cube10 = new Cube(glm::vec3(originX + cubeOffset * 3, originY + cubeOffset * 3, originZ));
	Cube * cube11 = new Cube(glm::vec3(originX + cubeOffset * 3, originY + cubeOffset * 4, originZ));
	Cube * cube12 = new Cube(glm::vec3(originX + cubeOffset * 3, originY + cubeOffset * 5, originZ));
	//middle top
	Cube * cube13 = new Cube(glm::vec3(originX + cubeOffset, originY + cubeOffset * 5, originZ));
	Cube * cube14 = new Cube(glm::vec3(originX + cubeOffset * 2, originY + cubeOffset * 5, originZ));
	//middle bottom
	Cube * cube15 = new Cube(glm::vec3(originX + cubeOffset, originY + cubeOffset * 3, originZ));
	Cube * cube16 = new Cube(glm::vec3(originX + cubeOffset * 2, originY + cubeOffset * 3, originZ));

	//drawing 0
	//left
	Cube * cube17 = new Cube(glm::vec3(originX + letterOffset, originY, originZ));
	Cube * cube18 = new Cube(glm::vec3(originX + letterOffset, originY + cubeOffset, originZ));
	Cube * cube19 = new Cube(glm::vec3(originX + letterOffset, originY + cubeOffset * 2, originZ));
	Cube * cube20 = new Cube(glm::vec3(originX + letterOffset, originY + cubeOffset * 3, originZ));
	Cube * cube21 = new Cube(glm::vec3(originX + letterOffset, originY + cubeOffset * 4, originZ));
	Cube * cube22 = new Cube(glm::vec3(originX + letterOffset, originY + cubeOffset * 5, originZ));
	//right
	Cube * cube23 = new Cube(glm::vec3(originX + letterOffset + cubeOffset * 3, originY, originZ));
	Cube * cube24 = new Cube(glm::vec3(originX + letterOffset + cubeOffset * 3, originY + cubeOffset, originZ));
	Cube * cube25 = new Cube(glm::vec3(originX + letterOffset + cubeOffset * 3, originY + cubeOffset * 2, originZ));
	Cube * cube26 = new Cube(glm::vec3(originX + letterOffset + cubeOffset * 3, originY + cubeOffset * 3, originZ));
	Cube * cube27 = new Cube(glm::vec3(originX + letterOffset + cubeOffset * 3, originY + cubeOffset * 4, originZ));
	Cube * cube28 = new Cube(glm::vec3(originX + letterOffset + cubeOffset * 3, originY + cubeOffset * 5, originZ));
	//top
	Cube * cube29 = new Cube(glm::vec3(originX + letterOffset + cubeOffset, originY + cubeOffset * 5, originZ));
	Cube * cube30 = new Cube(glm::vec3(originX + letterOffset + cubeOffset * 2, originY + cubeOffset * 5, originZ));
	//bottom
	Cube * cube31 = new Cube(glm::vec3(originX + letterOffset + cubeOffset, originY, originZ));
	Cube * cube32 = new Cube(glm::vec3(originX + letterOffset + cubeOffset * 2, originY, originZ));

	Model * isabellesModel = new Model(true, false, false);
	isabellesModel->addPolygon(cube1);
	isabellesModel->addPolygon(cube2);
	isabellesModel->addPolygon(cube3);
	isabellesModel->addPolygon(cube4);
	isabellesModel->addPolygon(cube5);
	isabellesModel->addPolygon(cube6);
	isabellesModel->addPolygon(cube7);
	isabellesModel->addPolygon(cube8);
	isabellesModel->addPolygon(cube9);
	isabellesModel->addPolygon(cube10);
	isabellesModel->addPolygon(cube11);
	isabellesModel->addPolygon(cube12);
	isabellesModel->addPolygon(cube13);
	isabellesModel->addPolygon(cube14);
	isabellesModel->addPolygon(cube15);
	isabellesModel->addPolygon(cube16);
	isabellesModel->addPolygon(cube17);
	isabellesModel->addPolygon(cube18);
	isabellesModel->addPolygon(cube19);
	isabellesModel->addPolygon(cube20);
	isabellesModel->addPolygon(cube21);
	isabellesModel->addPolygon(cube22);
	isabellesModel->addPolygon(cube23);
	isabellesModel->addPolygon(cube24);
	isabellesModel->addPolygon(cube25);
	isabellesModel->addPolygon(cube26);
	isabellesModel->addPolygon(cube27);
	isabellesModel->addPolygon(cube28);
	isabellesModel->addPolygon(cube29);
	isabellesModel->addPolygon(cube30);
	isabellesModel->addPolygon(cube31);
	isabellesModel->addPolygon(cube32);

	glm::mat4 mat(1.0f);
	mat = glm::translate(mat, glm::vec3(0.0f, 0.0f, 15.0f));

	isabellesModel->transform(mat);

	return isabellesModel;
}

static Model * createZimingsModel()
{
	Cube * cb1 = new Cube(glm::vec3(0.0f, 0.5f, 0.0f));
	Cube * cb2 = new Cube(glm::vec3(0.0f, 1.5f, 0.0f));
	Cube * cb3 = new Cube(glm::vec3(0.0f, 2.5f, 0.0f));
	Cube * cb4 = new Cube(glm::vec3(0.0f, 3.5f, 0.0f));
	Cube * cb5 = new Cube(glm::vec3(1.0f, 3.5f, 0.0f));
	Cube * cb6 = new Cube(glm::vec3(2.0f, 0.5f, 0.0f));
	Cube * cb7 = new Cube(glm::vec3(2.0f, 1.5f, 0.0f));
	Cube * cb8 = new Cube(glm::vec3(2.0f, 2.5f, 0.0f));
	Cube * cb9 = new Cube(glm::vec3(2.0f, 3.5f, 0.0f));
	Cube * cb10 = new Cube(glm::vec3(3.0f, 3.5f, 0.0f));
	Cube * cb11 = new Cube(glm::vec3(4.0f, 0.5f, 0.0f));
	Cube * cb12 = new Cube(glm::vec3(4.0f, 1.5f, 0.0f));
	Cube * cb13 = new Cube(glm::vec3(4.0f, 2.5f, 0.0f));
	Cube * cb14 = new Cube(glm::vec3(4.0f, 3.5f, 0.0f));
	Cube * cb15 = new Cube(glm::vec3(6.0f, 1.5f, 0.0f));
	Cube * cb16 = new Cube(glm::vec3(6.0f, 2.5f, 0.0f));
	Cube * cb17 = new Cube(glm::vec3(6.0f, 3.5f, 0.0f));
	Cube * cb18 = new Cube(glm::vec3(7.0f, 1.5f, 0.0f));
	Cube * cb19 = new Cube(glm::vec3(8.0f, 0.5f, 0.0f));
	Cube * cb20 = new Cube(glm::vec3(8.0f, 1.5f, 0.0f));
	Cube * cb21 = new Cube(glm::vec3(8.0f, 2.5f, 0.0f));
	Cube * cb22 = new Cube(glm::vec3(8.0f, 3.5f, 0.0f));
	Cube * cb23 = new Cube(glm::vec3(9.0f, 1.5f, 0.0f));

	Model * ZimingsModel = new Model(true, false, false);
	ZimingsModel->addPolygon(cb1);
	ZimingsModel->addPolygon(cb2);
	ZimingsModel->addPolygon(cb3);
	ZimingsModel->addPolygon(cb4);
	ZimingsModel->addPolygon(cb5);
	ZimingsModel->addPolygon(cb6);
	ZimingsModel->addPolygon(cb7);
	ZimingsModel->addPolygon(cb8);
	ZimingsModel->addPolygon(cb9);
	ZimingsModel->addPolygon(cb10);
	ZimingsModel->addPolygon(cb11);
	ZimingsModel->addPolygon(cb12);
	ZimingsModel->addPolygon(cb13);
	ZimingsModel->addPolygon(cb14);
	ZimingsModel->addPolygon(cb15);
	ZimingsModel->addPolygon(cb16);
	ZimingsModel->addPolygon(cb17);
	ZimingsModel->addPolygon(cb18);
	ZimingsModel->addPolygon(cb19);
	ZimingsModel->addPolygon(cb20);
	ZimingsModel->addPolygon(cb21);
	ZimingsModel->addPolygon(cb22);
	ZimingsModel->addPolygon(cb23);

	glm::mat4 mat(1.0f);
	mat = glm::translate(mat, glm::vec3(0.0f, 0.0f, 15.0f));

	ZimingsModel->transform(mat);

	return ZimingsModel;
}