#pragma once
#include <string>

class Texture
{

public: 
	unsigned int renderer_id;
	std::string filePath;
	unsigned char* localBuffer;
	int width, height, BPP;

	Texture(const std::string& path);
	Texture();
	~Texture();

	void bind(unsigned int slot = 0) const;
	void unbind() const;

	inline int GetWidth() const { return width; }
	inline int GetHeight() const { return height; }


};