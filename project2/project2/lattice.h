#pragma once
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "object.h"
#include "shader.h"

class lattice : public Object
{
	protected:
		typedef Object super;
		std::vector<VertexAttributesPCN> vertices;
		int slice_count;
		int lattice_width;
		int lattice_size;
		bool flip_surface;
		glm::vec3 reflectance;

		glm::vec3 NormalizeVector(glm::vec3);
		virtual void DefineNormals(void);
		virtual void DefineTriangles(void);
	public:
		///////////////////////////////////
		//the following seven functions hould be defined in a derived class which defines a particular surface
		virtual void DefineVertices(void) = 0;
		virtual int vertex_top(int) = 0;
		virtual int vertex_top_right(int) = 0;
		virtual int vertex_right(int) = 0;
		virtual int vertex_bottom(int) = 0;
		virtual int vertex_bottom_left(int) = 0;
		virtual int vertex_left(int) = 0;
		////////////////////////////////////
		void switch_shader(void);

		void Draw(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size);
		lattice();

		bool Initialize(int slices);
		void TakeDown(void);
		//TODO: make these private?
		Shader phong_shader;
		Shader flat_shader;
		Shader gouraud_shader;
		Shader solid_color;
		Shader* current_shader;
};