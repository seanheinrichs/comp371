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
		virtual int getVAVertexCount() { return 5; }
		virtual int getVAByteSize() { return 5; }
		virtual int getVAFloatCount() { return 5; }
		virtual int getVertexByteSize() { return 5; }
		virtual void setVertexController(bool position, bool texture, bool color) {}
		virtual Vertex getSampleVertex() { return Vertex(); }
		virtual std::map<std::string, glm::vec3> getMinMax()
		{
			std::map<std::string, glm::vec3> map;
			map["min"] = glm::vec3(0.0f);
			map["max"] = glm::vec3(0.0f);
			return map;
		};
		virtual float* getVertexArray() {
			float* a = new float[3];
			a[0] = 5.0;
			a[1] = 5.0;
			a[2] = 5.0;

			return a;
		}
};
