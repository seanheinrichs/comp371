/*
Model

Depends on: Polygon.h

Description: A container for groups of related geometry. It handles the creation of
arbitrarily sized vertex arrays from the polygons that it contains.

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
#include <glm/gtx/transform2.hpp> 

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
	void addTranslationSphere(glm::vec3 translate);
	void addShear(glm::vec3 translate);

	glm::mat4 getRotation();
	glm::mat4 getTranslation();
	glm::mat4 getTranslationSphere();
	glm::mat4 getScale();
	glm::mat4 getShear();
	glm::mat4 getModelMatrix(bool state);//sate = true when include shear in calculation
	virtual float* getVertexArray();
	virtual int getVAFloatCount();
	virtual int getVAByteSize();
	virtual int getVAVertexCount();
	virtual int getVertexByteSize();
	virtual Vertex getSampleVertex();
	virtual std::map<std::string, glm::vec3> getMinMax();


	void translateToOrigin();

	glm::vec3 origin;
	int vaComponentCount;
	int vaByteSize;


	//vertex components
	bool position, color, texture;
	glm::vec3 rotate_vec;
	glm::vec3 translate_vec;
	glm::vec3 translate_vec_sphere;
	glm::vec3 scale_vec;
	glm::vec3 shear_vec;

	float rotate_angle;

};