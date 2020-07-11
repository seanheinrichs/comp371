

#include<iostream>
#include<vector>
#include "VertexController.h"
#include "vertexComponent.h"
#include "vertex.h"
#include <string>
#include <map>

VertexController::VertexController(bool position, bool texture, bool color)
{
	VertexController::position = position;
	VertexController::texture = texture;
	VertexController::color = color;
}


VertexController::VertexController(std::vector<Vertex> verts, bool position, bool texture)
{
	VertexController::position = position;
	VertexController::texture = texture;
	VertexController::vertices = verts;
}

void VertexController::appendVertex(Vertex& ver) 
{
	vertices.push_back(ver);
}

int VertexController::getVertexByteSize(Vertex vert)
{
	int size = 0;
	for (std::vector<VertexComponent>::iterator it = vert.vertexComponents.begin(); it < vert.vertexComponents.end(); it++)
	{
		if (position && it->type == POSITION)
		{
			size += it->getByteSize();
		}
		else if (texture && it->type == TEXTURE)
		{
			size += it->getByteSize();
		}
		else if (color && it->type == COLOR)
		{
			size += it->getByteSize();
		}
		else 
		{
			//pass
		}
	}

	return size;
}

int VertexController::getVertexFloatCount(Vertex vert)
{
	int size = 0;
	for (std::vector<VertexComponent>::iterator it = vert.vertexComponents.begin(); it < vert.vertexComponents.end(); it++)
	{
		if (position && it->type == POSITION)
		{
			size += it->getFloatCount();
		}
		else if (texture && it->type == TEXTURE)
		{
			size += it->getFloatCount();
		}
		else if (color && it->type == COLOR)
		{
			size += it->getFloatCount();
		}
		else
		{
			//pass
		}
	}

	return size;
}


float* VertexController::getVertex(Vertex vert)
{
	float* a = new float[getVertexFloatCount(vert)];
	int currentCount = 0;
	for(std::vector<VertexComponent>::iterator it = vert.vertexComponents.begin(); it < vert.vertexComponents.end(); it++)
	{
		if (position && it->type == POSITION)
		{
			std::copy(it->data, it->data + it->getFloatCount(), a+ currentCount);
			currentCount += it->getFloatCount();
		}
		else if (texture && it->type == TEXTURE)
		{
			std::copy(it->data, it->data + it->getFloatCount(), a + currentCount);
			currentCount += it->getFloatCount();
		}
		else if (color && it->type == COLOR)
		{
			std::copy(it->data, it->data + it->getFloatCount(), a + currentCount);
			currentCount += it->getFloatCount();
		}
	}

	return a;
}


int VertexController::getVAByteSize()
{
	return  getVertexByteSize(vertices.front()) * vertices.size();
}


int VertexController::getVAFloatCount()
{
	return  getVertexFloatCount(vertices.front()) * vertices.size();
}


int VertexController::getVAVertexCount()
{
	return  vertices.size();
}

void VertexController::transformOne(glm::mat4 transmat, VertexComponent& vc)
{
	if (vc.getFloatCount() == 4) 
	{
		glm::vec4 tempVec(
			vc.data[0],
			vc.data[1],
			vc.data[2],
			vc.data[3]
		);

		tempVec = transmat * tempVec;

		vc.data[0] = tempVec.x;
		vc.data[1] = tempVec.y;
		vc.data[2] = tempVec.z;
		vc.data[3] = tempVec.w;

	}
	else if (vc.getFloatCount() == 3)
	{
		glm::vec4 tempVec(
			vc.data[0],
			vc.data[1],
			vc.data[2],
			1.0f
		);

		tempVec = transmat * tempVec;

		vc.data[0] = tempVec.x;
		vc.data[1] = tempVec.y;
		vc.data[2] = tempVec.z;

	}
	else 
	{
		std::cout << "INVALID FLOAT COUNT VertexController::TransformOne" << std::endl;
		std::cout << "float count: "<< vc.getFloatCount() << std::endl;
	}
}

void VertexController::transform(glm::mat4 transmat)
{
	for (std::vector<Vertex>::iterator it = vertices.begin(); it < vertices.end(); it++)
	{
		for (std::vector<VertexComponent>::iterator it2 = (*it).vertexComponents.begin(); it2 < (*it).vertexComponents.end(); it2++)
		{
			if (position && it2->type == POSITION)
			{
				transformOne(transmat, *it2);
				break;
			}
			else
			{
				//pass
			}
		}
	}
	
}

float* VertexController::getVertexArray()
{
	float* va = new float[getVAFloatCount()];
	int currentCount = 0;
	int floatCount = getVertexFloatCount(vertices.front());
	for (std::vector<Vertex>::iterator it = vertices.begin(); it < vertices.end(); it++) 
	{
		float* temp = getVertex(*it);
		std::copy(temp, temp + floatCount, va + currentCount);
		currentCount += floatCount;
	}
	return va;

}



std::map<std::string, glm::vec3> VertexController::getMinMax()
{
	std::map<std::string, glm::vec3> map;
	int count = 0;
	for (std::vector<Vertex>::iterator it = vertices.begin(); it < vertices.end(); it++)
	{
		for (std::vector<VertexComponent>::iterator it2 = (*it).vertexComponents.begin(); it2 < (*it).vertexComponents.end(); it2++)
		{
			if (position && it2->type == POSITION)
			{
				if (count == 0)
				{
					glm::vec3* temp1 = new glm::vec3();
					glm::vec3* temp2 = new glm::vec3();
					temp1->x = (*it2).data[0];
					temp1->y = (*it2).data[1];
					temp1->z = (*it2).data[2];
					temp2->x = (*it2).data[0];
					temp2->y = (*it2).data[1];
					temp2->z = (*it2).data[2];


					map["min"] = *temp1;
					map["max"] = *temp2;

					delete temp2;
					delete temp1;
				}
				else 
				{
					glm::vec3* temp1 = new glm::vec3();
					glm::vec3* temp2 = new glm::vec3();
					temp1->x = (*it2).data[0];
					temp1->y = (*it2).data[1];
					temp1->z = (*it2).data[2];
					temp2->x = (*it2).data[0];
					temp2->y = (*it2).data[1];
					temp2->z = (*it2).data[2];
					std::map<std::string, glm::vec3> temp;

					temp["min"] = *temp1;
					temp["max"] = *temp2;


					
					if (map["max"].x < temp["max"].x)
						map["max"].x = temp["max"].x;

					if (map["max"].y < temp["max"].y)
						map["max"].y = temp["max"].y;

					if (map["max"].z < temp["max"].z)
						map["max"].z = temp["max"].z;

					if (map["min"].x > temp["min"].x)
						map["min"].x = temp["min"].x;

					if (map["min"].y > temp["min"].y)
						map["min"].y = temp["min"].y;

					if (map["min"].z > temp["min"].z)
						map["min"].z = temp["min"].z;

					delete temp2;
					delete temp1;
				}

				count += 1;
				break;
			}
			else
			{
				//pass
			}
		}
	}
	return map;

}
