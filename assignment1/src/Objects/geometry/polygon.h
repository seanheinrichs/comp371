#pragma once

#include "../../Opengl_a/vertex.h"
#include <map>
#include <string>

/*
*Polygon
*
*Description: A base class for any polygons we may need to create. The virtual methods bellow
*are a necessary API for interacting with the model object to properly calculate vertice byte sizes
*
*Note: The virtual methods below must be overriden to for correct polymorphic behaviour
*
*/
class Polygon 
{
	public:
		virtual void transform(glm::mat4 transMat) {}
		virtual int getVAVertexCount() = 0;
		virtual int getVAByteSize() = 0;
		virtual int getVAFloatCount() = 0;
		virtual int getVertexByteSize() = 0;
		virtual void setVertexController(bool position, bool texture, bool color, bool normal) = 0;
		virtual Vertex getSampleVertex() { return Vertex(); }
		virtual void setBoolean(bool position, bool texture, bool color, bool normal) {}
		virtual std::map<std::string, glm::vec3> getMinMax(glm::mat4 modelMatrix, bool useMat)=0;
		virtual float* getVertexArray() = 0;
		virtual void print() = 0;
		virtual void printMat(glm::mat4 modelMatrix) = 0;
};




