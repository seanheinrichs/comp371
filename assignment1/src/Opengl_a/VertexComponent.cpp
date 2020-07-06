#include "VertexComponent.h"


VertexComponent::VertexComponent(Components tp, glm::vec2 dat) 
{
	type = tp;
	data = new float[2];
	data[0] = dat.x;
	data[1] = dat.y;
	floatCount = 2;
}
VertexComponent::VertexComponent(Components tp, glm::vec3 dat)
{
	type = tp;
	data = new float[3];
	data[0] = dat.x;
	data[1] = dat.y;
	data[2] = dat.z;
	floatCount = 3;
}
VertexComponent::VertexComponent(Components tp, glm::vec4 dat)
{
	type = tp;
	data = new float[4];
	data[0] = dat.x;
	data[1] = dat.y;
	data[2] = dat.z;
	data[3] = dat.w;
	floatCount = 4;
}

float* VertexComponent::getData()
{
	return data;
}

