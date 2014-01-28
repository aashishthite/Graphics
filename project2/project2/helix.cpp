#include "helix.h"

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "vertexattributes.h"

using namespace std;

helix::helix(glm::vec3 clr, GLdouble innerRadius, GLdouble outerRadius, GLdouble Pitch, GLdouble Windings, bool Slope, bool flipSurface) : lattice()
{
	this->color = clr;
	this->flip_surface = flipSurface;
	this->in_rad = innerRadius;
	this->out_rad = outerRadius;
	this->pitch = Pitch;
	this->windings = Windings;
	this->slope = Slope;
	this->reflectance = glm::vec3(1.0f);
}

helix::helix() : lattice()
{
}

int helix::vertex_top(int index)
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

int helix::vertex_top_right(int index)
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

int helix::vertex_right(int index)
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

int helix::vertex_bottom(int index)
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

int helix::vertex_bottom_left(int index)
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

int helix::vertex_left(int index)
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

void helix::DefineVertices()
{
	//Define coordinates and color
	const GLfloat in_bias = ((float(pitch)/2.0f) * 0.95f)/(float(this->slice_count));
	const GLfloat radial_slice_width = (float(out_rad) - float(in_rad)) / (float(this->slice_count));
	const GLfloat angular_slice_width = (360.0f) / (float(this->slice_count));
	const GLfloat axial_slice_width = (float(pitch)) / (float(this->slice_count));
	
	glm::mat4 translate_matrix;
	glm::mat4 rotate_matrix;
	glm::vec4 vertex_position;

	int i;
	int j;
	int sloppy = slope ? -1 : 1;

	for(i=0; i<this->lattice_width; i++)
	{
		for(j=0; j<this->lattice_width; j++)
		{
			translate_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, float(in_rad)+float(radial_slice_width)*float(i), -(float(axial_slice_width)*float(j) + float(sloppy)*float(in_bias)*float(slice_count-i))));
			rotate_matrix = glm::rotate(glm::mat4(1.0f), GLfloat(angular_slice_width*float(j)), glm::vec3(0.0f, 0.0f, -1.0f));
			vertex_position = rotate_matrix * translate_matrix * glm::vec4(0.0f,0.0f,0.0f,1.0f);
			this->vertices.push_back(VertexAttributesPCN(glm::vec3(vertex_position.x, vertex_position.y, vertex_position.z), color, glm::vec3(0.0f)));
		}
	}
}



bool helix::Initialize(int slices)
{
	//Tuboid requires more slices for better aesthetics
	return Super_lattice::Initialize(slices*6);
}

void helix::Draw(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size)
{
	int i;
	for(i=0; i<windings; i++)
	{
		Super_lattice::Draw(projection, glm::translate(modelview, glm::vec3(0.0f, 0.0f, float(pitch)*float(i))),size);
	}
}