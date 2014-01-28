#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "world.h"

world::world(int num)
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

	
	myobjects = new object_set(num);
	myarena = new arena();
	this->background = new textured_sphere(glm::vec3(0.0f),120,true);
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
	if(!this->myarena->Initialize(slices))
	{
		cerr << "world::Initialize myfloor failed to initialize" << endl;
		return false;
	}
	char texture_name[20];
	sprintf_s(texture_name, "space%d.jpg", this->universe_texture);
	if(!this->background->Initialize(slices, (const char*) texture_name, NULL))
	{
		cerr << "world::Initialize background failed to initialize" << endl;
		return false;
	}

	return true;
}

bool world::DrawWorld(glm::mat4 projection_matrix, glm::mat4 modelview_matrix, glm::ivec2 size, window *win)
{
	glMatrixMode(GL_MODELVIEW);
	glm::mat4 local_modelview = modelview_matrix;

	if(!this->mydebug->Draw(projection_matrix, modelview_matrix, size))
	{
		cerr << "world::Draw debug failed" << endl;
		return false;
	}

	//environ->DrawEnviron
	if(!this->myobjects->Draw(projection_matrix, modelview_matrix, size, win->paused))
	{
		cerr << "world::Draw debug failed" << endl;
		return false;
	}
	if(!this->myarena->Draw(projection_matrix, modelview_matrix, size, this->myobjects->getStriker_x_Position(), this->myobjects->getStriker_z_Position()))
	{
		cerr << "world::Draw debug failed" << endl;
		return false;
	}

	local_modelview = modelview_matrix;
	local_modelview = glm::rotate(local_modelview, 270.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	local_modelview = glm::translate(local_modelview, glm::vec3(20.0f, 0.0f, 0.0f));
	if(!this->background->Draw(projection_matrix, local_modelview, size, 0.0f, 0.0f,0,glm::vec2(0.0f,0.0f)))
	{
		cerr << "world::Draw debug failed" << endl;
		return false;
	}
	return true;

}

void world::UpdatePhysicsWorld(window *win)
{
	this->myobjects->UpdatePhysics(win);
}

void world::switch_special_effect(void)
{
	this->myobjects->switch_special_effect();
}

void world::switch_special_mode(void)
{
	this->myarena->switch_special_mode();
}

world::~world()
{
	//TODO: delete environ
	//delete myenviron;
	delete mydebug;
	delete myobjects;
	delete myarena;
	delete background;
}

void world::TakeDown()
{
	this->mydebug->TakeDown();
	this->myobjects->TakeDown();
	this->myarena->TakeDown();
	this->background->TakeDown();
}

void world::FlipNormals()
{
	this->myobjects->FlipNormals();
	this->myarena->FlipNormals();
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
	this->myarena->switch_shader();
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

GLfloat world::getStrikerDirection(void)
{
	return myobjects->getStrikerDirection();
}

GLfloat world::getStriker_x_Position(void)
{
	return myobjects->getStriker_x_Position();
}

GLfloat world::getStriker_z_Position(void)
{
	return myobjects->getStriker_z_Position();
}