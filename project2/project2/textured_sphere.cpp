#include "textured_sphere.h"

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "vertexattributes.h"

using namespace std;

textured_sphere::textured_sphere(glm::vec3 clr, GLdouble Radius, bool flipSurface) : textured_lattice()
{
	this->color = clr;
	this->rad = Radius;
	this->flip_surface = flipSurface;
	this->reflectance = glm::vec3(1.0f);
}

textured_sphere::textured_sphere() : textured_lattice()
{
}


bool textured_sphere::Initialize(int slices, const char* texture_file)
{
	//TODO: to be fixed
	return Super_tex_lat::Initialize(slices, texture_file);
}

int textured_sphere::vertex_top(int index)
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

int textured_sphere::vertex_top_right(int index)
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

int textured_sphere::vertex_right(int index)
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

int textured_sphere::vertex_bottom(int index)
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

int textured_sphere::vertex_bottom_left(int index)
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

int textured_sphere::vertex_left(int index)
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

void textured_sphere::DefineVertices()
{
	//Define coordinates and color
	const GLfloat longitudinal_slice_width = 360.0f / (float(this->slice_count));
	const GLfloat lattitudinal_slice_width = 180.0f / (float(this->slice_count));

	GLfloat lat_coord;
	GLfloat long_coord;
	//GLfloat angle_coord;

	GLfloat tex_x_coord;
	GLfloat tex_y_coord;

	glm::vec4 vertex_position;
	glm::mat4 translate_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, rad));;
	glm::mat4 rotate_matrix = glm::mat4(1.0f);

	int i,j;
	
	for(i=0; i<lattice_width; i++)
	{
		lat_coord = -90.0f  + float(i) * lattitudinal_slice_width;
		for(j=0; j<lattice_width; j++)
		{
			long_coord = float(j) * longitudinal_slice_width;
			rotate_matrix = glm::rotate(glm::mat4(1.0f), long_coord, glm::vec3(0.0f, 1.0f, 0.0f));
			rotate_matrix = glm::rotate(rotate_matrix, lat_coord, glm::vec3(1.0f, 0.0f, 0.0f));
			vertex_position = rotate_matrix * translate_matrix * glm::vec4(0.0f,0.0f,0.0f,1.0f);
			tex_x_coord = 0.5f + (lat_coord/180.0f);
			tex_y_coord = long_coord/360.0f;
			this->vertices.push_back(VertexAttributesPCNT(glm::vec3(vertex_position.x, vertex_position.y, vertex_position.z), color, glm::vec3(0.0f), glm::vec2(tex_x_coord,tex_y_coord)));
		}
	}
}