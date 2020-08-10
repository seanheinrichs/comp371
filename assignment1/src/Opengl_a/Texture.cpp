/*
*
*Texture class highly inspired from this video
*
*source: https://www.youtube.com/watch?v=n4k7ANAFsIQ&t=1161s
*
*/

#define STB_IMAGE_IMPLEMENTATION

#include "Texture.h"
#include "../utils/stb_image.h"
#include "../utils/gl_error.h"
#include <iostream>
#include <string>
#include "../Common.h"
#define MAX_TEX 32


void Texture::TextureFromFile(const char* path)
{
	

	//flip image for orientation to reflect opengl's
	stbi_set_flip_vertically_on_load(1);
	localBuffer = stbi_load(path, &width, &height, &BPP, 4);

	if (localBuffer)
	{
		GLenum format;
		if (BPP == 1)
			format = GL_RED;
		else if (BPP == 3)
			format = GL_RGB;
		else if (BPP == 4)
			format = GL_RGBA;


		GLCall(glGenTextures(1, &renderer_id));
		glBindTexture(GL_TEXTURE_2D, renderer_id);

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);
		glGenerateMipmap(GL_TEXTURE_2D);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		

		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(localBuffer);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(localBuffer);
	}

	/*

	if (localBuffer == NULL)
		std::cout << "failed to load image" << std::endl;
	else
		std::cout << "loaded " << path << std::endl;

	GLCall(glGenTextures(1, &renderer_id));
	GLCall(glBindTexture(GL_TEXTURE_2D, renderer_id));



	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer));

	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (localBuffer)
	{
		stbi_image_free(localBuffer);
		//std::cout << "images was loaded and now its deleted" << std::endl;
	}

	*/
}


/*
*
*Read texture image and create the texture itself in opengl
*
*/
Texture::Texture(const std::string& path) : filePath(path), localBuffer(nullptr), width(0), height(0), BPP(0)
{
	int texIndex = -1; 
	for (unsigned int i = 0; i < MAX_TEX; i++)
	{
		if (std::string(path) == g_textures[i].path)
		{
			texIndex = i;
			break;
		}

		std::cout << std::string(path) << "  and  " << g_textures[i].path << "not matching" << std::endl;

	}
	if (texIndex == -1) 
	{
		Texture::path = path;
		TextureFromFile(path.c_str());
	}
	else 
	{
		this->renderer_id =  g_textures[texIndex].renderer_id;
		this->path = g_textures[texIndex].path;
	}
	
}

Texture::Texture() : filePath(""), localBuffer(nullptr), width(0), height(0), BPP(0) {}

Texture::~Texture() {}



/*
*
*bind a texture to a slot
*
*/
void Texture::bind(unsigned int slot) const 
{
	GLCall(glActiveTexture(slot ));
	GLCall(glBindTexture(GL_TEXTURE_2D, renderer_id));
}

void Texture::unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D,0))
}