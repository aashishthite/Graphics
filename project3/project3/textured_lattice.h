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
#include "fbo.h"

class textured_lattice : public lattice
{
	protected:
		std::vector<VertexAttributesPCNT> vertices;
		unsigned int texID;
		FrameBufferObject* myfbo;
	public:
		bool Draw(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size, const GLfloat Wcrop, const GLfloat Hcrop, GLint fbo_attachment, const glm::vec2 striker_coord);
		bool Initialize(int slices, const char* texture_file, FrameBufferObject* fbo);
		void TakeDown(void);
		TexturedShader texture_shader;
		textured_lattice();
		void DefineNormals(void);
		void DefineTriangles(void);
};