#include "fence.h"

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

using namespace std;

glm::vec3 fence::GetColor(GLint color)
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

fence::fence()
{
	mycube = new cube(GetColor(2), false);
}

bool fence::Draw(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size, GLfloat radius, GLfloat angle)
{
	const GLfloat thickness = 0.25f;
	const GLfloat height = 1.0f;
	glm::mat4 local_modelview = modelview;
	local_modelview = glm::rotate(local_modelview, angle, glm::vec3(0.0f, 1.0f, 0.0f));
	local_modelview = glm::translate(local_modelview, glm::vec3(radius+(thickness/2.0f), height/2.0f, 0.0f));
	local_modelview = glm::scale(local_modelview, glm::vec3(thickness, height, (radius*2.0f)+(thickness*2)));
	if(!mycube->Draw(projection, local_modelview, size))
	{
		std::cerr << "object_set::Draw fence_model failed" << std::endl;
		return false;
	}
	return true;
}

void fence::FlipNormals(void)
{
	this->mycube->FlipNormals();
}

bool fence::Initialize(int slices)
{
	return this->mycube->Initialize(slices);
}

void fence::TakeDown(void)
{
	this->mycube->TakeDown();
}

fence::~fence()
{
	delete mycube;
}

void fence::switch_shader(void)
{
	this->mycube->switch_shader();
}

//////////////////////////////////
//functions for ball_params
fence_params::fence_params(const GLfloat & Rad, const GLfloat & Ang,b2World* thisworld)
{
	this->radius = Rad;
	this->angle = Ang;
	b2BodyDef groundBodyDef;
	b2PolygonShape groundBox;
	switch(int(Ang))
	{
		case 0:
			groundBodyDef.position.Set(0.0f, -25.5f);
			this->body=thisworld->CreateBody(&groundBodyDef);			
			groundBox.SetAsBox(25.0f, 0.5f);
			this->body->CreateFixture(&groundBox, 0.0f);
			break;
		case 90:
			groundBodyDef.position.Set(25.5f, 0.0f);
			this->body=thisworld->CreateBody(&groundBodyDef);
			groundBox.SetAsBox(0.5f, 25.0f);
			this->body->CreateFixture(&groundBox, 0.0f);
			break;
		case 180:
			groundBodyDef.position.Set(0.0f, 25.5f);
			this->body=thisworld->CreateBody(&groundBodyDef);
			groundBox.SetAsBox(25.0f, 0.5f);
			this->body->CreateFixture(&groundBox, 0.0f);
			break;
		case 270:
			groundBodyDef.position.Set(-25.5f, 0.0f);
			this->body=thisworld->CreateBody(&groundBodyDef);
			groundBox.SetAsBox(0.5f, 25.0f);
			this->body->CreateFixture(&groundBox, 0.0f);
			break;


	}


	
	
	

	// The extents are the half-widths of the box.
	

	// Add the ground fixture to the ground body.
	

}

fence_params::fence_params(const fence_params & other)
{
	this->radius = other.radius;
	this->angle = other.angle;
	this->body = other.body;
}