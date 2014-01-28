#pragma once
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <Box2D/Box2D.h>
#include <vector>
#include <iomanip>
#include "camera.h"
#include "world.h"

using namespace std;


class world;
class camera;
class window
{
	private:
		GLint handle;
		bool mainView_is_third;
		camera *striker;
		camera *reflection;
		camera *third;
		camera *top;
		camera* jumbocam1;
		world *myworld;
		vector<string> instructions;
		vector<string> startup_instr;
		vector<string> status_text;
		void DisplayStatus();
		void DisplayInstructions(void);
		bool GLReturnedError(char * s);
		bool game_started;
	public:
		window(GLint x_pixel, GLint y_pixel, world* Myworld, const char* name);
		bool Initialize(void);
		void ReshapeFunc(GLint w, GLint h);
		void MouseFunc(int x, int y);
		void KeyboardFunc(unsigned char c, int x, int y);
		void SpecialFunc(int c, int x, int y);
		void DisplayFunc(void);
		bool Render(camera* mycam, FrameBufferObject* myfbo, GLint w, GLint h, GLfloat AR, GLint attachment);
		bool RenderReflection(camera* mycam, FrameBufferObject* myfbo, GLint w, GLint h, GLint attachment);
		void FboToOrtho(FrameBufferObject* myfbo, FrameBufferObject* mytopfbo);
		void CloseFunc(void);
		~window();
		GLint height;
		GLint width;
		GLfloat aspect_ratio;
		float32 mouse_x;
		float32 mouse_y;
		bool paused;
		int time_remaining;
};