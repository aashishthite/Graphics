#include "textured_cuboid.h"

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "vertexattributes.h"

textured_cuboid::textured_cuboid() : textured_square()
{
}

textured_cuboid::textured_cuboid(glm::vec3 clr, GLint x, GLint y, GLint z, bool flipSurface) : textured_square()
{
	blocks_x = x;
	blocks_y = y;
	blocks_z = z;
	flip_surface = flipSurface;
}

bool textured_cuboid::Draw(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size, GLfloat Wcrop, const GLfloat Hcrop)
{
	modelview = glm::translate(modelview, glm::vec3(0.0f,0.5f,0.0f));
	/////////////////in draw function
	glm::mat4 local_modelview=modelview;
	int i;
	int j;
	for(i=0;i<blocks_x; i++)
	{
		//local_modelview = modelview;
		//local_modelview = glm::translate(local_modelview, glm::vec3(GLfloat(i), 0.0f, 0.0f));
		for(j=0;j<blocks_y; j++)
		{
			local_modelview = modelview;
			local_modelview = glm::translate(local_modelview, glm::vec3(GLfloat(i)-2.5f, GLfloat(j), -1.5f));
			if(!Super_tex_lattice::Draw(projection,local_modelview,size,Wcrop,Hcrop,0,glm::vec2(0.0f,0.0f)))
			{
				std::cerr << "textured_cuboid::Draw superlattice failed" << std::endl;
				return false;
			}

		}
		
		for(j=0;j<blocks_y; j++)
		{
			//local_modelview = modelview;
			local_modelview = glm::rotate(modelview , 180.0f,glm::vec3(0.0f,1.0f,0.0f));
			local_modelview = glm::translate(local_modelview, glm::vec3(GLfloat(i)+0.5f, GLfloat(j), -1.5f));
			if(!Super_tex_lattice::Draw(projection,local_modelview,size,Wcrop,Hcrop,0,glm::vec2(0.0f,0.0f)))
			{
				std::cerr << "textured_cuboid::Draw superlattice failed" << std::endl;
				return false;
			}

		}
		
	}
	glm::mat4 other_modelview =glm::rotate(modelview,90.0f,glm::vec3(1.0f,0.0f,0.0f));
	for(i=0;i<blocks_x; i++)
	{
		for(j=0;j<blocks_z; j++)
		{
			local_modelview = other_modelview;
			local_modelview = glm::translate(local_modelview, glm::vec3(GLfloat(i)-2.5f, GLfloat(j)-1.0, -blocks_z+0.5f));
			if(!Super_tex_lattice::Draw(projection,local_modelview,size,Wcrop,Hcrop,0,glm::vec2(0.0f,0.0f)))
			{
				std::cerr << "textured_cuboid::Draw superlattice failed" << std::endl;
				return false;
			}
		}

	}
	
	modelview=glm::rotate(modelview,90.0f,glm::vec3(0.0f,1.0f,0.0f));
	modelview=glm::translate(modelview,glm::vec3(1.5f,0.0f,-1.5f));
	for(i=0;i<blocks_z; i++)
	{
		for(j=0;j<blocks_y; j++)
		{
			local_modelview = modelview;
			local_modelview = glm::translate(local_modelview, glm::vec3(GLfloat(i)-2.5f, GLfloat(j), -1.5f));
			if(!Super_tex_lattice::Draw(projection,local_modelview,size,Wcrop,Hcrop,0,glm::vec2(0.0f,0.0f)))
			{
				std::cerr << "textured_cuboid::Draw superlattice failed" << std::endl;
				return false;
			}

		}
		
		for(j=0;j<blocks_y; j++)
		{
			//local_modelview = modelview;
			local_modelview = glm::rotate(modelview , 180.0f,glm::vec3(0.0f,1.0f,0.0f));
			local_modelview = glm::translate(local_modelview, glm::vec3(GLfloat(i)+0.5f, GLfloat(j), -1.5f));
			if(!Super_tex_lattice::Draw(projection,local_modelview,size,Wcrop,Hcrop,0,glm::vec2(0.0f,0.0f)))
			{
				std::cerr << "textured_cuboid::Draw superlattice failed" << std::endl;
				return false;
			}

		}
		
	}
	return true;
}