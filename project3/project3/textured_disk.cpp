#include "textured_disk.h"

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "vertexattributes.h"

textured_disk::textured_disk(glm::vec3 clr, GLdouble innerRadius, GLdouble outerRadius, bool flipSurface) : textured_lattice()
{
	this->color = clr;
	this->in_rad = innerRadius;
	this->out_rad = outerRadius;
	this->flip_surface = flipSurface;
}

textured_disk::textured_disk() : textured_lattice()
{
}

bool textured_disk::Initialize(int slices, const char* texture_file, FrameBufferObject* fbo)
{
	//TODO: to be fixed
	return Super_tex_lat::Initialize(slices, texture_file, fbo);
}

int textured_disk::vertex_top(int index)
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

int textured_disk::vertex_top_right(int index)
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

int textured_disk::vertex_right(int index)
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

int textured_disk::vertex_bottom(int index)
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

int textured_disk::vertex_bottom_left(int index)
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

int textured_disk::vertex_left(int index)
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

void textured_disk::DefineVertices()
{
	//Define coordinates and color
	const GLfloat radial_slice_width = (float(this->out_rad) - float(this->in_rad)) / (float(this->slice_count));
	const GLfloat angular_slice_width = 360.0f / (float(this->slice_count));

	GLfloat rad_coord;
	GLfloat angle_coord;

	GLfloat tex_x_coord;
	GLfloat tex_y_coord;

	glm::vec4 vertex_position;
	glm::mat4 translate_matrix = glm::mat4(1.0f);
	glm::mat4 rotate_matrix = glm::mat4(1.0f);

	int i,j;
	
	for(i=0; i<this->lattice_width; i++)
	{
		rad_coord = float(this->in_rad) + float(i) * radial_slice_width;
		translate_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -(rad_coord), 0.0f));
		for(j=0; j<this->lattice_width; j++)
		{
			angle_coord = float(j) * angular_slice_width;
			rotate_matrix = glm::rotate(glm::mat4(1.0f), angle_coord, glm::vec3(0.0f, 0.0f, 1.0f));
			vertex_position = rotate_matrix * translate_matrix * glm::vec4(0.0f,0.0f,0.0f,1.0f);
			tex_x_coord = (float(vertex_position.x) + float(this->out_rad))/(2.0f * float(this->out_rad));
			tex_y_coord = (float(vertex_position.y) + float(this->out_rad))/(2.0f * float(this->out_rad));
			this->vertices.push_back(VertexAttributesPCNT(glm::vec3(vertex_position.x, vertex_position.y, vertex_position.z), color, glm::vec3(0.0f), glm::vec2(tex_x_coord,tex_y_coord)));
		}
	}
}