#pragma once
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "object.h"
#include "shader.h"
#include "lattice.h"

class sphere : public lattice
{
	protected:
		glm::vec3 color;
		GLdouble rad;
		int vertex_top(int);
		int vertex_top_right(int);
		int vertex_right(int);
		int vertex_bottom(int);
		int vertex_bottom_left(int);
		int vertex_left(int);
	public:
		sphere();
		sphere(glm::vec3 clr, GLdouble Radius, bool flipSurface);
		void DefineVertices(void);
};