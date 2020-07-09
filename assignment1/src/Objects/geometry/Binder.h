#pragma once

class Model;

class Binder
{

public: 
	Binder(bool position, bool texture, bool color);
	void bindArrayBuffer(bool unbind, Model* model);
	void deallocate();
	Binder();
	void bind();
	void unbind();

	unsigned int vao, vbo;
	bool position, texture, color;

};