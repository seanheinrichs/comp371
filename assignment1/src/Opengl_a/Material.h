#pragma once
#include <glm/glm.hpp>
#include "shader.h" 
#include "Texture.h" 
#include <vector>


enum MatType
{
	TEXTURE_OFF =0,
	TEXTURE_D,
	TEXTURE_DS
};


/*
Material Class

Depends on: N/A

Description: An abastraction for Phong lighting materials that works with assimp model loading. This material class
complies with the wavefront .mtl material format for its naming conventions. (WIKIPEDIA)It provides
custom shader settings for the different options available: TEXTURE_OFF, TEXTURE_D, TEXTURE_DS

NAMING CONVENTION SOURCE(WIKIPEDIA): https://en.wikipedia.org/wiki/Wavefront_.obj_file

MatType type;
ka: abient color
kd: diffuse color
ks: specular color
ke: emmissive color
Ns: shininess
Ni: optical density
d: the transparency
illum: the illuminations strength
textures: a vector of textures containing all the textures needed

*/
class Material
{
public:
	MatType type;
	glm::vec3 ka, kd, ks, ke;
	float Ns, Ni, d;
	int illum;
	std::vector<Texture> textures;

	Material();

	Material(
		glm::vec3 ka,
		glm::vec3 kd = glm::vec3(1.0f),
		glm::vec3 ks = glm::vec3(1.0f),
		glm::vec3 ke = glm::vec3(1.0f),
		float Ns = 10.00, //shininess
		float Ni = 1.45, //optical density
		float d = 1.0, //transparency
		int illum = 2,
		MatType type = TEXTURE_OFF);

	Material(glm::vec3 kd, glm::vec3 ks, float Ns);

	Material(glm::vec3 kd, Texture map_kd, float Ns);

	

	bool equals(Material comp);
	bool equals(Material* comp);

	void setShader(Shader* shader);
	void addTexture(Texture texture);


};

