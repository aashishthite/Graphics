#pragma once
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "lattice.h"
#include "object.h"
#include "shader.h"
#include "square.h"

class cube : public square
{
	private:
		typedef lattice Super_lattice;
	public:
		cube(glm::vec3 clr, bool flipSurface);
		bool Draw(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size);
};