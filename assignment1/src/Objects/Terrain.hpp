#pragma once

#include "./geometry/Model.h"
#include "../Opengl_a/Shader.h"
#include <iostream>

#include "../utils/SimplexNoise.h"

const int VERTEX_COUNT = 100;
const int SIZE = 10;

class Terrain
{
public:
	// Constructors & Destructors
	Terrain()
	{
		for (int i = 0; i < VERTEX_COUNT; i++)
		{
			if (smooth > 2.0f)
			{
				smooth *= 0.995;
			}
			for (int j = 0; j < VERTEX_COUNT; j++)
			{

				if (i == j && smooth > 2.0f)
				{
					smooth *= 0.99;
				}
				float x = (float)j / ((float)VERTEX_COUNT - 1) * SIZE;
				float z = (float)i / ((float)VERTEX_COUNT - 1) * SIZE;

				float y = SimplexNoise::noise(x, z) / smooth;

				heights[j][i] = y;

				vertices_temp.push_back(glm::vec3(x, y, z));
				normals_temp.push_back(glm::vec3(0, 1, 0));
			}
		}

		for (int gz = 0; gz < VERTEX_COUNT - 1; gz++)
		{
			for (int gx = 0; gx < VERTEX_COUNT - 1; gx++)
			{
				int topLeft = (gz * VERTEX_COUNT) + gx;
				int topRight = topLeft + 1;
				int bottomLeft = ((gz + 1) * VERTEX_COUNT) + gx;
				int bottomRight = bottomLeft + 1;
				indices.push_back(topLeft);
				indices.push_back(bottomLeft);
				indices.push_back(topRight);
				indices.push_back(topRight);
				indices.push_back(bottomLeft);
				indices.push_back(bottomRight);
			}
		}

		for (unsigned int i = 0; i < indices.size(); i++)
		{
			glm::vec3 vertex = vertices_temp[indices[i]];
			glm::vec3 vertexNormal = normals_temp[indices[i]];
			vertices.push_back(vertex);
			normals.push_back(vertexNormal);
		}
	}

	~Terrain() {};

	float getHeightOfTerrain(float worldX, float worldZ, Model* terrainModel)
	{
		// Find the terrain relative to camera
		float terrainX = worldX - terrainModel->translate_vec.x;
		float terrainZ = worldZ - terrainModel->translate_vec.z;

		float gridSquareSize = (float)SIZE * 3.0f / (float)(VERTEX_COUNT - 1);

		// Determine which square on the grid the user is in
		int gridX = (int)glm::floor(terrainX / gridSquareSize);
		int gridZ = (int)glm::floor(terrainZ / gridSquareSize);

		// Check if the player is even on the grid
		// TODO: Return - 1 and prevent to prevent the user from leaving
		if (gridX >= VERTEX_COUNT - 1 || gridZ >= VERTEX_COUNT - 1 || gridX < 0 || gridZ < 0)
		{
			return 0;
		}

		// Determine where the user is on the individual square
		float xCoord = glm::mod(terrainX, gridSquareSize) / gridSquareSize;
		float zCoord = glm::mod(terrainZ, gridSquareSize) / gridSquareSize;

		float answer;

		// Divide square into two triangles and interpolate where on the triangle the camera is
		if (xCoord <= (1 - zCoord)) {
			answer = barryCentric(glm::vec3(0, heights[gridX][gridZ], 0),
				glm::vec3(1, heights[gridX + 1][gridZ], 0),
				glm::vec3(0, heights[gridX][gridZ + 1], 1),
				glm::vec2(xCoord, zCoord));
		}
		else {
			answer = barryCentric(glm::vec3(1, heights[gridX + 1][gridZ], 0),
				glm::vec3(1, heights[gridX + 1][gridZ + 1], 1),
				glm::vec3(0, heights[gridX][gridZ + 1], 1),
				glm::vec2(xCoord, zCoord));
		}

		return answer;
	}

	// Helper Method - https://en.wikipedia.org/wiki/Barycentric_coordinate_system
	float barryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos) {
		float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
		float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
		float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
		float l3 = 1.0f - l1 - l2;
		return l1 * p1.y + l2 * p2.y + l3 * p3.y;
	}

	float heights[100][100];

	std::vector<glm::vec3> vertices_temp;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> textureCoords;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> normals_temp;

	std::vector<int> indices;

	int relief = (rand() % 6);
	float smooth = 20.0f;
	float smoothInitial = smooth;
	float offset = VERTEX_COUNT / 3;
	int vertexPointer = 0;
};