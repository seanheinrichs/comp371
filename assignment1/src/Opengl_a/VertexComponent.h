#pragma once
#include <glm/glm.hpp>


enum Components
{
	POSITION = 1,
	TEXTURE = 2
};

class VertexComponent 
{
	public:

		Components type;
		float * data;
		int floatCount = 0;

		inline int getFloatCount() { return floatCount; }
		inline int getByteSize() { return floatCount*sizeof(float); }

		VertexComponent(Components tp, glm::vec2 dat);
		VertexComponent(Components tp, glm::vec3 dat);
		VertexComponent(Components tp, glm::vec4 dat);
		float* getData();
	
};