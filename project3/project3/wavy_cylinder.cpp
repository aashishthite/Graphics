#include "wavy_cylinder.h"

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "vertexattributes.h"

wavy_cylinder::wavy_cylinder(glm::vec3 clr, GLdouble baseRadius, GLdouble topRadius, GLdouble Height, bool flipSurface) : cylinder()
{
	this->color = clr;
	this->base_rad = baseRadius;
	this->top_rad = topRadius;
	this->height = Height;
	this->flip_surface = flipSurface;
	this->reflectance = glm::vec3(0.0f);
}

void wavy_cylinder::DefineVertices(void)
{

	//Super_cylinder::DefineVertices();
	//Define coordinates and color
	const GLfloat axial_slice_width = float(height) / (float(this->slice_count));
	const GLfloat radial_slice_width = (float(top_rad) - float(base_rad))/ (float(this->slice_count));
	const GLfloat angular_slice_width = 360.0f / (float(this->slice_count));

	GLfloat ax_coord;
	GLfloat rad_coord;
	GLfloat angle_coord;

	GLfloat pertubation;

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

			pertubation = rad_coord * 0.3f * (glm::cos(angle_coord * 20.0f * PI/(360.0f)) * glm::cos(ax_coord * 10.0f));
			//pertubation = rad_coord * 0.2f * (glm::pow(glm::cos(angle_coord * 20.0f * PI/(360.0f)),0.5f) * glm::cos(ax_coord * 9.0f));

			vertex_position = rotate_matrix * glm::translate(translate_matrix, glm::vec3(0.0f, pertubation, 0.0f)) * glm::vec4(0.0f,0.0f,0.0f,1.0f);
			this->vertices.push_back(VertexAttributesPCN(glm::vec3(vertex_position.x, vertex_position.y, vertex_position.z), color, glm::vec3(0.0f)));
		}
	}
}