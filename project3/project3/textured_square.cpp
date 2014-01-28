#include "textured_square.h"

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "vertexattributes.h"


textured_square::textured_square(glm::vec3 clr, bool flipSurface) : textured_lattice()
{
	this->color = clr;
	this->flip_surface = flipSurface;
}

textured_square::textured_square() : textured_lattice()
{
}

bool textured_square::Initialize(int slices, const char* texture_file, FrameBufferObject* fbo)
{
	//TODO: to be fixed
	return Super_tex_lat::Initialize(1, texture_file, fbo);
}

int textured_square::vertex_top(int index)
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

int textured_square::vertex_top_right(int index)
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
			return index;
		}
		else
		{
			return right;
		}
	}
}

int textured_square::vertex_right(int index)
{
	int right = index + 1;
	if(right % this->lattice_width == 0)
	{
		return index;
	}
	else
	{
		return right;
	}
}

int textured_square::vertex_bottom(int index)
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

int textured_square::vertex_bottom_left(int index)
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
			return index;
		}
		else
		{
			return left;
		}
	}
}

int textured_square::vertex_left(int index)
{
	int left = index - 1;
	if(index % this->lattice_width == 0)
	{
		return index;
	}
	else
	{
		return left;
	}
}

void textured_square::DefineVertices()
{
	//Define coordinates and color
	const GLfloat slice_width = 1.0f / (float(this->slice_count));
	const GLfloat x_min = -0.5f;
	const GLfloat y_min = 0.5f;

	GLfloat x_coord;
	GLfloat y_coord;
	GLfloat tex_x_coord;
	GLfloat tex_y_coord;
	const GLfloat z_coord = 0;

	glm::vec3 vertex_position;

	int i,j;
	
	for(i=0; i<lattice_width; i++)
	{
		y_coord = y_min - float(i) * slice_width;
		tex_y_coord = float(i)/(float(this->lattice_width)-1.0f);
		for(j=0; j<this->lattice_width; j++)
		{
			x_coord = x_min + float(j) * slice_width;
			tex_x_coord = float(j)/(float(this->lattice_width)-1.0f);
			vertex_position = glm::vec3(x_coord, y_coord, z_coord);
			this->vertices.push_back(VertexAttributesPCNT(vertex_position, color, glm::vec3(0.0f),glm::vec2(tex_x_coord,tex_y_coord)));
		}
	}
}