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
#include "cylinder.h"
#include "constants.h"

class wavy_cylinder : public cylinder
{
	private:
		//typedef lattice Super_lattice;
		//typedef cylinder Super_cylinder;
	public:
		wavy_cylinder(glm::vec3 clr, GLdouble baseRadius, GLdouble topRadius, GLdouble Height, bool flipSurface);
		void DefineVertices(void);
};