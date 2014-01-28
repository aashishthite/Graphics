#pragma once
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "object.h"
#include "shader.h"
#include "wavy_cylinder.h"

class tree
{
	private:
		glm::vec3 GetColor(GLint color);
		wavy_cylinder* leaves;
	public:
		bool tree::Draw(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size, GLfloat pos_x, GLfloat pos_y, GLfloat pos_z, GLfloat height);
		tree();
		void FlipNormals(void);
		bool Initialize(int slices);
		void TakeDown(void);
		~tree();
		void switch_shader(void);
};

class tree_params
{
	public:
		GLfloat pos_x;
		GLfloat pos_y;
		GLfloat pos_z;
		GLfloat tree_height; //In multiples of 1 foot
		tree_params(const GLfloat & Posx, const GLfloat & Posy, const GLfloat & Posz, const GLfloat & SeatHt);
		tree_params(const tree_params & other);
};