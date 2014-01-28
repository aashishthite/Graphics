#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "world.h"

world::world(void)
{
	//TODO: create environment
	//myenviron = new environ(true,false,false);
	
	mydebug = new debug(false,false);
	//Arguments of stool constructor
	//X coordinate (in feet)
	//Y coordinate (in feet)
	//Z coordinate (in feet)
	//Angle of rotation along the y axis (in degrees)
	//Seat height (unit is 0.0025 foot over the minimum height)
	//mystools[0] = new stool(0,0,0,0,50);
	//stool temp = ;

	
	myobjects = new object_set();
	this->background = new textured_sphere(glm::vec3(0.0f),80,true);
	//stool_count = 2;
	//this->curr_stool = this->mystools.size();
	this->slices = 30;
	this->wireframe = false;
	this->universe_texture = 1;
}

bool world::Initialize(void)
{
	if(!this->mydebug->Initialize(slices))
	{
		cerr << "world::Initialize debug failed to initialize" << endl;
		return false;
	}
	if(!this->myobjects->Initialize(slices))
	{
		cerr << "world::Initialize stools failed to initialize" << endl;
		return false;
	}
	char texture_name[20];
	sprintf_s(texture_name, "space%d.jpg", this->universe_texture);
	if(!this->background->Initialize(slices, (const char*) texture_name))
	{
		cerr << "world::Initialize background failed to initialize" << endl;
		return false;
	}
	return true;
}

void world::DrawWorld(window *win, glm::mat4 projection_matrix, glm::mat4 modelview_matrix)
{
	glMatrixMode(GL_MODELVIEW);


	this->mydebug->Draw(projection_matrix, modelview_matrix, glm::ivec2(win->width,win->height));

	//environ->DrawEnviron
	this->myobjects->Draw(projection_matrix, modelview_matrix, glm::ivec2(win->width,win->height));
	//this->wc1->Draw(projection_matrix, modelview_matrix, glm::ivec2(win->width,win->height));

	//glm::mat4 background_projection = glm::ortho(0.0f, GLfloat(win->width), 0.0f, GLfloat(win->height), 1.0f, 10.0f);
	//glm::mat4 background_modelview = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.5f));
	//glm::mat4 background_modelview = glm::mat4(1.0f);
	//background_modelview = glm::translate(background_modelview, glm::vec3(0.0f, 0.0f, -5.5f));
	//background_modelview = glm::scale(background_modelview, glm::vec3(win->width, win->width, 3.0f));
	//this->background->Draw(background_projection, background_modelview, glm::ivec2(win->width,win->height));
	//modelview_matrix = glm::scale(copy_modelview, glm::vec3(win->width, win->height, 0.0f));
	//modelview_matrix = glm::rotate(modelview_matrix, 270.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	//modelview_matrix = glm::translate(modelview_matrix, glm::vec3(0.0f, 0.0f, -6.0f));
	this->background->Draw(projection_matrix, modelview_matrix, glm::ivec2(win->width,win->height));
}

world::~world()
{
	//TODO: delete environ
	//delete myenviron;
	delete mydebug;
	delete myobjects;
	delete background;
}

void world::TakeDown()
{
	this->mydebug->TakeDown();
	this->myobjects->TakeDown();
	this->background->TakeDown();
}

void world::FlipNormals()
{
	this->myobjects->FlipNormals();
	this->background->FlipNormals();
}

void world::DecrementSlices(void)
{
	if (this->slices != 4)
	{
		this->slices--;
	}
}

void world::IncrementSlices(void)
{
	if (this->slices != 99)
	{
		this->slices++;
	}
}
void world::FlipWireFrame(void)
{
	this->wireframe = !this->wireframe;
}

bool world::GetWireFrame(void)
{
	return this->wireframe;
}

void world::switch_shader(void)
{
	this->myobjects->switch_shader();
	this->background->switch_shader();
}

void world::switch_universe(void)
{
	if(this->universe_texture == 5)
	{
		this->universe_texture = 1;
	}
	else
	{
		this->universe_texture = this->universe_texture + 1;
	}
}