#include "lattice.h"

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

using namespace std;

lattice::lattice() : Object()
{
	current_shader = &phong_shader;
}

void lattice::switch_shader(void)
{
	if(current_shader == &phong_shader)
	{
		current_shader = &flat_shader;
	}
	else
	{
		if(current_shader == &flat_shader)
		{
			current_shader = &gouraud_shader;
		}
		else
		{
			if(current_shader == &gouraud_shader)
			{
				current_shader = &phong_shader;
			}
		}
	}
}

bool lattice::Initialize(int slices)
{
	if (this->GLReturnedError("lattice::Initialize - on entry"))
		return false;

	if (!super::Initialize())
	{
		cerr << "lattice::Initialize - Unable to initialize Object" << endl;
		return false;
	}

	if (slices < 0)
		slices =4;

	slice_count = slices;
	lattice_width = slice_count + 1;
	lattice_size = (lattice_width) * (lattice_width);
	
	//Defining the object here/////
	this->DefineVertices();
	this->DefineNormals();
	this->DefineTriangles();
	///////////////////////////////

	if (!this->PostGLInitialize(&this->vertex_array_handle, &this->vertex_coordinate_handle, this->vertices.size() * sizeof(VertexAttributesPCN), &this->vertices[0]))
	{
		cerr << "lattice::Initialize - PostGLInitialize for lattice failed" << endl;
		return false;
	}

	/*	The VertexAttributesPCN class stores vertex attributes: position, color and normal in that order.

		Vertex attributes are stored in an interleaved manner aiding speed of vertex processing.
	*/

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttributesPCN), (GLvoid *) 0); //Position
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttributesPCN), (GLvoid *) (sizeof(glm::vec3) * 1)); //Color
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttributesPCN), (GLvoid *) (sizeof(glm::vec3) * 2)); //Normal
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	if (this->normal_vertices.size() > 0)
	{
		if (!this->PostGLInitialize(&this->normal_array_handle, &this->normal_coordinate_handle, this->normal_vertices.size() * sizeof(VertexAttributesPC), &this->normal_vertices[0]))
		{
			cerr << "lattice::Initialize - PostGLInitialize for normals failed" << endl;
			return false;
		}

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttributesPC), (GLvoid *) 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttributesPC), (GLvoid *) (sizeof(glm::vec3) * 1));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	if (!this->phong_shader.Initialize("phong_shader.vert", "phong_shader.frag"))
	{
		cerr << "lattice::Initialize - Initializing phong_shader failed" << endl;
		return false;
	}
	if (!this->flat_shader.Initialize("flat_shader.vert", "flat_shader.frag"))
	{
		cerr << "lattice::Initialize - Initializing flat_shader failed" << endl;
		return false;
	}
	if (!this->gouraud_shader.Initialize("gouraud_shader.vert", "gouraud_shader.frag"))
	{
		cerr << "lattice::Initialize - Initializing gouraud_shader failed" << endl;
		return false;
	}
	if (!this->solid_color.Initialize("solid_shader.vert", "solid_shader.frag"))
	{
		cerr << "lattice::Initialize - Initializing solid_shader failed" << endl;
		return false;
	}

	if (this->GLReturnedError("lattice::Initialize - on exit"))
	{
		return false;
	}
	return true;
}

void lattice::Draw(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size)
{
	//Draw the lattice; general function for any kind of surface
	if (this->GLReturnedError("lattice::Draw - on entry"))
		return;

	glEnable(GL_DEPTH_TEST);

	glm::mat4 mvp = projection * modelview;
	glm::mat3 nm = glm::inverse(glm::transpose(glm::mat3(modelview)));
	
	this->current_shader->Use();
	this->current_shader->CommonSetup(0.0f, glm::value_ptr(size), glm::value_ptr(projection), glm::value_ptr(modelview), glm::value_ptr(mvp), glm::value_ptr(nm), this->reflectance);
	glBindVertexArray(this->vertex_array_handle);
	glDrawElements(GL_TRIANGLES, this->vertex_indices.size(), GL_UNSIGNED_INT , &this->vertex_indices[0]);
	glBindVertexArray(0);
	glUseProgram(0);
	
	if (this->draw_normals)
	{
		this->solid_color.Use();
		this->solid_color.CommonSetup(0.0f, glm::value_ptr(size), glm::value_ptr(projection), glm::value_ptr(modelview), glm::value_ptr(mvp), glm::value_ptr(nm), this->reflectance);
		glBindVertexArray(this->normal_array_handle);
		glDrawElements(GL_LINES , this->normal_indices.size(), GL_UNSIGNED_INT , &this->normal_indices[0]);
		glBindVertexArray(0);
		glUseProgram(0);
	}

	if (this->GLReturnedError("lattice::Draw - on exit"))
		return;
}

