#pragma once
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "object.h"
#include "shader.h"
#include "textured_square.h"

class textured_cuboid : public textured_square
{
	protected:
		GLint blocks_x;
		GLint blocks_y;
		GLint blocks_z;
		typedef textured_lattice Super_tex_lattice;
	public:
		textured_cuboid();
		textured_cuboid(glm::vec3 clr, GLint x, GLint y, GLint z, bool flipSurface);
		void Draw(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size);
};