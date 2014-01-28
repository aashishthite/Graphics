#include "debug.h"
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

using namespace std;

debug::debug(bool Grid, bool Axis) : Object()
{
	grid = Grid;
	axis = Axis;
}

bool debug::Initialize(int slices)
{
	if (this->GLReturnedError("debug::Initialize - on entry"))
		return false;

	if (!super::Initialize())
	{
		cerr << "debug::Initialize - Unable to initialize Object" << endl;
		return false;
	}

	if(axis)
	{
		//x axis
		this->normal_vertices.push_back(VertexAttributesPC(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
		this->normal_vertices.push_back(VertexAttributesPC(glm::vec3(5.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
		this->normal_indices.push_back(this->normal_vertices.size() - 2);
		this->normal_indices.push_back(this->normal_vertices.size() - 1);

		//y axis
		this->normal_vertices.push_back(VertexAttributesPC(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
		this->normal_vertices.push_back(VertexAttributesPC(glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
		this->normal_indices.push_back(this->normal_vertices.size() - 2);
		this->normal_indices.push_back(this->normal_vertices.size() - 1);

		//z axis
		this->normal_vertices.push_back(VertexAttributesPC(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
		this->normal_vertices.push_back(VertexAttributesPC(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
		this->normal_indices.push_back(this->normal_vertices.size() - 2);
		this->normal_indices.push_back(this->normal_vertices.size() - 1);
	}

	if(grid)
	{
		int i;
		//y-z plane
		for(i = -5; i <= 5; i++)
		{
			this->normal_vertices.push_back(VertexAttributesPC(glm::vec3(0.0f, float(i), -5.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
			this->normal_vertices.push_back(VertexAttributesPC(glm::vec3(0.0f, float(i), 5.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
			this->normal_indices.push_back(this->normal_vertices.size() - 2);
			this->normal_indices.push_back(this->normal_vertices.size() - 1);
		}
		for(i = -5; i <= 5; i++)
		{
			this->normal_vertices.push_back(VertexAttributesPC(glm::vec3(0.0f, -5.0f, float(i)), glm::vec3(1.0f, 0.0f, 0.0f)));
			this->normal_vertices.push_back(VertexAttributesPC(glm::vec3(0.0f, 5.0f, float(i)), glm::vec3(1.0f, 0.0f, 0.0f)));
			this->normal_indices.push_back(this->normal_vertices.size() - 2);
			this->normal_indices.push_back(this->normal_vertices.size() - 1);
		}
	
		//x-z plane
		for(i = -5; i <= 5; i++)
		{
			this->normal_vertices.push_back(VertexAttributesPC(glm::vec3(-5.0f, 0.0f, float(i)), glm::vec3(0.0f, 1.0f, 0.0f)));
			this->normal_vertices.push_back(VertexAttributesPC(glm::vec3(5.0f, 0.0f, float(i)), glm::vec3(0.0f, 1.0f, 0.0f)));
			this->normal_indices.push_back(this->normal_vertices.size() - 2);
			this->normal_indices.push_back(this->normal_vertices.size() - 1);
		}
		for(i = -5; i <= 5; i++)
		{
			this->normal_vertices.push_back(VertexAttributesPC(glm::vec3(float(i), 0.0f, -5.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
			this->normal_vertices.push_back(VertexAttributesPC(glm::vec3(float(i), 0.0f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
			this->normal_indices.push_back(this->normal_vertices.size() - 2);
			this->normal_indices.push_back(this->normal_vertices.size() - 1);
		}
	
		//x-y plane
		for(i = -5; i <= 5; i++)
		{
			this->normal_vertices.push_back(VertexAttributesPC(glm::vec3(float(i), -5.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
			this->normal_vertices.push_back(VertexAttributesPC(glm::vec3(float(i), 5.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
			this->normal_indices.push_back(this->normal_vertices.size() - 2);
			this->normal_indices.push_back(this->normal_vertices.size() - 1);
		}
		for(i = -5; i <= 5; i++)
		{
			this->normal_vertices.push_back(VertexAttributesPC(glm::vec3(-5.0f, float(i), 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
			this->normal_vertices.push_back(VertexAttributesPC(glm::vec3(5.0f, float(i), 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
			this->normal_indices.push_back(this->normal_vertices.size() - 2);
			this->normal_indices.push_back(this->normal_vertices.size() - 1);
		}
	}

	if (this->normal_vertices.size() > 0)
	{
		if (!this->PostGLInitialize(&this->normal_array_handle, &this->normal_coordinate_handle, this->normal_vertices.size() * sizeof(VertexAttributesPC), &this->normal_vertices[0]))
		{
			cerr << "debug::Initialize - PostGLInitialize for debug features failed" << endl;
			return false;
		}
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttributesPC), (GLvoid *) 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttributesPC), (GLvoid *) (sizeof(glm::vec3) * 1));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	if (!this->solid_color.Initialize("solid_shader.vert", "solid_shader.frag"))
	{
		cerr << "debug::Initialize - Initializing solid_shader failed" << endl;
		return false;
	}

	if (this->GLReturnedError("debug::Initialize - on exit"))
	{
		return false;
	}
	return true;
}

void debug::TakeDown()
{
	this->solid_color.TakeDown();
	super::TakeDown();
}

bool debug::Draw(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size)
{
	if (this->normal_vertices.size() > 0)
	{
		if (this->GLReturnedError("debug::Draw - on entry"))
			return false;

		glEnable(GL_DEPTH_TEST);
		glm::mat4 mvp = projection * modelview;

		this->solid_color.Use();
		this->solid_color.CommonSetup(0.0f, glm::value_ptr(size), glm::value_ptr(projection), glm::value_ptr(modelview), glm::value_ptr(mvp), glm::value_ptr(glm::mat3(0.0f)),glm::vec3(0.0f));
		glBindVertexArray(this->normal_array_handle);
		glDrawElements(GL_LINES , this->normal_indices.size(), GL_UNSIGNED_INT , &this->normal_indices[0]);
		glBindVertexArray(0);
		glUseProgram(0);
	}
	return true;
}

void debug::FlipAxis(void)
{
	axis = !axis;
}

void debug::FlipGrid(void)
{
	grid = !grid;
}