#include "object_set.h"

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

using namespace std;

object_set::object_set()
{
	stool_model = new stool();
	ground = new textured_disk(glm::vec3(0.5f), 0,15,true);
	building = new textured_cuboid(glm::vec3(0.5f), 3, 3, 3, true);
	tree_model = new tree();

	stool_properties.push_back(stool_params(0,0,0,0,50));
	stool_properties.push_back(stool_params(2,0,-2,30,150));
	stool_properties.push_back(stool_params(-2,0,4,3,75));
	stool_properties.push_back(stool_params(-3,0,-2,12,34));
	stool_properties.push_back(stool_params(2,0,3,23,123));
	stool_properties.push_back(stool_params(-2,0,1,67,199));
	stool_properties.push_back(stool_params(4,0,1,87,0));
	stool_properties.push_back(stool_params(-4,0,-4,25,12));
	stool_properties.push_back(stool_params(4,0,4,76,3));
	stool_properties.push_back(stool_params(-4,0,3,76,79));
	stool_properties.push_back(stool_params(1,0,-4,76,6));
	stool_properties.push_back(stool_params(3,0,-3,76,87));
	stool_properties.push_back(stool_params(2,0,1,76,190));
	stool_properties.push_back(stool_params(3,0,-1,76,101));
	stool_properties.push_back(stool_params(-1,0,-3,76,32));
	stool_properties.push_back(stool_params(-8,6,8,76,32));
	this->curr_stool = this->stool_properties.size();

	tree_properties.push_back(tree_params(-7,0,7,1));
	tree_properties.push_back(tree_params(6,0,6,5));
	tree_properties.push_back(tree_params(-6,0,-6,3));
	tree_properties.push_back(tree_params(2,0,7,4));

	tree_properties.push_back(tree_params(7,0,-8,2));
	tree_properties.push_back(tree_params(7,0,-6,2));
	tree_properties.push_back(tree_params(7,0,-4,2));
	tree_properties.push_back(tree_params(7,0,-2,2));

	tree_properties.push_back(tree_params(8,0,-7,2));
	tree_properties.push_back(tree_params(8,0,-5,2));
	tree_properties.push_back(tree_params(8,0,-3,2));
	tree_properties.push_back(tree_params(8,0,-1,2));

	tree_properties.push_back(tree_params(9,0,-8,2));
	tree_properties.push_back(tree_params(9,0,-6,2));
	tree_properties.push_back(tree_params(9,0,-4,2));
	tree_properties.push_back(tree_params(9,0,-2,2));

	tree_properties.push_back(tree_params(10,0,-7,2));
	tree_properties.push_back(tree_params(10,0,-5,2));
	tree_properties.push_back(tree_params(10,0,-3,2));
	tree_properties.push_back(tree_params(10,0,-1,2));

	tree_properties.push_back(tree_params(11,0,-8,2));
	tree_properties.push_back(tree_params(11,0,-6,2));
	tree_properties.push_back(tree_params(11,0,-4,2));
	tree_properties.push_back(tree_params(11,0,-2,2));

	tree_properties.push_back(tree_params(6,0,9,1));
	tree_properties.push_back(tree_params(8,0,9,7));
}

bool object_set::Initialize(int slices)
{
	if(!this->stool_model->Initialize(slices))
	{
		cerr << "object_set::Initialize stools failed to initialize" << endl;
		return false;
	}
	if(!this->tree_model->Initialize(slices))
	{
		cerr << "object_set::Initialize tree failed to initialize" << endl;
		return false;
	}

	this->ground->Initialize(slices, "moon.jpg");
	this->building->Initialize(slices, "brick.jpg");
	return true;
}

