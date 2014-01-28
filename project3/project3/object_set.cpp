#include "object_set.h"

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

using namespace std;

object_set::object_set(int num)
{

	world2d = new b2World(b2Vec2(0.0f, 00.0f));
	world2d->SetContactListener(&myContactListenerInstance);
	myContactListenerInstance.hit_time=30+num*2;
	stool_model = new stool();
	//ground = new textured_disk(glm::vec3(0.5f), 0,15,true);
	//building = new textured_cuboid(glm::vec3(0.5f), 3, 3, 3, true);
	tree_model = new tree();
	ball_model = new ball();
	fence_model = new fence();
	ball_count=num;
	targets_remaining=num;
	game_won=false;

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

	tree_properties.push_back(tree_params(70,0,60,25));
	tree_properties.push_back(tree_params(100,0,40,30));
	tree_properties.push_back(tree_params(40,0,90,35));
	tree_properties.push_back(tree_params(20,0,70,15));
	tree_properties.push_back(tree_params(70,0,10,25));

	tree_properties.push_back(tree_params(-70,0,60,25));
	tree_properties.push_back(tree_params(-100,0,40,30));
	tree_properties.push_back(tree_params(-40,0,90,35));
	tree_properties.push_back(tree_params(-20,0,70,15));
	tree_properties.push_back(tree_params(-70,0,10,25));

	tree_properties.push_back(tree_params(-70,0,-60,25));
	tree_properties.push_back(tree_params(-100,0,-40,30));
	tree_properties.push_back(tree_params(-40,0,-90,35));
	tree_properties.push_back(tree_params(-20,0,-70,15));
	tree_properties.push_back(tree_params(-70,0,-10,25));

	tree_properties.push_back(tree_params(70,0,-60,25));
	tree_properties.push_back(tree_params(100,0,-40,30));
	tree_properties.push_back(tree_params(40,0,-90,35));
	tree_properties.push_back(tree_params(20,0,-70,15));
	tree_properties.push_back(tree_params(70,0,-10,25));

	ball_properties.push_back(ball_params(GLfloat(rand()%40-25),GLfloat(rand()%40-25),world2d,1));//striker ball
	ball_properties.push_back(ball_params(GLfloat(rand()%40-25),GLfloat(rand()%40-25),world2d,2));//Evil ball
	for(int i=0; i<num;i++)
	{
		ball_properties.push_back(ball_params(GLfloat(rand()%40-25),GLfloat(rand()%40-25),world2d,i+3));//Safe balls
	}
	for(unsigned int i=0; i<ball_properties.size(); i++)
	{
		ball_properties[i].body->SetUserData(&(ball_properties[i]));
	}

	fence_properties.push_back(fence_params(25,0,world2d));
	fence_properties.push_back(fence_params(25,90,world2d));
	fence_properties.push_back(fence_params(25,180,world2d));
	fence_properties.push_back(fence_params(25,270,world2d));
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
	if(!this->ball_model->Initialize(slices))
	{
		cerr << "object_set::Initialize ball failed to initialize" << endl;
		return false;
	}
	if(!this->fence_model->Initialize(slices))
	{
		cerr << "object_set::Initialize fence failed to initialize" << endl;
		return false;
	}
	/*
	if(!this->ground->Initialize(slices, "moon.jpg", NULL))
	{
		cerr << "object_set::Initialize ground failed to initialize" << endl;
		return false;
	}
	if(!this->building->Initialize(slices, "brick.jpg", NULL))
	{
		cerr << "object_set::Initialize building failed to initialize" << endl;
		return false;
	}*/
	return true;
}

