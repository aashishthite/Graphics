#pragma once
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <vector>
#include "camera.h"
#include "world.h"

using namespace std;

class world;
class camera;
class window
{
	private:
		GLint handle;
		camera *cam;
		world *myworld;
		vector<string> instructions;
		void DisplayInstructions(void);
	public:
		window(GLint x_pixel, GLint y_pixel, world* Myworld, const char* name, GLint Distance, GLint Fov, GLint O_lat, GLint O_long, GLint O_spin, GLint P_lat, GLint P_long, GLint Nearplane, GLint Farplane, bool Draw);
		void ReshapeFunc(GLint w, GLint h);
		void KeyboardFunc(unsigned char c, int x, int y);
		void SpecialFunc(int c, int x, int y);
		void DisplayFunc(void);
		void CloseFunc(void);
		~window();
		GLint height;
		GLint width;
		GLfloat aspect_ratio;
};