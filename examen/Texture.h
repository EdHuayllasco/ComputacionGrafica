#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include<glad/glad.h>
#include<stb/stb_image.h>

#include"shaderClass.h"

class Texture
{
public:
	GLuint ID;
	GLenum type;
	Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

	// asignamos textura
	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	// Bind a la texture
	void Bind();
	// Unbind a la  texture
	void Unbind();
	// Delete
	void Delete();
};
#endif