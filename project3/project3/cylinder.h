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

class cylinder : public lattice
{
	protected:
		glm::vec3 color;
		GLdouble base_rad;
		GLdouble top_rad;
		GLdouble height;
		int vertex_top(int);
		int vertex_top_right(int);
		int vertex_right(int);
		int vertex_bottom(int);
		int vertex_bottom_left(int);
		int vertex_left(int);
	public:
		cylinder();
		cylinder(glm::vec3 clr, GLdouble baseRadius, GLdouble topRadius, GLdouble Height, bool flipSurface);
		void DefineVertices(void);
};