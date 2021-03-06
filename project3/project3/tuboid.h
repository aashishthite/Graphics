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

class tuboid : public lattice
{
	protected:
		glm::vec3 color;
		GLdouble tuboid_rad;
		GLdouble ring_rad;
		int vertex_top(int);
		int vertex_top_right(int);
		int vertex_right(int);
		int vertex_bottom(int);
		int vertex_bottom_left(int);
		int vertex_left(int);
		typedef lattice Super_lattice;
	public:
		tuboid();
		tuboid(glm::vec3 clr, GLdouble tuboidRadius, GLdouble ringRadius, bool flipSurface);
		bool Initialize(int slices);
		void DefineVertices(void);
};