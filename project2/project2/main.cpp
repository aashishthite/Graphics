/*	A more sophisticated example of modern OpenGL
	Perry Kivolowitz - UW - Madison - CS 559 demo

	In this example program, I will build a solid
	object comprised of two triangle fans. Note 
	these are topologically triangle fans but the
	OpenGL triangle fan functionality is not being
	used. 

	Created:	02/28/13
	Updates:	03/05/13 - continued improvements
				Added solid color shader for drawing normals
				Switched to timer based redisplay.
*/

#include <iostream>
#include <assert.h>
#include <vector>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "world.h"
#include "window.h"

using namespace std;
using namespace glm;


int main(int argc, char * argv[])
{

	glutInit(&argc , argv);
	
	

	world* myworld = new world();
	//Argument list of window constructor:
	//X coordinate of window; not guaranteed
	//Y coordinate of window; not guaranteed
	//Pointer to world
	//window name
	//distance to origin
	//fov
	//camera orientation lattitude
	//camera orientation longitude
	//camera orientation spin
	//camera position lattitude
	//camera position longitude
	//camera to nearplane distance
	//camera to farplane
	//To draw camera or not?

	window* simpleview = new window(25, 100, myworld, "On the Moon", -40, 20, 0, 0, 0, 45, 45, 1, 200, true);
	if (glewInit() != GLEW_OK)
	{
		cerr << "GLEW failed to initialize." << endl;
		return 0;
	}

	if(!myworld->Initialize())
	{
			cerr << "main: Initialization of world has failed" << endl;
			return 1;
	}

	glutMainLoop();
	delete myworld;
	delete simpleview;
	return 0;
}