bool object_set::Draw(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size, bool is_paused)
{
	glm::mat4 local_modelview = modelview;
	unsigned int i,unhit=0;
	game_won=true;
	//draw the balls
	for(i=0; i<ball_properties.size(); i++)
	{
		if(i!=1 || (i==1 && !ball_properties[i].is_killed))//Dont draw the evil ball if it is killed
		{
			if(!this->ball_model->Draw(projection, local_modelview, size, ball_properties[i].pos_x, ball_properties[i].pos_z, &ball_properties[i], getStrikerDirection(),is_paused))
			{
				std::cerr << "object_set::Draw ball_model failed" << std::endl;
				return false;
			}
		}
		else if(i==1 && ball_properties[i].is_killed)
		{
			if(ball_properties[i].body)//Remove the evil ball
			{
				world2d->DestroyBody(ball_properties[i].body);
				ball_properties[i].body->SetUserData(NULL);
				ball_properties[i].body = NULL;

			}
		}
		if(i > 1)
		{
			if(ball_properties[i].time>0 )
			{
				if(!is_paused)
				ball_properties[i].time--;//Decrement ball timer
				
			}
			else
			{
				unhit++;
				ball_properties[i].time=0;
				ball_properties[i].type_sphere=3;
				game_won=false;
			}
		}
	}
	targets_remaining=unhit;
	
	if(game_won)
	{
		//if the game is won get out of the game
		glutLeaveMainLoop();
		return true;
		
	}
	//Draw fence
	for(i=0; i<fence_properties.size(); i++)
	{
		if(!this->fence_model->Draw(projection, local_modelview, size, fence_properties[i].radius, fence_properties[i].angle))
		{
			std::cerr << "object_set::Draw fence_model failed" << std::endl;
			return false;
		}
	}

	/*

	GLfloat giant_scale = 30.0f;
	//Find trabnsformations for the first (giant stool)
	GLfloat default_min_seat_displacement = 2.0f+0.02f+0.135f;
	GLfloat effective_seat_height = stool_properties[0].seat_height/400.0f;
	GLfloat effective_seat_angle = stool_properties[0].seat_height*3600.0f/400.0f;


	glm::mat4 local_modelview = modelview;
	local_modelview = glm::scale(local_modelview, glm::vec3(giant_scale, giant_scale, giant_scale));
	local_modelview = glm::translate(local_modelview, glm::vec3(0.0f, -effective_seat_height, 0.0f));
	local_modelview = glm::translate(local_modelview, glm::vec3(0.0f, -default_min_seat_displacement, 0.0f));
	if(!this->stool_model->Draw(projection, local_modelview, size, stool_properties[0].pos_x, stool_properties[0].pos_y, stool_properties[0].pos_z, stool_properties[0].rot_y, stool_properties[0].seat_height, stool_properties[0].adjust_height, stool_properties[0].highlight_seat))
	{
		std::cerr << "object_set::Draw stool_model failed" << std::endl;
		return false;
	}

	
	local_modelview = glm::translate(local_modelview, glm::vec3(0.0f, effective_seat_height, 0.0f));
	local_modelview = glm::rotate(local_modelview, -effective_seat_angle, glm::vec3(0.0f, 1.0f, 0.0f));
	local_modelview = glm::translate(local_modelview, glm::vec3(0.0f, default_min_seat_displacement, 0.0f));
	//local_modelview = glm::rotate(local_modelview, 90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	
	

	local_modelview = glm::scale(local_modelview, glm::vec3(1.0f/giant_scale, 1.0f/giant_scale, 1.0f/giant_scale));
	unsigned int i;
	for(i=1; i<stool_properties.size(); i++)
	{
		if(!this->stool_model->Draw(projection, local_modelview, size, stool_properties[i].pos_x, stool_properties[i].pos_y, stool_properties[i].pos_z, stool_properties[i].rot_y, stool_properties[i].seat_height, stool_properties[i].adjust_height, stool_properties[i].highlight_seat))
		{
			std::cerr << "object_set::Draw stool_model failed" << std::endl;
			return false;
		}
	}
	*/
	/*
	for(i=0; i<tree_properties.size(); i++)
	{
	 	if(!this->tree_model->Draw(projection, local_modelview, size, tree_properties[i].pos_x, tree_properties[i].pos_y, tree_properties[i].pos_z, tree_properties[i].tree_height))
		{
			std::cerr << "object_set::Draw tree_model failed" << std::endl;
			return false;
		}
	}
	*/
	/*
	////in object set:: draw

	glm::mat4 local_modelview1 = glm::translate(local_modelview, glm::vec3(0.0f, 0.01f, 0.0f));
	local_modelview1 = glm::rotate(local_modelview1, 90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	if(!ground->Draw(projection, local_modelview1, size, 0.0f, 0.0f,0))
	{
		std::cerr << "object_set::Draw ground failed" << std::endl;
		return false;
	}

	glm::mat4 local_modelview2= glm::translate(local_modelview, glm::vec3(0.0f, 0.0f, -10.0f));
	building->Draw(projection, local_modelview2, size, 0.0f, 0.0f);
	if(!building->Draw(projection, glm::translate(local_modelview2,glm::vec3(0.0f,2.0f,0.0f)), size, 0.0f, 0.0f))
	{
		std::cerr << "object_set::Draw building failed" << std::endl;
		return false;
	}
	
	local_modelview=glm::translate(local_modelview,glm::vec3(5.0f,0.0f,8.0f));
	if(!building->Draw(projection,local_modelview, size, 0.0f, 0.0f))
	{
		std::cerr << "object_set::Draw building failed" << std::endl;
		return false;
	}
	if(!building->Draw(projection, glm::translate(local_modelview,glm::vec3(1.0f,0.0f,0.0f)), size, 0.0f, 0.0f))
	{
		std::cerr << "object_set::Draw building failed" << std::endl;
		return false;
	}

	local_modelview=glm::translate(local_modelview,glm::vec3(-12.0f,0.0f,0.0f));
	if(!building->Draw(projection,local_modelview, size, 0.0f, 0.0f))
	{
		std::cerr << "object_set::Draw building failed" << std::endl;
		return false;
	}
	if(!building->Draw(projection, glm::translate(local_modelview,glm::vec3(0.0f,3.0f,0.0f)), size, 0.0f, 0.0f))
	{
		std::cerr << "object_set::Draw building failed" << std::endl;
		return false;
	}
	*/

	return true;
}

