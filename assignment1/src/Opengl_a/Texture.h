#pragma once
#include <string>

/*
*Texture 
*
*Description: provides a simple interface for creating textures and binding them to interfaces in opengl
*
*/
class Texture
{

public: 
	unsigned int renderer_id;
	std::string filePath;
	unsigned char* localBuffer;
	int width, height, BPP;

	std::string id, type, path;
	

	void TextureFromFile(const char* path);
	Texture(const std::string& path);
	Texture();
	~Texture();

	void bind(unsigned int slot = 0) const;
	void unbind() const;

	inline int GetWidth() const { return width; }
	inline int GetHeight() const { return height; }


};