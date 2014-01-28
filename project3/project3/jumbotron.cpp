#include "jumbotron.h"

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

using namespace std;

extern FrameBufferObject* MainView_fbo;
extern GLint mainview_display_attachment;

glm::vec3 jumbotron::GetColor(GLint color)
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
		case 6: //Gray for pillar
			return glm::vec3(105.0f/255.0f, 105.0f/255.0f, 105.0f/255.0f);
			break;
		case 7: //Black for frame
			return glm::vec3(0.0f/255.0f, 0.0f/255.0f, 0.0f/255.0f);
			break;
		default:
			cerr << "stool::GetColor - Illegal color; setting to white" <<endl;
			return glm::vec3(1.0f, 1.0f, 1.0f);
			break;
	}
}

jumbotron::jumbotron()
{
	pillar = new cylinder(GetColor(6),0.5,0.25,5,false);
	frame = new cube(GetColor(1), false);
	screen = new textured_square(GetColor(1), true);
}

bool jumbotron::Draw(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size, GLfloat radius, GLfloat angle, GLfloat height)
{
	//Relocating and orienting  jumbotron
	modelview = glm::rotate(modelview, angle, glm::vec3(0.0f, 1.0f, 0.0f));
	modelview = glm::translate(modelview, glm::vec3(radius, height, 0.0f));
	glm::mat4 local_modelview = modelview;
	
	//Rotate to draw the pillar
	local_modelview = glm::rotate(local_modelview, 270.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	if(!pillar->Draw(projection, local_modelview, size))
	{
		cerr << "jumbotron::Draw pillar failed" << endl;
		return false;
	}

	//Draw the frame
	local_modelview = modelview;
	local_modelview = glm::translate(local_modelview, glm::vec3(0.0f, 8.0f, 0.0f));
	local_modelview = glm::scale(local_modelview, glm::vec3(0.5f,6.0f,10.0f));
	if(!frame->Draw(projection, local_modelview, size))
	{
		cerr << "jumbotron::Draw frame failed" << endl;
		return false;
	}

	//Draw screen
	local_modelview = modelview;
	local_modelview = glm::translate(local_modelview, glm::vec3(-0.26f, 0.0f, 0.0f));
	local_modelview = glm::rotate(local_modelview, 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	local_modelview = glm::translate(local_modelview, glm::vec3(0.0f, 8.0f, 0.0f));
	local_modelview = glm::rotate(local_modelview, 180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	local_modelview = glm::scale(local_modelview, glm::vec3(10.0f,6.0f,1.0f));
	if(!screen->Draw(projection, local_modelview, size, 0.0f, 0.0f, mainview_display_attachment,glm::vec2(0.0f,0.0f)))
	{
		cerr << "jumbotron::Draw screen failed" << endl;
		return false;
	}

	return true;

}

void jumbotron::FlipNormals(void)
{
	this->pillar->FlipNormals();
	this->frame->FlipNormals();
	this->screen->FlipNormals();
}

bool jumbotron::Initialize(int slices)
{
	if(!this->pillar->Initialize(slices))
		return false;
	if(!this->frame->Initialize(slices))
		return false;
	if(!this->screen->Initialize(slices, "dummy", MainView_fbo))
		return false;
	return true;
}

void jumbotron::TakeDown(void)
{
	this->pillar->TakeDown();
	this->frame->TakeDown();
	this->screen->TakeDown();
}

jumbotron::~jumbotron()
{
	delete pillar;
	delete frame;
	delete screen;
}

void jumbotron::switch_shader(void)
{
	this->pillar->switch_shader();
	this->frame->switch_shader();
	this->screen->switch_shader();
}

//////////////////////////////////
//functions for ball_params
jumbotron_params::jumbotron_params(const GLfloat & Rad, const GLfloat & Ang, const GLfloat & Ht)
{
	this->radius = Rad;
	this->angle = Ang;
	this->height = Ht;
}

jumbotron_params::jumbotron_params(const jumbotron_params & other)
{
	this->radius = other.radius;
	this->angle = other.angle;
	this->height = other.height;
}