void object_set::Draw(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size)
{

	GLfloat giant_scale = 30.0f;
	//Find trabnsformations for the first (giant stool)
	GLfloat default_min_seat_displacement = 2.0f+0.02f+0.135f;
	GLfloat effective_seat_height = stool_properties[0].seat_height/400.0f;
	GLfloat effective_seat_angle = stool_properties[0].seat_height*3600.0f/400.0f;


	glm::mat4 local_modelview = modelview;
	local_modelview = glm::scale(local_modelview, glm::vec3(giant_scale, giant_scale, giant_scale));
	local_modelview = glm::translate(local_modelview, glm::vec3(0.0f, -effective_seat_height, 0.0f));
	local_modelview = glm::translate(local_modelview, glm::vec3(0.0f, -default_min_seat_displacement, 0.0f));
	this->stool_model->Draw(projection, local_modelview, size, stool_properties[0].pos_x, stool_properties[0].pos_y, stool_properties[0].pos_z, stool_properties[0].rot_y, stool_properties[0].seat_height, stool_properties[0].adjust_height, stool_properties[0].highlight_seat);

	
	local_modelview = glm::translate(local_modelview, glm::vec3(0.0f, effective_seat_height, 0.0f));
	local_modelview = glm::rotate(local_modelview, -effective_seat_angle, glm::vec3(0.0f, 1.0f, 0.0f));
	local_modelview = glm::translate(local_modelview, glm::vec3(0.0f, default_min_seat_displacement, 0.0f));
	//local_modelview = glm::rotate(local_modelview, 90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	
	

	local_modelview = glm::scale(local_modelview, glm::vec3(1.0f/giant_scale, 1.0f/giant_scale, 1.0f/giant_scale));
	unsigned int i;
	for(i=1; i<stool_properties.size(); i++)
	{
		this->stool_model->Draw(projection, local_modelview, size, stool_properties[i].pos_x, stool_properties[i].pos_y, stool_properties[i].pos_z, stool_properties[i].rot_y, stool_properties[i].seat_height, stool_properties[i].adjust_height, stool_properties[i].highlight_seat);
	}

	for(i=0; i<tree_properties.size(); i++)
	{
	 	this->tree_model->Draw(projection, local_modelview, size, tree_properties[i].pos_x, tree_properties[i].pos_y, tree_properties[i].pos_z, tree_properties[i].tree_height);
	}

	////in object set:: draw

	glm::mat4 local_modelview1 = glm::translate(local_modelview, glm::vec3(0.0f, 0.01f, 0.0f));
	local_modelview1 = glm::rotate(local_modelview1, 90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	ground->Draw(projection, local_modelview1, size);

	glm::mat4 local_modelview2= glm::translate(local_modelview, glm::vec3(0.0f, 0.0f, -10.0f));
	building->Draw(projection, local_modelview2, size);
	building->Draw(projection, glm::translate(local_modelview2,glm::vec3(0.0f,2.0f,0.0f)), size);
	
	local_modelview=glm::translate(local_modelview,glm::vec3(5.0f,0.0f,8.0f));
	building->Draw(projection,local_modelview, size);
	building->Draw(projection, glm::translate(local_modelview,glm::vec3(1.0f,0.0f,0.0f)), size);

	local_modelview=glm::translate(local_modelview,glm::vec3(-12.0f,0.0f,0.0f));
	building->Draw(projection,local_modelview, size);
	building->Draw(projection, glm::translate(local_modelview,glm::vec3(0.0f,3.0f,0.0f)), size);
}

object_set::~object_set()
{
	delete stool_model;
	delete tree_model;
}

void object_set::TakeDown(void)
{
	stool_model->TakeDown();
	tree_model->TakeDown();
	ground->TakeDown();
	building->TakeDown();
}

void object_set::FlipNormals(void)
{
	stool_model->FlipNormals();
	tree_model->FlipNormals();
	ground->FlipNormals();
	building->FlipNormals();
}

void object_set::change_active_stool(void)
{
	if(this->curr_stool < int(this->stool_properties.size()))
	{
		this->stool_properties[curr_stool].toggle_highlight();
	}
	this->curr_stool = this->curr_stool + 1;
	if(this->curr_stool >= int(this->stool_properties.size()))
	{
		this->curr_stool = 0;
	}
	this->stool_properties[this->curr_stool].toggle_highlight();
}

void object_set::toggle_active_stool(void)
{
	if(this->curr_stool < int(this->stool_properties.size()))
	{
		this->stool_properties[this->curr_stool].toggle_active_stool();
	}
}

void object_set::Increase_stool_heights(void)
{
	unsigned int i;
	for(i=0; i<this->stool_properties.size(); i++)
	{
		this->stool_properties[i].Increase_stool_height();
	}
}

void object_set::Decrease_stool_heights(void)
{
	unsigned int i;
	for(i=0; i<this->stool_properties.size(); i++)
	{
		this->stool_properties[i].Decrease_stool_height();
	}
}

void object_set::switch_shader(void)
{
	stool_model->switch_shader();
	tree_model->switch_shader();
}