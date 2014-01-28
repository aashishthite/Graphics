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

class helix : public lattice
{
	protected:
		glm::vec3 color;
		GLdouble in_rad;
		GLdouble out_rad;
		GLdouble pitch;
		GLdouble windings;
		bool slope;
		int vertex_top(int);
		int vertex_top_right(int);
		int vertex_right(int);
		int vertex_bottom(int);
		int vertex_bottom_left(int);
		int vertex_left(int);
		typedef lattice Super_lattice;
	public:
		helix();
		helix(glm::vec3 clr, GLdouble innerRadius, GLdouble outerRadius, GLdouble Pitch, GLdouble Windings, bool Slope, bool flipSurface);
		void DefineVertices(void);
		bool Initialize(int slices);
		bool Draw(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size);
};