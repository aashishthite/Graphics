#include "textured_lattice.h"

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "TextureManager.h"
#include "object.h"

using namespace std;

unsigned int texture_count = 0;

textured_lattice::textured_lattice()
{
	this->current_shader = &texture_shader;
	this->texID = texture_count;
	texture_count++;
}

bool textured_lattice::Initialize(int slices, const char* texture_file)
{
	if (this->GLReturnedError("textured_lattice::Initialize - on entry"))
		return false;

	if (!super::Initialize())
	{
		cerr << "textured_lattice::Initialize - Unable to initialize Object" << endl;
		return false;
	}

	if (slices < 0)
		slices =4;

	this->slice_count = slices;
	this->lattice_width = this->slice_count + 1;
	this->lattice_size = (this->lattice_width) * (this->lattice_width);
	
	//Defining the object here/////
	this->DefineVertices();
	this->DefineNormals();
	this->DefineTriangles();
	///////////////////////////////

	if (!this->PostGLInitialize(&this->vertex_array_handle, &this->vertex_coordinate_handle, this->vertices.size() * sizeof(VertexAttributesPCNT), &this->vertices[0]))
	{
		cerr << "textured_lattice::Initialize - PostGLInitialize for textured_lattice failed" << endl;
		return false;
	}

	/*	The VertexAttributesPCN class stores vertex attributes: position, color and normal in that order.

		Vertex attributes are stored in an interleaved manner aiding speed of vertex processing.
	*/

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttributesPCNT), (GLvoid *) 0); //Position
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttributesPCNT), (GLvoid *) (sizeof(glm::vec3) * 1)); //Color
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttributesPCNT), (GLvoid *) (sizeof(glm::vec3) * 2)); //Normal
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(VertexAttributesPCNT), (GLvoid *) (sizeof(glm::vec3) * 3)); //Texture coordinate
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	if (this->normal_vertices.size() > 0)
	{
		if (!this->PostGLInitialize(&this->normal_array_handle, &this->normal_coordinate_handle, this->normal_vertices.size() * sizeof(VertexAttributesPC), &this->normal_vertices[0]))
		{
			cerr << "textured_lattice::Initialize - PostGLInitialize for normals failed" << endl;
			return false;
		}

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttributesPC), (GLvoid *) 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttributesPC), (GLvoid *) (sizeof(glm::vec3) * 1));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	/*
	if (!this->phong_shader.Initialize("phong_shader.vert", "phong_shader.frag"))
	{
		cerr << "textured_lattice::Initialize - Initializing phong_shader failed" << endl;
		return false;
	}
	if (!this->phong_shader_new.Initialize("phong_shader_new.vert", "phong_shader_new.frag"))
	{
		cerr << "textured_lattice::Initialize - Initializing phong_shader_new failed" << endl;
		return false;
	}
	if (!this->gouraud_shader.Initialize("gouraud_shader.vert", "gouraud_shader.frag"))
	{
		cerr << "textured_lattice::Initialize - Initializing gouraud_shader failed" << endl;
		return false;
	}
	*/

	if (!this->solid_color.Initialize("solid_shader.vert", "solid_shader.frag"))
	{
		cerr << "textured_lattice::Initialize - Initializing solid_shader failed" << endl;
		return false;
	}
	if (!this->texture_shader.Initialize("texture_shader.vert", "texture_shader.frag"))
	{
		cerr << "textured_lattice::Initialize - Initializing texture_shader failed" << endl;
		return false;
	}

#pragma region Code to make FreeImage work
	//	The picture too, ought not to be here.

	if (!TextureManager::Inst()->LoadTexture(texture_file, this->texID))
		return false;

	//	The current "TextureManager" that comes with FreeImage is quite dumb.
	glTexEnvf(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_REPLACE);
	glTexParameterf(GL_TEXTURE_2D , GL_TEXTURE_WRAP_S , GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D , GL_TEXTURE_WRAP_T , GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER , GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER , GL_LINEAR);
#pragma endregion


	if (this->GLReturnedError("textured_lattice::Initialize - on exit"))
	{
		return false;
	}
	return true;
}

void textured_lattice::DefineNormals(void)
{
	//Define normals
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
		current = this->vertices[i].position;
		top = this->vertices[this->vertex_top(i)].position;
		top_right = this->vertices[this->vertex_top_right(i)].position;
		right = this->vertices[this->vertex_right(i)].position;
		bottom = this->vertices[this->vertex_bottom(i)].position;
		bottom_left = this->vertices[this->vertex_bottom_left(i)].position;
		left = this->vertices[this->vertex_left(i)].position;
		normal_part1 = glm::cross(NormalizeVector(top_right - current), NormalizeVector(top - current));
		normal_part2 = glm::cross(NormalizeVector(right - current), NormalizeVector(top_right - current));
		normal_part3 = glm::cross(NormalizeVector(bottom - current), NormalizeVector(right - current));
		normal_part4 = glm::cross(NormalizeVector(bottom_left - current), NormalizeVector(bottom - current));
		normal_part5 = glm::cross(NormalizeVector(left - current), NormalizeVector(bottom_left - current));
		normal_part6 = glm::cross(NormalizeVector(top - current), NormalizeVector(left - current));
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
void textured_lattice::DefineTriangles(void)
{
	//Define triangles
	int t;
	int r;
	int b;
	int l;
	int i;
	for(i=0; i<this->lattice_size; i++)
	{
		t = this->vertex_top(i);
		r = this->vertex_right(i);
		b = this->vertex_bottom(i);
		l = this->vertex_left(i);
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
void textured_lattice::Draw(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size)
{
	if (this->GLReturnedError("textured_lattice::Draw - on entry"))
		return;

	//Setting the texture to be drawn
	if(!TextureManager::Inst()->BindTexture((const unsigned int) (texID)))
	{
		cerr << "textured_lattice::Unable to bind texture" << texID <<endl;
	}

	glEnable(GL_DEPTH_TEST);

	glm::mat4 mvp = projection * modelview;
	glm::mat3 nm = glm::inverse(glm::transpose(glm::mat3(modelview)));
	
	this->current_shader->Use();
	this->current_shader->CommonSetup(0.0f, glm::value_ptr(size), glm::value_ptr(projection), glm::value_ptr(modelview), glm::value_ptr(mvp), glm::value_ptr(nm), this->reflectance);
	this->current_shader->CustomSetup();
	//phong_shader.Use();
	//phong_shader.CommonSetup(0.0f, glm::value_ptr(size), glm::value_ptr(projection), glm::value_ptr(modelview), glm::value_ptr(mvp), glm::value_ptr(nm));
	//gouraud_shader.Use();
	//gouraud_shader.CommonSetup(0.0f, glm::value_ptr(size), glm::value_ptr(projection), glm::value_ptr(modelview), glm::value_ptr(mvp), glm::value_ptr(nm));
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

	if (this->GLReturnedError("textured_lattice::Draw - on exit"))
		return;
}

void textured_lattice::TakeDown()
{
	this->vertices.clear();
	this->texture_shader.TakeDown();
	this->solid_color.TakeDown();
	super::TakeDown();
}
