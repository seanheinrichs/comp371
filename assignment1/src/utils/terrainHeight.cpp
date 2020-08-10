#include "terrainHeight.h"



terrainHeight::terrainHeight()
{
	
}


terrainHeight::~terrainHeight()
{
}



float terrainHeight::generateHeight(int x, int z) {
	float total = 0;
	float d = (float)pow(2, OCTAVES - 1);
	for (int i = 0; i<OCTAVES; i++) {
		float freq = (float)(pow(2, i) / d);
		float amp = (float)pow(ROUGHNESS, i) * AMPLITUDE;
		total += getInterpolatedNoise((x + xOffset)*freq, (z + zOffset)*freq) * amp;
	}
	return total;
}

float terrainHeight::getInterpolatedNoise(float x, float z) {
	int intX = (int)x;
	int intZ = (int)z;
	float fracX = x - intX;
	float fracZ = z - intZ;

	float v1 = getSmoothNoise(intX, intZ);
	float v2 = getSmoothNoise(intX + 1, intZ);
	float v3 = getSmoothNoise(intX, intZ + 1);
	float v4 = getSmoothNoise(intX + 1, intZ + 1);
	float i1 = interpolate(v1, v2, fracX);
	float i2 = interpolate(v3, v4, fracX);
	return interpolate(i1, i2, fracZ);
}

float terrainHeight::interpolate(float a, float b, float blend) {
	double theta = blend * M_PI;
	float f = (float)(1.0f - cos(theta)) * 0.5f;
	return a * (1.0f - f) + b * f;
}

float terrainHeight::getSmoothNoise(int x, int z) {
	float corners = (getNoise(x - 1, z - 1) + getNoise(x + 1, z - 1) + getNoise(x - 1, z + 1)
		+ getNoise(x + 1, z + 1)) / 16.0f;
	float sides = (getNoise(x - 1, z) + getNoise(x + 1, z) + getNoise(x, z - 1)
		+ getNoise(x, z + 1)) / 8.0f;
	float center = getNoise(x, z) / 4.0f;
	return corners + sides + center;
}

float terrainHeight::getNoise(int x, int z) {
	if (x == 0 && z == 0) {
		return 0;
	}
	else if (z==0){
		return (rand() % x) +z;
	}
	else if (x==0) {
		return (rand() % z) + x;
	}
	else {
		return (rand() % z) + x;
	}
		//return (rand() % (int)seed * 49632 + x ) + z * 325176;
	//random.setSeed(x * 49632 + z * 325176 + seed);
	//return random.nextFloat() * 2.0f - 1.0f;
}