void lattice::TakeDown()
{
	this->vertices.clear();
	this->flat_shader.TakeDown();
	this->phong_shader.TakeDown();
	this->gouraud_shader.TakeDown();
	this->solid_color.TakeDown();
	super::TakeDown();
}

glm::vec3 lattice::NormalizeVector(glm::vec3 in)
{
	//handles the tricky case of normalizing a zero vector
	glm::vec3 out;
    if((in.r == 0) && (in.g == 0) && (in.b == 0))
	{
		out = glm::vec3(0.0f);
	}
	else
	{
		out = glm::normalize(in);
	}
	return out;
}

void lattice::DefineNormals(void)
{
	//Define normals for a general surface
	glm::vec3 current;
	glm::vec3 top;
	glm::vec3 top_right;
	glm::vec3 right;
	glm::vec3 bottom;
	glm::vec3 bottom_left;
	glm::vec3 left;
	glm::vec3 normal_part1;
	glm::vec3 normal_part2;
	glm::vec3 normal_part3;
	glm::vec3 normal_part4;
	glm::vec3 normal_part5;
	glm::vec3 normal_part6;
	glm::vec3 normal;
	const float normal_scalar = 0.125f;
	int i;
	for(i=0; i<this->lattice_size; i++)
	{
		//Locate the neighboring vertices
		current = this->vertices[i].position;
		top = this->vertices[this->vertex_top(i)].position;
		top_right = this->vertices[this->vertex_top_right(i)].position;
		right = this->vertices[this->vertex_right(i)].position;
		bottom = this->vertices[this->vertex_bottom(i)].position;
		bottom_left = this->vertices[this->vertex_bottom_left(i)].position;
		left = this->vertices[this->vertex_left(i)].position;
		
		//Find vectors along each line segment emanating from the current vertex, calculate cross product for adjacent pairs
		//The special NormalizeVector function is designed to handle zero vectors
		normal_part1 = glm::cross(NormalizeVector(top_right - current), NormalizeVector(top - current));
		normal_part2 = glm::cross(NormalizeVector(right - current), NormalizeVector(top_right - current));
		normal_part3 = glm::cross(NormalizeVector(bottom - current), NormalizeVector(right - current));
		normal_part4 = glm::cross(NormalizeVector(bottom_left - current), NormalizeVector(bottom - current));
		normal_part5 = glm::cross(NormalizeVector(left - current), NormalizeVector(bottom_left - current));
		normal_part6 = glm::cross(NormalizeVector(top - current), NormalizeVector(left - current));

		//Add normals of each contributing triangle, normalize
		normal = NormalizeVector(normal_part1 + normal_part2 + normal_part3 + normal_part4 + normal_part5 + normal_part6);

		if(this->flip_surface)
		{
			normal.x = - normal.x;
			normal.y = - normal.y;
			normal.z = - normal.z;
		}

		this->vertices[i].normal = normal;

		//Calculate normal visualization geometry
		this->normal_vertices.push_back(VertexAttributesPC(this->vertices[i].position, glm::vec3(1.0f)));
		this->normal_vertices.push_back(VertexAttributesPC(this->vertices[i].position + this->vertices[i].normal * normal_scalar, glm::vec3(1.0f)));
		this->normal_indices.push_back(this->normal_vertices.size() - 2);
		this->normal_indices.push_back(this->normal_vertices.size() - 1);
	}
}
void lattice::DefineTriangles(void)
{
	//Define triangles for a general surface
	int t;
	int r;
	int b;
	int l;
	int i;
	for(i=0; i<this->lattice_size; i++)
	{
		t = vertex_top(i);
		r = vertex_right(i);
		b = vertex_bottom(i);
		l = vertex_left(i);
		if((i != r) && (i != b))
		{
			if(this->flip_surface)
			{
				this->vertex_indices.push_back(i);
				this->vertex_indices.push_back(r);
				this->vertex_indices.push_back(b);
			}
			else
			{
				this->vertex_indices.push_back(i);
				this->vertex_indices.push_back(b);
				this->vertex_indices.push_back(r);
			}
		}
		if((i != l) && (i != t))
		{
			if(this->flip_surface)
			{
				this->vertex_indices.push_back(i);
				this->vertex_indices.push_back(l);
				this->vertex_indices.push_back(t);
			}
			else
			{
				this->vertex_indices.push_back(i);
				this->vertex_indices.push_back(t);
				this->vertex_indices.push_back(l);
			}
		}
	}
}

