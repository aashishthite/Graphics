#include "window.h"
#include "camera.h"
#include <vector>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Hack to get around the limitation that i cant use member functions to register callbacks
int window_count = 0;
/////////////////////////////////////////////////////////////////////////////////////////////////
int light_id=2;
/////////////////////////////////////////////////////////////////////////////////////////////////
window* first;
window* second;
void CloseFunc_1(void)
{
	first->CloseFunc();
}
void CloseFunc_2(void)
{
	second->CloseFunc();
}
void DisplayFunc_1(void)
{
	first->DisplayFunc();
}
void DisplayFunc_2(void)
{
	second->DisplayFunc();
}
void ReshapeFunc_1(GLint w, GLint h)
{
	first->ReshapeFunc(w,h);
}
void ReshapeFunc_2(GLint w, GLint h)
{
	second->ReshapeFunc(w,h);
}
void KeyboardFunc_1(unsigned char c, int x, int y)
{
	first->KeyboardFunc(c,x,y);
}
void KeyboardFunc_2(unsigned char c, int x, int y)
{
	//this is mapped to the firs camera's display function so that pressing keys will result in the first camera moving
	//map this to second camera's function so as to have equivalent views from both windows.
	second->KeyboardFunc(c,x,y);
}
void SpecialFunc_1(int c, int x, int y)
{
	first->SpecialFunc(c,x,y);
}
void SpecialFunc_2(int c, int x, int y)
{	
	//See above comment in KeyboardFunc_2
	second->SpecialFunc(c,x,y);
}
//End of hack

window::window(GLint x_pixel, GLint y_pixel, world* Myworld, const char* name, GLint Distance, GLint Fov, GLint O_lat, GLint O_long, GLint O_spin, GLint P_lat, GLint P_long, GLint Nearplane, GLint Farplane, bool Draw)
{
	//GLint height = 900;
	//GLint width = 900;
	//GLint x_pos;
	//GLint y_pos;
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(x_pixel, y_pixel);
	handle = glutCreateWindow(name);
	glutFullScreen();
	cam = new camera(Distance, Fov, O_lat, O_long, O_spin, P_lat, P_long, Nearplane, Farplane, Draw);
	myworld = Myworld;
	/* This doesnt work: Member functions can be considered to be equivalnet of a function with an additional argument
	glutDisplayFunc(this->DisplayFunc);
	glutReshapeFunc(this->ReshapeFunc);
	glutKeyboardFunc(this->KeyboardFunc);
	glutSpecialFunc(this->SpecialFunc);*/

	//Hack
	if(0 == window_count)
	{
		first = this;
		glutCloseFunc(CloseFunc_1);
		glutDisplayFunc(DisplayFunc_1);
		glutReshapeFunc(ReshapeFunc_1);
		glutKeyboardFunc(KeyboardFunc_1);
		glutSpecialFunc(SpecialFunc_1);
		window_count++;
	}
	else
	{
		second = this;
		glutCloseFunc(CloseFunc_2);
		glutDisplayFunc(DisplayFunc_2);
		glutReshapeFunc(ReshapeFunc_2);
		glutKeyboardFunc(KeyboardFunc_2);
		glutSpecialFunc(SpecialFunc_2);
	}
	//End of hack
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
	instructions.push_back("General options:");
	instructions.push_back(" x - exits the application");
	instructions.push_back(" s - switch flat/gouraud/phong shaders");
	instructions.push_back(" u - change the universe!");
	instructions.push_back("");
	instructions.push_back("Debug options:");
	instructions.push_back(" w - toggles wireframe");
	instructions.push_back(" n - toggles normals");
	instructions.push_back(" a - toggles axis");
	instructions.push_back(" g - toggles grid");
	instructions.push_back(" F11,F12 - Adjusts number of slices");
	instructions.push_back("");
	instructions.push_back("Camera Settings:");
	instructions.push_back(" UP,DOWN,LEFT,RIGHT - Orbits camera");
	instructions.push_back(" Home,End,Delete,PageDown - Swivels camera, maintaining its position");
	instructions.push_back(" Insert,PageUp - Spins camera around its axis");
	instructions.push_back(" +,- - Moves camera relative to origin");
	instructions.push_back(" *,/ - Adjusts the field of view of camera");
	instructions.push_back(" F1,F2 - Adjusts the near plane location");
	instructions.push_back(" F3,F4 - Adjusts the far plane location");
	instructions.push_back("");
	instructions.push_back("Lights:");
	instructions.push_back(" 1 - Toggles light source 1 (top)");
	instructions.push_back(" 2 - Toggles light source 2 (right)");
	instructions.push_back(" 3 - Toggles light source 3 (left)");
	instructions.push_back(" 4 - Toggles light source 4 (bottom)");
	instructions.push_back("");
	instructions.push_back("Interacting with stools:");
	instructions.push_back(" Tab - Switches the highlighted stool");
	instructions.push_back(" ` - Selects a highlighted stool (Selected stools get marked by a square");
	instructions.push_back(" r,f - Adjusts the seat height of selected stools");
	light_id = 2;

	 window_count += 1;
}

void window::ReshapeFunc(GLint w, GLint h)
{
	if (h > 0)
	{
		height = h;
		width = w;
		aspect_ratio = float(w) / float(h);
	}
}