void object_set::UpdatePhysics(window *win)
{
	if(!win->paused)
		world2d->Step(1.0f / 60.0f, 6, 2);//Step the world
	unsigned int i;
	b2Vec2 position;

	for(i=0; i<ball_properties.size(); i++)
	{
		if(ball_properties[i].body)
		{
			position=ball_properties[i].body->GetPosition();//update position
			ball_properties[i].pos_x = position.x;
			ball_properties[i].pos_z = -position.y;
		}
	}


		b2Vec2 velocity= ball_properties[0].body->GetLinearVelocity();
		//b2Vec2 dir=velocity;
		//dir.Normalize();
		
		float theta=0;
		b2Vec2 acc= b2Vec2(0.0f,0.0f);
		theta= myContactListenerInstance.curr_dir;
		acc=b2Vec2(cos(theta)*win->mouse_x*velocity.Length()*10.0f/ 360.0f-sin(-theta)*win->mouse_y*10.0f/60.0f, sin(-theta)*win->mouse_x*velocity.Length()*10.0f/ 360.0f+cos(theta)*win->mouse_y*10.0f/60.0f);
		
				
		velocity.x+=acc.x;//*10.0f/ 60.0f;
		velocity.y+=acc.y;//*10.0f/60.0f;
		if(abs(win->mouse_x)>0.01 /*&& win->mouse_y>-0.15*/ && !win->paused)
		{
			b2Vec2 dir=velocity;
				dir.Normalize();
				float theta=atan2(dir.x,dir.y);
				
				if(abs(myContactListenerInstance.curr_dir-theta)<PI/2)
				//if((velocity.Length()>0.5 && b2Dot( velocity, acc )>0) || b2Dot( velocity, acc )<0)
					myContactListenerInstance.curr_dir=theta;
				else 
				{
					if(myContactListenerInstance.curr_dir-theta>0)
						myContactListenerInstance.curr_dir=theta+PI;
					if(myContactListenerInstance.curr_dir-theta<0)
						myContactListenerInstance.curr_dir=theta-PI;
				}
		}
		//velocity=b2Vec2(cos(-theta)*vel.x-sin(-theta)*vel.y,sin(-theta)*vel.x+cos(-theta)*vel.y);
		if(abs(win->mouse_x)<0.05 &&abs(win->mouse_y)<0.05)
			ball_properties[0].body->SetLinearDamping(1.0f);
		else
			ball_properties[0].body->SetLinearDamping(0.0f);
		//velocity=b2Vec2(cos(-theta)*vel.x-sin(-theta)*vel.y,sin(-theta)*vel.x+cos(-theta)*vel.y);
		
		ball_properties[0].body->SetLinearVelocity(velocity);

		if(ball_properties[1].body)
		{
			velocity= ball_properties[1].body->GetLinearVelocity();
			if(velocity.Length()>0.001)
			{
				velocity.Normalize();
				ball_properties[1].body->SetLinearVelocity(35*velocity);
			}
			else
				ball_properties[1].body->SetLinearVelocity(b2Vec2(1.412f,1.412f));
		}
}

object_set::~object_set()
{
	delete stool_model;
	delete tree_model;
	delete ball_model;
	delete fence_model;
	//delete ground;
	//delete building;
}

void object_set::switch_special_effect(void)
{
	ball_model->switch_special_effect();
}

void object_set::TakeDown(void)
{
	stool_model->TakeDown();
	tree_model->TakeDown();
	ball_model->TakeDown();
	fence_model->TakeDown();
	//ground->TakeDown();
	//building->TakeDown();
}

void object_set::FlipNormals(void)
{
	stool_model->FlipNormals();
	tree_model->FlipNormals();
	ball_model->FlipNormals();
	fence_model->FlipNormals();
	//ground->FlipNormals();
	//building->FlipNormals();
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
	ball_model->switch_shader();
	fence_model->switch_shader();
}

GLfloat object_set::getStrikerDirection(void)
{
	return GLfloat(myContactListenerInstance.curr_dir);
}

GLfloat object_set::getStriker_x_Position(void)
{
	return ball_properties[0].pos_x;
}

GLfloat object_set::getStriker_z_Position(void)
{
	return ball_properties[0].pos_z;
}