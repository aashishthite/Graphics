#include "tuboid.h"

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "vertexattributes.h"

using namespace std;

tuboid::tuboid(glm::vec3 clr, GLdouble tuboidRadius, GLdouble ringRadius, bool flipSurface) : lattice()
{
	this->color = clr;
	this->tuboid_rad = tuboidRadius;
	this->ring_rad = ringRadius;
	this->flip_surface = flipSurface;
	this->reflectance = glm::vec3(1.0f);
}

tuboid::tuboid() : lattice()
{
}

int tuboid::vertex_top(int index)
{
	int top = index - this->lattice_width;
	if(top < 0)
	{
		return (top + this->lattice_size - this->lattice_width);
	}
	else
	{
		return top;
	}
}

int tuboid::vertex_top_right(int index)
{
	//Since tuboid has no abrupt ends, it is okay to call other functions here.
	return this->vertex_right(this->vertex_top(index));
}

int tuboid::vertex_right(int index)
{
	int right = index + 1;
	if(right % this->lattice_width == 0)
	{
		return (right + 1 - this->lattice_width);
	}
	else
	{
		return right;
	}
}

int tuboid::vertex_bottom(int index)
{
	int bottom = index + this->lattice_width;
	if(bottom >= this->lattice_size)
	{
		return (bottom + this->lattice_width - this->lattice_size);
	}
	else
	{
		return bottom;
	}
}

int tuboid::vertex_bottom_left(int index)
{
	//Since tuboid has no abrupt ends, it is okay to call other functions here.
	return this->vertex_left(this->vertex_bottom(index));
}

int tuboid::vertex_left(int index)
{
	int left = index - 1;
	if(index % this->lattice_width == 0)
	{
		return (left + this->lattice_width -1);
	}
	else
	{
		return left;
	}
}

void tuboid::DefineVertices()
{
	//Define coordinates and color
	const GLfloat angular_slice_width = 360.0f / (float(this->slice_count));

	glm::vec4 vertex_position;

	glm::mat4 axial_matrix;
	glm::mat4 tuboid_matrix;

	int i,j;
	
	for(i=0; i<lattice_width; i++)
	{
		axial_matrix = glm::rotate(glm::mat4(1.0f), float(i) * angular_slice_width, glm::vec3(0.0f, 1.0f, 0.0f));
		axial_matrix = glm::translate(axial_matrix, glm::vec3(0.0f, 0.0f, this->tuboid_rad));

		for(j=0; j<lattice_width; j++)
		{
			tuboid_matrix = glm::rotate(axial_matrix, float(j) * angular_slice_width, glm::vec3(-1.0f, 0.0f, 0.0f));
			tuboid_matrix = glm::translate(tuboid_matrix, glm::vec3(0.0f, 0.0f, this->ring_rad));

			vertex_position = tuboid_matrix * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
			this->vertices.push_back(VertexAttributesPCN(glm::vec3(vertex_position.x, vertex_position.y, vertex_position.z), color, glm::vec3(0.0f)));
		}
	}
}

bool tuboid::Initialize(int slices)
{
	//Tuboid requires more slices for better aesthetics
	return Super_lattice::Initialize(slices*6);
}