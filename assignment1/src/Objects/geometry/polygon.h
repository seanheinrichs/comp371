#pragma once

#include <glm/glm.hpp>


class Polygon 
{
	public:
		virtual void transform(glm::mat4 transMat);
		virtual int getVAComponentCount() { return 0; }
		virtual int getVAByteSize() { return 0; }
		virtual float* getVertices();
		//virtual ~Polygon();

};
