#pragma once
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "object.h"
#include "shader.h"
#include "texturedshader.h"
#include "lattice.h"

class textured_lattice : public lattice
{
	protected:
		std::vector<VertexAttributesPCNT> vertices;
		unsigned int texID;
	public:
		void Draw(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size);
		bool Initialize(int slices, const char* texture_file);
		void TakeDown(void);
		TexturedShader texture_shader;
		textured_lattice();
		void DefineNormals(void);
		void DefineTriangles(void);
};