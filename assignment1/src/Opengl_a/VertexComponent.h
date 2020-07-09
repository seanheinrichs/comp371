#pragma once
#include <glm/glm.hpp>


//#define POSITION 0
//#define TEXTURE 1 
//#define COLOR 2 

enum Components
{
	POSITION = 0,
	TEXTURE ,
	COLOR 
};

static bool operator==(Components& a, Components& b)  
{
	return (int)a == (int)b;
}

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