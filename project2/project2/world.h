#pragma once
#include <gl/glew.h>
#include <gl/freeglut.h>
#include "environ.h"
#include "debug.h"
#include "object_set.h"
#include "window.h"
#include "textured_sphere.h"

class window;
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
		debug *mydebug;
		object_set* myobjects;
		world(void);
		bool Initialize(void);
		void DrawWorld(window *win, glm::mat4 projection_matrix, glm::mat4 modelview_matrix);
		void TakeDown(void);
		void DecrementSlices(void);
		void IncrementSlices(void);
		~world();
		void switch_shader(void);
		void switch_universe(void);
};