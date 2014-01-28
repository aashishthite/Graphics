#include "tree.h"

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

using namespace std;

glm::vec3 tree::GetColor(GLint color)
{
	switch(color)
	{
		case 1: //Theme color 1 - Indigo
			return glm::vec3(76.0f/255.0f, 0.0f/255.0f, 153.0f/255.0f);
			break;
		case 2: //Theme color 2 - Amber
			return glm::vec3(215.0f/255.0f, 172.0f/255.0f, 0.0f/255.0f);
			break;
		case 3: //only for highlighted seats
			return glm::vec3(139.0f/255.0f, 20.0f/255.0f, 150.0f/255.0f);
			break;
		case 4: //green for tree
			return glm::vec3(35.0f/255.0f, 142.0f/255.0f, 35.0f/255.0f);
			break;
		case 5: //Lighter shade of 2; for threads, screws
			return glm::vec3(249.0f/255.0f, 229.0f/255.0f, 149.0f/255.0f);
			break;
		default:
			cerr << "stool::GetColor - Illegal color; setting to white" <<endl;
			return glm::vec3(1.0f, 1.0f, 1.0f);
			break;
	}
}

tree::tree()
{
	leaves = new wavy_cylinder(GetColor(4), 1, 0, 5, false);
}

bool tree::Draw(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size, GLfloat pos_x, GLfloat pos_y, GLfloat pos_z, GLfloat height)
{
	glm::mat4 local_modelview = modelview;
	local_modelview = glm::translate(local_modelview, glm::vec3(pos_x, pos_y, -pos_z));
	
	local_modelview = glm::rotate(local_modelview, 270.0f, glm::vec3(1.0f,0.0f,0.0f));
	local_modelview = glm::scale(local_modelview, glm::vec3(height/5));
	if(!leaves->Draw(projection, local_modelview, size))
	{
		std::cerr << "tree::Draw leaves failed" << std::endl;
		return false;
	}
	return true;
}

void tree::FlipNormals(void)
{
	this->leaves->FlipNormals();
}

bool tree::Initialize(int slices)
{
	return this->leaves->Initialize(slices *3);
}

void tree::TakeDown(void)
{
	this->leaves->TakeDown();
}

tree::~tree()
{
	delete leaves;
}

void tree::switch_shader(void)
{
	this->leaves->switch_shader();
}

//////////////////////////////////
//functions for tree_param
tree_params::tree_params(const GLfloat & Posx, const GLfloat & Posy, const GLfloat & Posz, const GLfloat & TreeHt)
{
	this->pos_x = Posx;
	this->pos_y = Posy;
	this->pos_z = Posz;
	this->tree_height = TreeHt;
}

tree_params::tree_params(const tree_params & other)
{
	this->pos_x = other.pos_x;
	this->pos_y = other.pos_y;
	this->pos_z = other.pos_z;
	this->tree_height = other.tree_height;
}