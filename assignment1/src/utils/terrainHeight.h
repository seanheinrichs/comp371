#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <math.h>

# define M_PI           3.14159265358979323846  /* pi */
class terrainHeight
{
private:
	 float AMPLITUDE = 75.0f;
	 int OCTAVES = 3;
	  float ROUGHNESS = 0.3f;

	  float seed = rand() % 10000000;

	 int xOffset = 0;
	 int zOffset = 0;

public:
	terrainHeight();
	~terrainHeight();

	float generateHeight(int x, int z);
	float getNoise(int x, int z);
	float getSmoothNoise(int x, int z);
	float interpolate(float a, float b, float blend);
	float getInterpolatedNoise(float x, float z);
};

