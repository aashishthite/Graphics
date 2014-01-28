#include "cylinder.h"

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "vertexattributes.h"

using namespace std;

cylinder::cylinder(glm::vec3 clr, GLdouble baseRadius, GLdouble topRadius, GLdouble Height, bool flipSurface) : lattice()
{
	this->color = clr;
	this->base_rad = baseRadius;
	this->top_rad = topRadius;
	this->height = Height;
	this->flip_surface = flipSurface;
	this->reflectance = glm::vec3(1.0f);
}

cylinder::cylinder() : lattice()
{
}

int cylinder::vertex_top(int index)
{
	int top = index - this->lattice_width;
	if(top < 0)
	{
		return index;
	}
	else
	{
		return top;
	}
}

int cylinder::vertex_top_right(int index)
{
	int top = index - this->lattice_width;
	if(top < 0)
	{
		return index;
	}
	else
	{
		int right = top + 1;
		if(right % this->lattice_width == 0)
		{
			return (right + 1 - this->lattice_width);
		}
		else
		{
			return right;
		}
	}
}

int cylinder::vertex_right(int index)
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

int cylinder::vertex_bottom(int index)
{
	int bottom = index + this->lattice_width;
	if(bottom >= this->lattice_size)
	{
		return index;
	}
	else
	{
		return bottom;
	}
}

int cylinder::vertex_bottom_left(int index)
{
	int bottom = index + this->lattice_width;
	if(bottom >= this->lattice_size)
	{
		return index;
	}
	else
	{
		int left = bottom - 1;
		if(bottom % this->lattice_width == 0)
		{
			return (left + this->lattice_width - 1);
		}
		else
		{
			return left;
		}
	}
}

int cylinder::vertex_left(int index)
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

void cylinder::DefineVertices()
{
	//Define coordinates and color
	const GLfloat axial_slice_width = float(height) / (float(this->slice_count));
	const GLfloat radial_slice_width = (float(top_rad) - float(base_rad))/ (float(this->slice_count));
	const GLfloat angular_slice_width = 360.0f / (float(this->slice_count));

	GLfloat ax_coord;
	GLfloat rad_coord;
	GLfloat angle_coord;

	glm::vec4 vertex_position;
	glm::mat4 translate_matrix = glm::mat4(1.0f);
	glm::mat4 rotate_matrix = glm::mat4(1.0f);

	int i,j;
	
	for(i=0; i<lattice_width; i++)
	{
		ax_coord = float(i) * axial_slice_width;
		rad_coord = float(this->base_rad) + float(i) * radial_slice_width;
		translate_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, rad_coord, ax_coord));
		for(j=0; j<lattice_width; j++)
		{
			angle_coord = float(j) * angular_slice_width;
			rotate_matrix = glm::rotate(glm::mat4(1.0f), angle_coord, glm::vec3(0.0f, 0.0f, -1.0f));
			vertex_position = rotate_matrix * translate_matrix * glm::vec4(0.0f,0.0f,0.0f,1.0f);
			this->vertices.push_back(VertexAttributesPCN(glm::vec3(vertex_position.x, vertex_position.y, vertex_position.z), color, glm::vec3(0.0f)));
		}
	}
}