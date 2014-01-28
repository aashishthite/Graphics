#include "arena.h"

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

using namespace std;

extern FrameBufferObject* ReflectionView_fbo;
extern FrameBufferObject* ReflectionTop_fbo;
extern bool rendertopview;
extern GLfloat Reflection_wcrop;
extern GLfloat Reflection_hcrop;

glm::vec3 arena::GetColor(GLint color)
{
	switch(color)
	{
		case 1: //Theme color 1 - Indigo
			return glm::vec3(76.0f/255.0f, 0.0f/255.0f, 153.0f/255.0f);
			break;
		case 2: //Theme color 2 - Amber
			return glm::vec3(255.0f/255.0f, 255.0f/255.0f, 0.0f/255.0f);
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
		case 6: //Brown for ground
			return glm::vec3(139.0f/255.0f, 119.0f/255.0f, 101.0f/255.0f);
			break;
		case 7: //Red old steps
			return glm::vec3(110.0f/255.0f, 20.0f/255.0f, 20.0f/255.0f);
			break;

		case 8: //Steps1
			return glm::vec3(12.0f/255.0f, 20.0f/255.0f, 110.0f/255.0f);
			break;
		case 9: //Steps2
			return glm::vec3(200.0f/255.0f, 255.0f/255.0f, 0.0f/255.0f);
			break;
		default:
			cerr << "stool::GetColor - Illegal color; setting to white" <<endl;
			return glm::vec3(1.0f, 1.0f, 1.0f);
			break;
	}
}

arena::arena()
{
	floor = new textured_square(GetColor(1), false);
	floor_top = new textured_square(GetColor(1), false);
	//arenaComponents.push_back(floor);
	ground = new disk(GetColor(6), 0, 200, false);
	arenaComponents.push_back(ground);

	//comstructing gallery objects
	cylinder1 = new cylinder(GetColor(8), 40, 40, 2, true);
	cylinder2 = new cylinder(GetColor(7), 42, 42, 4, true);
	cylinder3 = new cylinder(GetColor(8), 44, 44, 6, true);
	cylinder4 = new cylinder(GetColor(7), 46, 46, 8, true);
	cylinder5 = new cylinder(GetColor(8), 48, 48, 10, true);
	cylinder6 = new cylinder(GetColor(7), 50, 50, 10, false);
	disk1 = new disk(GetColor(8), 40, 42, false);
	disk2 = new disk(GetColor(7), 42, 44, false);
	disk3 = new disk(GetColor(8), 44, 46, false);
	disk4 = new disk(GetColor(7), 46, 48, false);
	disk5 = new disk(GetColor(8), 48, 50, false);
	disk6 = new disk(GetColor(7), 0, 50, true);
	arenaComponents.push_back(cylinder1);
	arenaComponents.push_back(cylinder2);
	arenaComponents.push_back(cylinder3);
	arenaComponents.push_back(cylinder4);
	arenaComponents.push_back(cylinder5);
	arenaComponents.push_back(cylinder6);
	arenaComponents.push_back(disk1);
	arenaComponents.push_back(disk2);
	arenaComponents.push_back(disk3);
	arenaComponents.push_back(disk4);
	arenaComponents.push_back(disk5);
	arenaComponents.push_back(disk6);

	//constructing jumbotron objects;
	jumbo = new jumbotron();
	jumbotron_properties.push_back(jumbotron_params(49,0,10));
	jumbotron_properties.push_back(jumbotron_params(49,90,10));
	jumbotron_properties.push_back(jumbotron_params(49,180,10));
	jumbotron_properties.push_back(jumbotron_params(49,270,10));
}

void arena::switch_special_mode(void)
{
	floor->texture_shader.switch_special_mode();
	floor_top->texture_shader.switch_special_mode();
}

