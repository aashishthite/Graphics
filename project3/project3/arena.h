#pragma once
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "object.h"
#include "shader.h"
#include "textured_square.h"
#include "disk.h"
#include "cylinder.h"
#include "jumbotron.h"

class arena
{
	private:
		glm::vec3 GetColor(GLint color);
		textured_square* floor;
		textured_square* floor_top;
		disk* ground;

		//Objects for gallery
		cylinder* cylinder1;
		cylinder* cylinder2;
		cylinder* cylinder3;
		cylinder* cylinder4;
		cylinder* cylinder5;
		cylinder* cylinder6;
		disk* disk1;
		disk* disk2;
		disk* disk3;
		disk* disk4;
		disk* disk5;
		disk* disk6;

		//Objects for jumbotron
		jumbotron* jumbo;
		std::vector<jumbotron_params> jumbotron_properties;

	public:
		bool arena::Draw(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size, GLfloat strike_x, GLfloat strike_y);
		arena();
		std::vector<lattice*> arenaComponents;
		void FlipNormals(void);
		bool Initialize(int slices);
		void TakeDown(void);
		~arena();
		void switch_shader(void);
		void switch_special_mode(void);
};