#pragma once
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "object.h"
#include "shader.h"
#include "cylinder.h"
#include "cube.h"
#include "textured_square.h"
#include "fbo.h"

class jumbotron
{
	private:
		glm::vec3 GetColor(GLint color);
		cylinder* pillar;
		cube* frame;
		textured_square* screen;
	public:
		bool jumbotron::Draw(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size, GLfloat radius, GLfloat angle, GLfloat height);
		jumbotron();
		void FlipNormals(void);
		bool Initialize(int slices);
		void TakeDown(void);
		~jumbotron();
		void switch_shader(void);
};

class jumbotron_params
{
	public:
		GLfloat radius;
		GLfloat angle;
		GLfloat height;
		jumbotron_params(const GLfloat & Rad, const GLfloat & Ang, const GLfloat & Ht);
		jumbotron_params(const jumbotron_params & other);
};