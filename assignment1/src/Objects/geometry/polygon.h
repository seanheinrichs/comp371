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
