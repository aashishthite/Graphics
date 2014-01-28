#pragma once
#include <Box2D/Box2D.h>
#include<iostream>
#include "constants.h"
#include "ball.h"
//class MyContactListener;
class ball_params;
using namespace std;


class MyContactListener : public b2ContactListener
{
	
	void BeginContact(b2Contact* contact) {

		

		void * bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();

		if (bodyUserData)
		{
			ball_params  temp= *(static_cast<ball_params *>(bodyUserData));

			
			if(temp.ball_num==1)
			{
				bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
				if (bodyUserData)
				{
					ball_params*  temp1= (static_cast<ball_params *>(bodyUserData));

			
					if(temp1->ball_num>2)///////////////////////////////////////////////////////////////////////////////////////////////////////////
					{
						temp1->type_sphere=2;
						temp1->time=hit_time*240;
					}
					if(temp1->ball_num==2)///////////////////////////////////////////////////////////////////////////////////////////////////////////
					{
						temp1->is_killed=true;
						
						
					}
				}
			}
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			if(temp.ball_num==2)
			{
				bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
				if (bodyUserData)
				{
					ball_params*  temp1= (static_cast<ball_params *>(bodyUserData));

			
					if(temp1->ball_num>2)
					{
						temp1->type_sphere=3;
						temp1->time=0;
					}
					
				}
			}
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			
		}

		bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();


		
		if (bodyUserData)
		{
			ball_params  temp= *(static_cast<ball_params *>(bodyUserData));

			
			if(temp.ball_num==1)
			{
				bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
				if (bodyUserData)
				{
					ball_params*  temp1= (static_cast<ball_params *>(bodyUserData));

			
					if(temp1->ball_num>2)///////////////////////////////////////////////////////////////////////////////////////////////////////////
					{
						temp1->type_sphere=2;
						temp1->time=hit_time*240;
						
					}
					if(temp1->ball_num==2)///////////////////////////////////////////////////////////////////////////////////////////////////////////
					{
						temp1->is_killed=true;
						
						
					}
				}
			}
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			if(temp.ball_num==2)
			{
				bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
				if (bodyUserData)
				{
					ball_params*  temp1= (static_cast<ball_params *>(bodyUserData));

			
					if(temp1->ball_num>2)
					{
						temp1->type_sphere=3;
						temp1->time=0;
					}
				}
			}
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
		}





	}


	void EndContact(b2Contact* contact) {

		//check if fixture A was the main ball
		void * bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
		if (bodyUserData)
		{

			ball_params  temp= *(static_cast<ball_params *>(bodyUserData));

			
			if(temp.ball_num==1)
			{
	
				b2Body* temp_body=contact->GetFixtureA()->GetBody();
				b2Vec2 velocity= temp_body->GetLinearVelocity();
				b2Vec2 dir=velocity;
				dir.Normalize();
				float theta=atan2(dir.x,dir.y);
				/*if(abs(dir.y)<0.0001)
				{
					if(dir.x>0.0001)
						theta=-PI/2.0f;
					else if(abs(dir.x)<0.0001)
						theta=0;
					else
						theta=PI/2.0f;
				}
				else if(dir.y>0.0001)
				{
					theta=atan(dir.x/dir.y);
				}
				else
				{
					theta=atan(dir.x/dir.y)+PI;
				}*/
				curr_dir=theta;


			}
			
		}
		bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
		if (bodyUserData)
		{

			ball_params  temp= *(static_cast<ball_params *>(bodyUserData));
			
			if(temp.ball_num==1)
			{
				
				b2Body* temp_body=contact->GetFixtureB()->GetBody();
				b2Vec2 velocity= temp_body->GetLinearVelocity();
				b2Vec2 dir=velocity;
				dir.Normalize();
				float theta=atan2(dir.x,dir.y);
				/*
				if(abs(dir.y)<0.0001)
				{
					if(dir.x>0.0001)
						theta=PI/2.0f;
					else if(abs(dir.x)<0.0001)
						theta=0;
					else
						theta=-PI/2.0f;
				}
				else if(dir.y>0.0001)
				{
					theta=atan(dir.x/dir.y);
				}
				else
				{
					theta=atan(dir.x/dir.y)+PI;
				}*/
				curr_dir=theta;
			}
		}
	}
public:
	float32 curr_dir;
	int hit_time;
};