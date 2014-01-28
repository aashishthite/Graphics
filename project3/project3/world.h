#pragma once
#include <gl/glew.h>
#include <gl/freeglut.h>
#include "environ.h"
#include "debug.h"
#include "arena.h"
#include "object_set.h"
#include "window.h"
#include "textured_sphere.h"

class window;
class object_set;
class world
{
	private:
		int slices;
		bool wireframe;
		textured_sphere* background;
		int universe_texture;
	public:
		void FlipNormals(void);
		void FlipWireFrame(void);
		bool GetWireFrame(void);
		//environ *environ;
		arena *myarena;
		debug *mydebug;
		object_set* myobjects;
		world(int);
		bool Initialize(void);
		bool DrawWorld(glm::mat4 projection_matrix, glm::mat4 modelview_matrix, glm::ivec2 size, window *win);
		void UpdatePhysicsWorld(window *win);
		void TakeDown(void);
		void DecrementSlices(void);
		void IncrementSlices(void);
		~world();
		void switch_shader(void);
		void switch_universe(void);
		GLfloat getStrikerDirection(void);
		GLfloat getStriker_x_Position(void);
		GLfloat getStriker_z_Position(void);
		void switch_special_effect(void);
		void switch_special_mode(void);
};