void window::KeyboardFunc(unsigned char c, int x, int y)
{
	switch (c)
	{
		case 'a':
			myworld->mydebug->FlipAxis();
			myworld->TakeDown();
			myworld->Initialize();
			break;
		case 'g':
			myworld->mydebug->FlipGrid();
			myworld->TakeDown();
			myworld->Initialize();
			break;

		case 'f':
			myworld->myobjects->Decrease_stool_heights();
			break;
		case 's':
			myworld->switch_shader();
			break;
		case 'r':
			myworld->myobjects->Increase_stool_heights();
			break;

		case 'u':
			myworld->switch_universe();
			myworld->TakeDown();
			myworld->Initialize();
			break;

		case 'w':
			myworld->FlipWireFrame();
			break;
		case '+':
			cam->IncrementDistance();
			break;
		case '-':
			cam->DecrementDistance();
			break;
		case '*':
			cam->DecrementFov();
			break;
		case '/':
			cam->IncrementFov();
			break;

		case 127: //delete key
			cam->Decrement_orient_longitude();
			break;

		case 9: //Tab key
			myworld->myobjects->change_active_stool();
			break;
		case 96: //Back tick
			myworld->myobjects->toggle_active_stool();
			break;
			//////////////////////////////////////////////////////
		case '1':
			if(light_id%2==0)
				light_id/=2;
			else
				light_id*=2;
			break;
		case '2':
			if(light_id%3==0)
				light_id/=3;
			else
				light_id*=3;
			break;
		case '3':
			if(light_id%5==0)
				light_id/=5;
			else
				light_id*=5;
			break;
		case '4':
			if(light_id%7==0)
				light_id/=7;
			else
				light_id*=7;
			break;
			//////////////////////////////////////////////////////
		case 'x':
		case 27:
			glutLeaveMainLoop();
			return;
		case 'n':
			myworld->FlipNormals();
			break;
	}
}

void window::SpecialFunc(int c, int x, int y)
{
	switch (c)
	{
		case GLUT_KEY_UP:
			cam->Increment_position_lattitude();
			break;
		case GLUT_KEY_DOWN:
			cam->Decrement_position_lattitude();
			break;
		case GLUT_KEY_LEFT:
			cam->Increment_position_longitude();
			break;
		case GLUT_KEY_RIGHT:
			cam->Decrement_position_longitude();
			break;
		case GLUT_KEY_HOME:
			cam->Decrement_orient_lattitude();
			break;
		case GLUT_KEY_END:
			cam->Increment_orient_lattitude();
			break;
		case GLUT_KEY_PAGE_DOWN:
			cam->Increment_orient_longitude();
			break;
		//Delete is ascii
		case GLUT_KEY_INSERT:
			cam->Decrement_orient_spin();
			break;
		case GLUT_KEY_PAGE_UP:
			cam->Increment_orient_spin();
			break;

		case GLUT_KEY_F1:
			cam->DecrementNearplane();
			break;
		case GLUT_KEY_F2:
			cam->IncrementNearplane();
			break;
		case GLUT_KEY_F3:
			cam->DecrementFarplane();
			break;
		case GLUT_KEY_F4:
			cam->IncrementFarplane();
			break;
		case GLUT_KEY_F5:
			cam->FlipDraw();
			break;
		case GLUT_KEY_F6:
			//if(this == first)
			//{
			//	second->cam->FlipDraw();
			//}
			//if(this == second)
			//{
			//	first->cam->FlipDraw();
			//}
			break;
		case GLUT_KEY_F11:
			myworld->DecrementSlices();
			myworld->TakeDown();
			myworld->Initialize();
			break;
		case GLUT_KEY_F12:
			myworld->IncrementSlices();
			myworld->TakeDown();
			myworld->Initialize();	
			break;
		default:
			return;
	}
}

void window::DisplayFunc(void)
{
	glEnable(GL_CULL_FACE);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, width, height);
	
	//Setup modelview and projection matrices
	glm::mat4 projection;
	glm::mat4 modelview;
	cam->SetupCamera(this, projection, modelview);

	//Draw the world!
	glPolygonMode(GL_FRONT_AND_BACK, myworld->GetWireFrame() ? GL_LINE : GL_FILL);

	myworld->DrawWorld(this, projection,modelview);

	//Draw the cameras
	//Removing this if condition to draw the camera (is an awesome debug tool)
	//You could see the frustum border flickering in the first person view; confirms that frustum is perfect!
	if(this == second)
	{
		//TODO: modelview, projection should be 
		first->cam->DrawCamera();
		second->cam->DrawCamera();
	}

	//Display instructions on window
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	DisplayInstructions();

	glutSwapBuffers();
	glutPostRedisplay();
}

window::~window(void)
{
	delete cam;
}

void window::DisplayInstructions()
{
	if (handle == -1)
		return;

	vector<string> *s = &instructions;
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glColor3f(1.0f, 1.0f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, 1, 10);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(10, 15 * s->size(), -5.5);
	glScaled(0.1, 0.1, 1.0);
	for (auto i = s->begin(); i < s->end(); ++i)
	{
		glPushMatrix();
		glutStrokeString(GLUT_STROKE_MONO_ROMAN, (const unsigned char *) (*i).c_str());
		glPopMatrix();
		glTranslated(0, -150, 0);
	}
}

void window::CloseFunc()
{
	handle = -1;
	myworld->TakeDown();
}