bool arena::Draw(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size, GLfloat strike_x, GLfloat strike_y)
{
	glm::mat4 local_modelview = modelview;
	
	//Draw the floor
	GLfloat arena_edge_size = 50.0f;
	local_modelview = glm::rotate(local_modelview, 270.0f, glm::vec3(1.0f,0.0f,0.0f));
	local_modelview = glm::scale(local_modelview, glm::vec3(arena_edge_size));
	if(rendertopview)
	{
		if(!floor_top->Draw(projection, local_modelview, size, Reflection_wcrop, Reflection_hcrop,0,glm::vec2(strike_x,strike_y)))
		{
			cerr << "arena::Draw floor failed" << endl;
			return false;
		}
	}
	else
	{
		if(!floor->Draw(projection, local_modelview, size, Reflection_wcrop, Reflection_hcrop,0,glm::vec2(strike_x,strike_y)))
		{
			cerr << "arena::Draw floor failed" << endl;
			return false;
		}
	}

	//Draw the ground
	local_modelview = modelview;
	local_modelview = glm::rotate(local_modelview, 270.0f, glm::vec3(1.0f,0.0f,0.0f));
	local_modelview = glm::translate(local_modelview, glm::vec3(0.0f, 0.0f, -0.005f));
	if(!ground->Draw(projection, local_modelview, size))
	{
		cerr << "arena::Draw ground failed" << endl;
		return false;
	}
	
	//Draw the gallery
	local_modelview = modelview;
	local_modelview = glm::rotate(local_modelview, 270.0f, glm::vec3(1.0f,0.0f,0.0f));
	local_modelview = glm::translate(local_modelview, glm::vec3(0.0f, 0.0f, -0.002f));
	if(!cylinder1->Draw(projection, local_modelview, size))
	{
		cerr << "arena::Draw cylinder1 failed" << endl;
		return false;
	}
	if(!cylinder2->Draw(projection, local_modelview, size))
	{
		cerr << "arena::Draw cylinder2 failed" << endl;
		return false;
	}
	if(!cylinder3->Draw(projection, local_modelview, size))
	{
		cerr << "arena::Draw cylinder3 failed" << endl;
		return false;
	}
	if(!cylinder4->Draw(projection, local_modelview, size))
	{
		cerr << "arena::Draw cylinder4 failed" << endl;
		return false;
	}
	if(!cylinder5->Draw(projection, local_modelview, size))
	{
		cerr << "arena::Draw cylinder5 failed" << endl;
		return false;
	}
	if(!cylinder6->Draw(projection, local_modelview, size))
	{
		cerr << "arena::Draw cylinder6 failed" << endl;
		return false;
	}

	local_modelview = glm::translate(local_modelview, glm::vec3(0.0f, 0.0f, 2.0f));
	if(!disk1->Draw(projection, local_modelview, size))
	{
		cerr << "arena::Draw disk1 failed" << endl;
		return false;
	}
	local_modelview = glm::translate(local_modelview, glm::vec3(0.0f, 0.0f, 2.0f));
	if(!disk2->Draw(projection, local_modelview, size))
	{
		cerr << "arena::Draw disk2 failed" << endl;
		return false;
	}
	local_modelview = glm::translate(local_modelview, glm::vec3(0.0f, 0.0f, 2.0f));
	if(!disk3->Draw(projection, local_modelview, size))
	{
		cerr << "arena::Draw disk3 failed" << endl;
		return false;
	}
	local_modelview = glm::translate(local_modelview, glm::vec3(0.0f, 0.0f, 2.0f));
	if(!disk4->Draw(projection, local_modelview, size))
	{
		cerr << "arena::Draw disk4 failed" << endl;
		return false;
	}
	local_modelview = glm::translate(local_modelview, glm::vec3(0.0f, 0.0f, 2.0f));
	if(!disk5->Draw(projection, local_modelview, size))
	{
		cerr << "arena::Draw disk5 failed" << endl;
		return false;
	}
	//local_modelview = glm::translate(local_modelview, glm::vec3(0.0f, 0.0f, -10.0f));
	//if(!disk6->Draw(projection, local_modelview, size))
	//{
	//	cerr << "arena::Draw disk6 failed" << endl;
	//	return false;
	//}

	//Draw the jumbotron
	local_modelview = modelview;
	unsigned int i;
	for(i=0; i<jumbotron_properties.size(); i++)
	{
		if(!this->jumbo->Draw(projection, local_modelview, size, jumbotron_properties[i].radius, jumbotron_properties[i].angle, jumbotron_properties[i].height))
		{
			cerr << "arena::Draw jumbotron failed" << endl;
			return false;
		}
	}

	return true;
}

void arena::FlipNormals(void)
{
	/*
	floor->FlipNormals();
	unsigned int i;
	for(i=0; i<arenaComponents.size(); i++)
	{
		arenaComponents[i]->FlipNormals();
	}
	jumbo->FlipNormals();
	*/
}

bool arena::Initialize(int slices)
{
	//Initialize all geometries which are part of the arena
	if(!floor->Initialize(slices, "dummy", ReflectionView_fbo))
		return false;
	if(!floor_top->Initialize(slices, "dummy", ReflectionTop_fbo))
		return false;

	unsigned int i;
	for(i=0; i<arenaComponents.size(); i++)
	{
		if(!arenaComponents[i]->Initialize(slices*2))
			return false;
	}
	if(!jumbo->Initialize(slices))
		return false;
	return true;
}

void arena::TakeDown(void)
{
	floor->TakeDown();
	floor_top->TakeDown();
	unsigned int i;
	for(i=0; i<arenaComponents.size(); i++)
	{
		arenaComponents[i]->TakeDown();
	}
	jumbo->TakeDown();
}

arena::~arena()
{
	delete floor;
	delete floor_top;
	unsigned int i;
	for(i=0; i<arenaComponents.size(); i++)
	{
		delete arenaComponents[i];
	}
	delete jumbo;
}

void arena::switch_shader(void)
{
	floor->switch_shader();
	floor_top->switch_shader();
	unsigned int i;
	for(i=0; i<arenaComponents.size(); i++)
	{
		arenaComponents[i]->switch_shader();
	}
	jumbo->switch_shader();
}