#define STB_IMAGE_IMPLEMENTATION

#include "Texture.h"
#include "../utils/stb_image.h"
#include "../utils/gl_error.h"

Texture::Texture(const std::string& path) : filePath(path), localBuffer(nullptr), width(0), height(0), BPP(0)
{
	//flip image for orientation to reflect opengl's
	stbi_set_flip_vertically_on_load(1);
	localBuffer = stbi_load(path.c_str(), &width, &height, &BPP, 4);

	if(localBuffer == NULL)
		std::cout << "failed to load image" << std::endl;

	GLCall(glGenTextures(1, &renderer_id));
	//GLCall(glActiveTexture(GL_TEXTURE0));
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
		std::cout << "images was loaded and now its deleted" << std::endl;
	}
}

Texture::Texture() : filePath(""), localBuffer(nullptr), width(0), height(0), BPP(0) {}

Texture::~Texture() {}

void Texture::bind(unsigned int slot) const 
{
	GLCall(glActiveTexture(slot ));
	GLCall(glBindTexture(GL_TEXTURE_2D, renderer_id));
}

void Texture::unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D,0))
}