#pragma once
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "object.h"
#include "shader.h"

class debug : public Object
{
	private:
		bool grid;
		bool axis;
		typedef Object super;
		//Note: the vertices fo axis and grid are stores in the normal_vertices (member of base class "Object").
		//Hence there is no need to declare other vertices here
	public:
		debug(bool Grid, bool Axis);
		void FlipAxis(void);
		void FlipGrid(void);

		//slices is ignored
		bool Initialize(int slices);
		void Draw(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size);
		void TakeDown(void);

		Shader solid_color;
};