#pragma once
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "object.h"
#include "shader.h"
#include "textured_lattice.h"

class textured_disk : public textured_lattice
{
	protected:
		glm::vec3 color;
		GLdouble in_rad;
		GLdouble out_rad;
		int vertex_top(int);
		int vertex_top_right(int);
		int vertex_right(int);
		int vertex_bottom(int);
		int vertex_bottom_left(int);
		int vertex_left(int);
		typedef textured_lattice Super_tex_lat;
	public:
		textured_disk();
		textured_disk(glm::vec3 clr, GLdouble innerRadius, GLdouble outerRadius, bool flipSurface);
		void DefineVertices(void);
		bool Initialize(int slices, const char* texture_file);
};