//to be cube

#include<iostream>
#include "Cube.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../Opengl_a/VertexComponent.h"


void Cube::setupVC() 
{

	vc = new VertexController(true, false);

	Vertex a1;
	a1.addVertexComponent(VertexComponent(POSITION, glm::vec3(-0.5f, -0.5f, -0.5f)));
	a1.addVertexComponent(VertexComponent(TEXTURE, glm::vec2(0.0f, 0.0f)));
	vc->appendVertex(a1);

	Vertex a2;
	a2.addVertexComponent(VertexComponent(POSITION, glm::vec3(0.5f, -0.5f, -0.5f)));
	a2.addVertexComponent(VertexComponent(TEXTURE, glm::vec2(1.0f, 0.0f)));
	vc->appendVertex(a2);

	Vertex a3;
	a3.addVertexComponent(VertexComponent(POSITION, glm::vec3(0.5f, 0.5f, -0.5f)));
	a3.addVertexComponent(VertexComponent(TEXTURE, glm::vec2(1.0f, 1.0f)));
	vc->appendVertex(a3);

	Vertex a4;
	a4.addVertexComponent(VertexComponent(POSITION, glm::vec3(0.5f, 0.5f, -0.5f)));
	a4.addVertexComponent(VertexComponent(TEXTURE, glm::vec2(1.0f, 1.0f)));
	vc->appendVertex(a4);

	Vertex a5;
	a5.addVertexComponent(VertexComponent(POSITION, glm::vec3(-0.5f, 0.5f, -0.5f)));
	a5.addVertexComponent(VertexComponent(TEXTURE, glm::vec2(0.0f, 1.0f)));
	vc->appendVertex(a5);

	Vertex a6;
	a6.addVertexComponent(VertexComponent(POSITION, glm::vec3(-0.5f, -0.5f, -0.5f)));
	a6.addVertexComponent(VertexComponent(TEXTURE, glm::vec2(0.0f, 0.0f)));
	vc->appendVertex(a6);




	Vertex l1;
	l1.addVertexComponent(VertexComponent(POSITION, glm::vec3(-0.5f, -0.5f, 0.5f)));
	l1.addVertexComponent(VertexComponent(TEXTURE, glm::vec2(0.0f, 0.0f)));
	vc->appendVertex(l1);

	Vertex l2;
	l2.addVertexComponent(VertexComponent(POSITION, glm::vec3(0.5f, -0.5f, 0.5f)));
	l2.addVertexComponent(VertexComponent(TEXTURE, glm::vec2(1.0f, 0.0f)));
	vc->appendVertex(l2);

	Vertex l3;
	l3.addVertexComponent(VertexComponent(POSITION, glm::vec3(0.5f, 0.5f, 0.5f)));
	l3.addVertexComponent(VertexComponent(TEXTURE, glm::vec2(1.0f, 1.0f)));
	vc->appendVertex(l3);

	Vertex l4;
	l4.addVertexComponent(VertexComponent(POSITION, glm::vec3(0.5f, 0.5f, 0.5f)));
	l4.addVertexComponent(VertexComponent(TEXTURE, glm::vec2(1.0f, 1.0f)));
	vc->appendVertex(l4);

	Vertex l5;
	l5.addVertexComponent(VertexComponent(POSITION, glm::vec3(-0.5f, 0.5f, 0.5f)));
	l5.addVertexComponent(VertexComponent(TEXTURE, glm::vec2(0.0f, 1.0f)));
	vc->appendVertex(l5);

	Vertex l6;
	l6.addVertexComponent(VertexComponent(POSITION, glm::vec3(-0.5f, -0.5f, 0.5f)));
	l6.addVertexComponent(VertexComponent(TEXTURE, glm::vec2(0.0f, 0.0f)));
	vc->appendVertex(l6);




	Vertex p1;
	p1.addVertexComponent(VertexComponent(POSITION, glm::vec3(-0.5f, 0.5f, 0.5f)));
	p1.addVertexComponent(VertexComponent(TEXTURE, glm::vec2(1.0f, 0.0f)));
	vc->appendVertex(p1);

	Vertex p2;
	p2.addVertexComponent(VertexComponent(POSITION, glm::vec3(-0.5f, 0.5f, -0.5f)));
	p2.addVertexComponent(VertexComponent(TEXTURE, glm::vec2(1.0f, 1.0f)));
	vc->appendVertex(p2);

	Vertex p3;
	p3.addVertexComponent(VertexComponent(POSITION, glm::vec3(-0.5f, -0.5f, -0.5f)));
	p3.addVertexComponent(VertexComponent(TEXTURE, glm::vec2(0.0f, 1.0f)));
	vc->appendVertex(p3);

	Vertex p4;
	p4.addVertexComponent(VertexComponent(POSITION, glm::vec3(-0.5f, -0.5f, -0.5f)));
	p4.addVertexComponent(VertexComponent(TEXTURE, glm::vec2(0.0f, 1.0f)));
	vc->appendVertex(p4);

	Vertex p5;
	p5.addVertexComponent(VertexComponent(POSITION, glm::vec3(-0.5f, -0.5f, 0.5f)));
	p5.addVertexComponent(VertexComponent(TEXTURE, glm::vec2(0.0f, 0.0f)));
	vc->appendVertex(p5);

	Vertex p6;
	p6.addVertexComponent(VertexComponent(POSITION, glm::vec3(-0.5f, 0.5f, 0.5f)));
	p6.addVertexComponent(VertexComponent(TEXTURE, glm::vec2(1.0f, 0.0f)));
	vc->appendVertex(p6);




	Vertex o1;
	o1.addVertexComponent(VertexComponent(POSITION, glm::vec3(0.5f, 0.5f, 0.5f)));
	o1.addVertexComponent(VertexComponent(TEXTURE, glm::vec2(1.0f, 0.0f)));
	vc->appendVertex(o1);

	Vertex o2;
	o2.addVertexComponent(VertexComponent(POSITION, glm::vec3(0.5f, 0.5f, -0.5f)));
	o2.addVertexComponent(VertexComponent(TEXTURE, glm::vec2(1.0f, 1.0f)));
	vc->appendVertex(o2);

	Vertex o3;
	o3.addVertexComponent(VertexComponent(POSITION, glm::vec3(0.5f, -0.5f, -0.5f)));
	o3.addVertexComponent(VertexComponent(TEXTURE, glm::vec2(0.0f, 1.0f)));
	vc->appendVertex(o3);

	Vertex o4;
	o4.addVertexComponent(VertexComponent(POSITION, glm::vec3(0.5f, -0.5f, -0.5f)));
	o4.addVertexComponent(VertexComponent(TEXTURE, glm::vec2(0.0f, 1.0f)));
	vc->appendVertex(o4);

	Vertex o5;
	o5.addVertexComponent(VertexComponent(POSITION, glm::vec3(0.5f, -0.5f, 0.5f)));
	o5.addVertexComponent(VertexComponent(TEXTURE, glm::vec2(0.0f, 0.0f)));
	vc->appendVertex(o5);

	Vertex o6;
	o6.addVertexComponent(VertexComponent(POSITION, glm::vec3(0.5f, 0.5f, 0.5f)));
	o6.addVertexComponent(VertexComponent(TEXTURE, glm::vec2(1.0f, 0.0f)));
	vc->appendVertex(o6);



	Vertex k1;
	k1.addVertexComponent(VertexComponent(POSITION, glm::vec3(-0.5f, -0.5f, -0.5f)));
	k1.addVertexComponent(VertexComponent(TEXTURE, glm::vec2(0.0f, 1.0f)));
	vc->appendVertex(k1);

	Vertex k2;
	k2.addVertexComponent(VertexComponent(POSITION, glm::vec3(0.5f, -0.5f, -0.5f)));
	k2.addVertexComponent(VertexComponent(TEXTURE, glm::vec2(1.0f, 1.0f)));
	vc->appendVertex(k2);

	Vertex k3;
	k3.addVertexComponent(VertexComponent(POSITION, glm::vec3(0.5f, -0.5f, 0.5f)));
	k3.addVertexComponent(VertexComponent(TEXTURE, glm::vec2(1.0f, 0.0f)));
	vc->appendVertex(k3);

	Vertex k4;
	k4.addVertexComponent(VertexComponent(POSITION, glm::vec3(0.5f, -0.5f, 0.5f)));
	k4.addVertexComponent(VertexComponent(TEXTURE, glm::vec2(1.0f, 0.0f)));
	vc->appendVertex(k4);

	Vertex k5;
	k5.addVertexComponent(VertexComponent(POSITION, glm::vec3(-0.5f, -0.5f, 0.5f)));
	k5.addVertexComponent(VertexComponent(TEXTURE, glm::vec2(0.0f, 0.0f)));
	vc->appendVertex(k5);

	Vertex k6;
	k6.addVertexComponent(VertexComponent(POSITION, glm::vec3(-0.5f, -0.5f, -0.5f)));
	k6.addVertexComponent(VertexComponent(TEXTURE, glm::vec2(0.0f, 1.0f)));
	vc->appendVertex(k6);



	Vertex u1;
	u1.addVertexComponent(VertexComponent(POSITION, glm::vec3(-0.5f, 0.5f, -0.5f)));
	u1.addVertexComponent(VertexComponent(TEXTURE, glm::vec2(0.0f, 1.0f)));
	vc->appendVertex(u1);

	Vertex u2;
	u2.addVertexComponent(VertexComponent(POSITION, glm::vec3(0.5f, 0.5f, -0.5f)));
	u2.addVertexComponent(VertexComponent(TEXTURE, glm::vec2(1.0f, 1.0f)));
	vc->appendVertex(u2);

	Vertex u3;
	u3.addVertexComponent(VertexComponent(POSITION, glm::vec3(0.5f, 0.5f, 0.5f)));
	u3.addVertexComponent(VertexComponent(TEXTURE, glm::vec2(1.0f, 0.0f)));
	vc->appendVertex(u3);

	Vertex u4;
	u4.addVertexComponent(VertexComponent(POSITION, glm::vec3(0.5f, 0.5f, 0.5f)));
	u4.addVertexComponent(VertexComponent(TEXTURE, glm::vec2(1.0f, 0.0f)));
	vc->appendVertex(u4);

	Vertex u5;
	u5.addVertexComponent(VertexComponent(POSITION, glm::vec3(-0.5f, 0.5f, 0.5f)));
	u5.addVertexComponent(VertexComponent(TEXTURE, glm::vec2(0.0f, 0.0f)));
	vc->appendVertex(u5);

	Vertex u6;
	u6.addVertexComponent(VertexComponent(POSITION, glm::vec3(-0.5f, 0.5f, -0.5f)));
	u6.addVertexComponent(VertexComponent(TEXTURE, glm::vec2(0.0f, 1.0f)));
	vc->appendVertex(u6);

}

Cube::Cube(glm::vec3 origin_a)
{
	setupVC();
	origin = origin_a;
	translate_fromOrigin();
}

void Cube::setVertexController(bool position, bool texture, bool color) 
{
	vc->position = position;
	vc->texture = texture;
	vc->color = color;
}

Vertex Cube::getSampleVertex()
{
	return vc->vertices.front();
}

void Cube::transform(glm::mat4 transmat)
{
	vc->transform(transmat);
}

void Cube::translate_fromOrigin()
{
	glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0 + origin.x, 0.0 + origin.y, 0.0 + origin.z));
	vc->transform(translation);
}

int Cube::getVAVertexCount()
{
	return vc->getVAVertexCount();
}

int Cube::getVAFloatCount()
{
	return vc->getVAFloatCount();
}

int Cube::getVAByteSize()
{
	return vc->getVAByteSize();
}

int Cube::getVertexByteSize()
{

	return vc->getVertexByteSize(vc->vertices.front());
}


float* Cube::getVertexArray()
{
	return vc->getVertexArray();
}
