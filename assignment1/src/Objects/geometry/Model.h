/*
Model

Depends on: Polygon.h

Description: A container for groups of related geometry. It handles the creation of
arbitrarily sized vertex arrays from the polygons that it contains.

TODO: Create API for one origin point for the entire polygon

origin: the point of origin for this particular polygon
vaComponentCount: the number of vertex components in the Polygons of the model
vaByteSize: the number Bytes required to contain the vertices of all the polygons in memory 

*/

#pragma once
#include "binder.h"
#include <vector>
#include <glm/glm.hpp>
#include "polygon.h"
#include <glm/gtc/type_ptr.hpp>


class Model : public Polygon, public Binder
{
public:
	virtual void setVertexController(bool position, bool texture, bool color);
	virtual void transform(glm::mat4 transmat);
	std::vector<Polygon*> polygons;
	void addPolygon(Polygon* poly);
	Model(bool position, bool texture, bool color);
	Model();

	void addRotation(float radians, glm::vec3 axis);
	void addScale(glm::vec3 scale);
	void addTranslation(glm::vec3 translate);
	void addTranslationOrigin(glm::vec3 translate);
	glm::mat4 getRotation();
	glm::mat4 getTranslation();
	glm::mat4 getScale();
	glm::mat4 getOrigin();
	glm::mat4 getModelMatrix();

	virtual float* getVertexArray();
	virtual int getVAFloatCount();
	virtual int getVAByteSize();
	virtual int getVAVertexCount();
	virtual int getVertexByteSize();
	virtual Vertex getSampleVertex();

	//binding
	//void bindArrayBuffer(bool unbind);
	//void bind();
	//void unbind();


	glm::vec3 origin;
	int vaComponentCount;
	int vaByteSize;

	//Binder* binder;

	//vertex components
	bool position, color, texture;

	void printTranslate();
	glm::vec3 rotate_vec;
	glm::vec3 translate_vec;
	glm::vec3 scale_vec;
	glm::vec3 translate_vec_origin;
	float rotate_angle;

};