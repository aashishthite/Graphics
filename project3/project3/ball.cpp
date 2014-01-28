#include "ball.h"

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

using namespace std;

glm::vec3 ball::GetColor(GLint color)
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
		case 6://Red for ball
			return glm::vec3(205.0f/255.0f,0.0f,0.0f);
			break;
		case 7://Blue for ball
			return glm::vec3(0.0f,0.0f,1.0f);
			break;
		case 8://Green for ball
			return glm::vec3(0.0f,205.0f/255.0f,0.0f);
			break;
		case 9://orange for ball
			return glm::vec3(255.0f/255.0f,153.0f/255.0f,0.0f);
			break;
		default:
			cerr << "stool::GetColor - Illegal color; setting to white" <<endl;
			return glm::vec3(1.0f, 1.0f, 1.0f);
			break;
	}
}

ball::ball()
{
	mysphere = new sphere(GetColor(7), 0.5, false);
	hitsphere = new sphere(GetColor(6), 0.5, false);
	safesphere = new sphere(GetColor(8), 0.5, false);
	evilsphere = new sphere(GetColor(9), 0.5, false);
}

bool ball::Draw(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size, GLfloat pos_x, GLfloat pos_z, ball_params* this_ball, GLfloat striker_dir, bool is_paused)
{

	b2Vec2 curr_vel=this_ball->body->GetLinearVelocity();
	float ang1=atan2(curr_vel.x,curr_vel.y);//Angle of linear motion
	float ang2=curr_vel.Length()/200.0f;//Angle of rotational motion
	
	glm::mat4 local_modelview = modelview;
	local_modelview = glm::translate(local_modelview, glm::vec3(pos_x, 0.5f, pos_z));

	glm::mat4 temp_local_modelview = glm::rotate(local_modelview,-(ang1)*180/PI, glm::vec3(0, 1.0f, 0));
	
	
	if(!is_paused)
		this_ball->rolling_angle+=ang2;
	
	temp_local_modelview = glm::rotate(temp_local_modelview,(this_ball->rolling_angle)*180/PI, glm::vec3(-1.0f, 0.0f, 0.0f));
	
	//Draw each sphere
	if(this_ball->type_sphere==1)
	{
		//if(!mysphere->Draw(projection, temp_local_modelview1, size))
		if(!mysphere->Draw(projection, temp_local_modelview, size))
		{
			std::cerr << "ball::Draw mysphere failed" << std::endl;
			return false;
		}
	}
	if(this_ball->type_sphere==2)
	{
		if(!hitsphere->Draw(projection, temp_local_modelview, size))
		{
			std::cerr << "ball::Draw hitsphere failed" << std::endl;
			return false;
		}
		//Display time over the hit ball
			glLineWidth(2.0f);
			stringstream ss;
			ss << this_ball->time/240;
			vector<string> s;
			s.push_back(ss.str());
			
			vector<string> *s1 =&s;

			glColor3f(1.0f, 1.0f, 1.0f);
			glMatrixMode(GL_PROJECTION);
			glPushMatrix();
			glLoadMatrixf(glm::value_ptr(projection));

			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glLoadMatrixf(glm::value_ptr(local_modelview));
			
			glRotatef((-striker_dir) * 180.0f /PI, 0.0f, 1.0f, 0.0f);

			glTranslated(-0.5, 0.5, 0);
			glScaled(0.005, 0.005, 1.0);
			for ( auto i = s1->begin(); i < s1->end(); ++i)
			{		
				glutStrokeString(GLUT_STROKE_MONO_ROMAN, (const unsigned char *) (*i).c_str());

			}
			glLineWidth(1.0f);
			glMatrixMode(GL_MODELVIEW);
			glPopMatrix();

			glMatrixMode(GL_PROJECTION);
			glPopMatrix();
	}
	if(this_ball->type_sphere==3)
	{	
		if(!safesphere->Draw(projection, temp_local_modelview, size))
		{
			std::cerr << "ball::Draw safesphere failed" << std::endl;
			return false;
		}
	}
	if(this_ball->type_sphere==4)
	{	
		if(!evilsphere->Draw(projection, temp_local_modelview, size))
		{
			std::cerr << "ball::Draw evilsphere failed" << std::endl;
			return false;
		}
	}
	return true;
}

void ball::FlipNormals(void)
{
	this->mysphere->FlipNormals();
	this->hitsphere->FlipNormals();
	this->safesphere->FlipNormals();
}

bool ball::Initialize(int slices)
{
	if(!this->mysphere->Initialize(slices))
		return false;
	if(!this->hitsphere->Initialize(slices))
		return false;
	if(!this->safesphere->Initialize(slices))
		return false;
	if(!this->evilsphere->Initialize(slices))
		return false;
	return true;
}

void ball::TakeDown(void)
{
	this->mysphere->TakeDown();
	this->hitsphere->TakeDown();
	this->safesphere->TakeDown();
	this->evilsphere->TakeDown();
}

void ball::switch_special_effect(void)
{
	this->mysphere->current_shader->switch_special_effect();
	this->hitsphere->current_shader->switch_special_effect();
	this->safesphere->current_shader->switch_special_effect();
	this->evilsphere->current_shader->switch_special_effect();
}

ball::~ball()
{
	delete mysphere;
	delete hitsphere;
	delete safesphere;
	delete evilsphere;
}

void ball::switch_shader(void)
{
	this->mysphere->switch_shader();
	this->hitsphere->switch_shader();
	this->safesphere->switch_shader();
	this->evilsphere->switch_shader();
}


//functions for ball_params
ball_params::ball_params(const GLfloat & Posx, const GLfloat & Posz, b2World* thisworld, int num)
{
	this->pos_x = Posx;
	this->pos_z = Posz;
	this->ball_num=num;
	
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;

	bodyDef.position.Set(Posx, Posz);

	body = thisworld->CreateBody(&bodyDef);

	//box2d stuff
	b2CircleShape circle;
	b2FixtureDef fixtureDef;

	circle.m_p.Set(0.0f, 0.0f);
	circle.m_radius = 0.5f;
	
	fixtureDef.shape = &circle;
	//fixtureDef.restitution=0.5f;
	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;
	// Override the default friction.
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution=1.0f;
	
	if(this->ball_num==1)
	{
		type_sphere=1;//Main ball
		
	}
	else if(this->ball_num==2)
	{
		type_sphere=4;//Evil ball
		fixtureDef.density = 0.2f;
	}
	else
	{
		type_sphere=3;//Safe ball
		body->SetLinearDamping(0.4f);
	}
	this->time=0;
	body->CreateFixture(&fixtureDef);
	rolling_angle=0;
	this->is_killed=false;
}

ball_params::ball_params(const ball_params & other)
{
	this->pos_x = other.pos_x;
	this->pos_z = other.pos_z;
	this->body = other.body;
	
	this->ball_num=other.ball_num;
	this->type_sphere=other.type_sphere;
	this->time=other.time;
	this->rolling_angle=other.rolling_angle;
	this->is_killed=other.is_killed;
}