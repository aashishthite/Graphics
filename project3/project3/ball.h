#pragma once
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include "object.h"
#include "shader.h"
#include "sphere.h"
#include "constants.h"

class ball_params;
class ball
{
	private:
		glm::vec3 GetColor(GLint color);
		sphere* mysphere;
		sphere* hitsphere;
		sphere* safesphere;
		sphere* evilsphere;

	public:
		bool ball::Draw(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size, GLfloat pos_x, GLfloat pos_y,ball_params* this_ball, GLfloat striker_dir, bool is_paused);
		ball();
		void FlipNormals(void);
		bool Initialize(int slices);
		void TakeDown(void);
		~ball();
		void switch_shader(void);
		void switch_special_effect(void);
};

class ball_params
{
	public:
		GLfloat pos_x;
		GLfloat pos_z;
		
		int ball_num;
		ball_params(const GLfloat & Posx, const GLfloat & Posz, b2World*, int num);
		
		ball_params(const ball_params & other);
		b2Body* body;

		int time;
		int type_sphere;
		float rolling_angle;
		bool is_killed;
};