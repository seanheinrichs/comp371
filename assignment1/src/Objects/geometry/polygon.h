/*
Polygon 

Description: A base class for any polygons we may need to create. The virtual methods bellow
are a necessary API for interacting with the model object that will be able to

Note: The virtual methods below must be overriden to for correct polymorphic behaviour


*/

#pragma once

#include "../../Opengl_a/vertex.h"

class Polygon 
{
	public:
		virtual void transform(glm::mat4 transMat) {}
		virtual int getVAComponentCount() { return 5; }
		virtual int getVAByteSize() { return 0; }
		virtual float* getVertexArray() {
			float* a = new float[3];
			a[0] = 5.0;
			a[1] = 5.0;
			a[2] = 5.0;

			return a;
		}
		//virtual ~Polygon();

};
