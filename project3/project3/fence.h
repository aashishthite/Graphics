#pragma once
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include "object.h"
#include "shader.h"
#include "cube.h"

class fence
{
	private:
		glm::vec3 GetColor(GLint color);
		cube* mycube;
	public:
		bool fence::Draw(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size, GLfloat radius, GLfloat angle);
		fence();
		void FlipNormals(void);
		bool Initialize(int slices);
		void TakeDown(void);
		~fence();
		void switch_shader(void);
};

class fence_params
{
	public:
		GLfloat radius;
		GLfloat angle;
		fence_params(const GLfloat & Rag, const GLfloat & Ang,b2World* thisworld);
		fence_params(const fence_params & other);
		b2Body* body;
};