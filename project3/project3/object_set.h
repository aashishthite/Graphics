#pragma once
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include "constants.h"
#include "window.h"
#include "stool.h"
#include "tree.h"
#include "ball.h"
#include "fence.h"
#include "textured_square.h"
#include "textured_disk.h"

#include "textured_cuboid.h"
#include "Contact_Listener.h"
class MyContactListener;
class window;

class object_set
{
	private:
		std::vector<stool_params> stool_properties;
		std::vector<tree_params> tree_properties;
		std::vector<ball_params> ball_properties;
		std::vector<fence_params> fence_properties;
		stool* stool_model;
		tree* tree_model;
		ball* ball_model;
		fence* fence_model;
		int curr_stool; 
		textured_disk* ground;
		textured_cuboid* building;

public:
		bool Draw(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size, bool is_paused);
		void UpdatePhysics(window *win);
		object_set(int);

		void change_active_stool(void);
		void toggle_active_stool(void);

		void Decrease_stool_heights(void);
		void Increase_stool_heights(void);

		bool Initialize(int slices);
		void TakeDown(void);
		void FlipNormals(void);
		~object_set();
		void switch_shader(void);
		GLfloat getStriker_x_Position(void);
		GLfloat getStriker_z_Position(void);
		GLfloat getStrikerDirection(void);
		b2World* world2d;
		int ball_count;
		int targets_remaining;
		 MyContactListener myContactListenerInstance;
		 //float32 curr_dir;

		 void switch_special_effect(void);
		 bool game_won;
};