#pragma once
#include "Opengl_a/Texture.h"
#include "GL/glew.h"
#include <glm/gtx/transform2.hpp>


extern Texture* g_textures;
extern GLenum* g_texLocations;
extern float *g_shininess;
extern glm::vec3 *g_specularStrength;