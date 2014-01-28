#include "window.h"
#include "camera.h"
#include <vector>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "fbo.h"


GLint mainview_render_attachment;
GLint mainview_display_attachment;

FrameBufferObject* MainView_fbo;
FrameBufferObject* ReflectionView_fbo;
FrameBufferObject* ReflectionTop_fbo;
FrameBufferObject* TopView_fbo;

bool rendertopview;
GLfloat Reflection_wcrop;
GLfloat Reflection_hcrop;

//Hack to get around the limitation that i cant use member functions to register callbacks
//int window_count = 0;
int light_id = 2;
int after_effect = 0;
window* first;
//window* second;
void CloseFunc_1(void)
{
	first->CloseFunc();
}
/*
void CloseFunc_2(void)
{
	second->CloseFunc();
}
*/
void DisplayFunc_1(void)
{
	//first->DisplaytoFbo();
	first->DisplayFunc();
}
/*
void DisplayFunc_2(void)
{
	second->DisplayFunc();
}
*/
void ReshapeFunc_1(GLint w, GLint h)
{
	first->ReshapeFunc(w,h);
}
/*
void ReshapeFunc_2(GLint w, GLint h)
{
	second->ReshapeFunc(w,h);
}
*/
void KeyboardFunc_1(unsigned char c, int x, int y)
{
	first->KeyboardFunc(c,x,y);
}

void MouseFunc_1(int x, int y)
{
	first->MouseFunc(x,y);
}
/*
void KeyboardFunc_2(unsigned char c, int x, int y)
{
	//this is mapped to the firs camera's display function so that pressing keys will result in the first camera moving
	//map this to second camera's function so as to have equivalent views from both windows.
	second->KeyboardFunc(c,x,y);
}
*/
void SpecialFunc_1(int c, int x, int y)
{
	first->SpecialFunc(c,x,y);
}
/*
void SpecialFunc_2(int c, int x, int y)
{	
	//See above comment in KeyboardFunc_2
	second->SpecialFunc(c,x,y);
}
*/
//End of hack

window::window(GLint x_pixel, GLint y_pixel, world* Myworld, const char* name)
{
	//GLint height = 900;
	//GLint width = 900;
	//GLint x_pos;
	//GLint y_pos;
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	
	//For antialiasing
	glBlendFunc( GL_SRC_ALPHA_SATURATE, GL_ONE );
	glEnable( GL_BLEND );
	glDisable( GL_DEPTH_TEST );
	glHint(GL_POLYGON_SMOOTH, GL_NICEST);
	glEnable(GL_POLYGON_SMOOTH);
	////////////////////
	this->width = 1920;
	this->height = 1200;
	glutInitWindowSize(this->width, this->height);
	glutInitWindowPosition(x_pixel, y_pixel);
	handle = glutCreateWindow(name);
	glutFullScreen();

	game_started = false;
	
	paused=true;

	//Argument list of camera constructor
	//ybias
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
	mainView_is_third = true;
	third = new camera(0.0f, -90.0f, 30.0f, 0.0f, 0.0f, 0.0f, 45.0f, 45.0f, 1.0f, 400.0f, false);
	striker = new camera(-0.5f, -50.0f, 40.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.1f, 400.0f, false);
	top = new camera(0.0f, -100.0f, 30.0f, 0.0f, 0.0f, 0.0f, 89.9f, 0.0f, 1.0f, 400.0f, false);
	reflection = new camera(0.0f, -50.0f, 30.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.1f, 400.0f, false);

	//top = new camera(0.0f, -100.0f, 70.0f, 0.0f, 0.0f, 0.0f, 89.9f, 0.0f, 1.0f, 200.0f, false);
	//third = striker;
	myworld = Myworld;
	/* This doesnt work: Member functions can be considered to be equivalnet of a function with an additional argument
	glutDisplayFunc(this->DisplayFunc);
	glutReshapeFunc(this->ReshapeFunc);
	glutKeyboardFunc(this->KeyboardFunc);
	glutSpecialFunc(this->SpecialFunc);*/

	//Hack
	//if(0 == window_count)
	//{
		first = this;
		glutCloseFunc(CloseFunc_1);
		glutDisplayFunc(DisplayFunc_1);
		glutReshapeFunc(ReshapeFunc_1);
		glutPassiveMotionFunc(MouseFunc_1);
		glutKeyboardFunc(KeyboardFunc_1);
		glutSpecialFunc(SpecialFunc_1);
/*		window_count++;
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
	*/
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
	instructions.push_back("Welcome to Moshball - Press \"enter key\" for action!");
	instructions.push_back("");
	instructions.push_back("General options:");
	instructions.push_back(" x/Esc - exits the application");
	instructions.push_back(" p - pause the game and view this menu");
	instructions.push_back("");
	instructions.push_back("Controls:");
	instructions.push_back(" Mouse - Position the mouse to move forward/backward and turn right/left");
	instructions.push_back("       - Use the crosshair at the centre of the screen as a reference");
	instructions.push_back("");
	instructions.push_back("Preferences:");
	instructions.push_back(" s - switch flat/gouraud/phong shaders");
	instructions.push_back(" u - change the universe!");
	instructions.push_back(" F7 - Customize balls");
	instructions.push_back(" F8 - Negative/Posterize");
	instructions.push_back(" F9 - Floor shading");
	instructions.push_back("");
	instructions.push_back("Camera Prefernces for third person view:");
	instructions.push_back(" UP,DOWN,LEFT,RIGHT - Orbits camera");
	instructions.push_back(" Home,End,Delete,PageDown - Swivels camera, maintaining its position");
	instructions.push_back(" Insert,PageUp - Spins camera around its axis");
	instructions.push_back(" +,- - Moves camera relative to origin");
	instructions.push_back(" *,/ - Adjusts the field of view of camera");
	instructions.push_back(" F1,F2 - Adjusts the near plane location");
	instructions.push_back(" F3,F4 - Adjusts the far plane location");
	instructions.push_back("");
	instructions.push_back("Lighting Preferences:");
	instructions.push_back(" 1 - Toggles light source 1 (top)");
	instructions.push_back(" 2 - Toggles light source 2 (right)");
	instructions.push_back(" 3 - Toggles light source 3 (left)");
	instructions.push_back(" 4 - Toggles light source 4 (bottom)");
	instructions.push_back("");
	instructions.push_back("Debug options:");
	instructions.push_back(" w - toggles wireframe");
	instructions.push_back(" n - toggles normals");
	instructions.push_back(" a - toggles axis");
	instructions.push_back(" g - toggles grid");
	instructions.push_back(" F11,F12 - Adjusts number of slices");
	instructions.push_back("");
	//instructions.push_back("Interacting with stools:");
	//instructions.push_back(" Tab - Switches the highlighted stool");
	//instructions.push_back(" ` - Selects a highlighted stool (Selected stools get marked by a square");
	//instructions.push_back(" r,f - Adjusts the seat height of selected stools");
	light_id = 2;

	//window_count += 1;
	time_remaining=myworld->myobjects->ball_count<10?myworld->myobjects->ball_count*8*60:40+myworld->myobjects->ball_count*4*60;

    MainView_fbo = new FrameBufferObject();
	TopView_fbo = new FrameBufferObject();
	ReflectionView_fbo = new FrameBufferObject();
	ReflectionTop_fbo = new FrameBufferObject();

	mainview_render_attachment = 0;
	mainview_display_attachment = 1;
}

bool window::Initialize(void)
{
	if(!MainView_fbo->Initialize(glm::ivec2(this->width, this->height), 2, true))
	{
		cerr << "window:: Frame buffer for main view failed to initialize." << endl;
		return false;
	}
	if(!TopView_fbo->Initialize(glm::ivec2(300, 300), 1, true))
	{
		cerr << "Frame buffer for top view failed to initialize." << endl;
		return false;
	}
	if(!ReflectionView_fbo->Initialize(glm::ivec2(3000, 3000), 1, true))
	{
		cerr << "Frame buffer for main reflection failed to initialize." << endl;
		return false;
	}
	if(!ReflectionTop_fbo->Initialize(glm::ivec2(300, 300), 1, true))
	{
		cerr << "Frame buffer for main reflection failed to initialize." << endl;
		return false;
	}
	return true;
}
//Callback for change in window size
void window::ReshapeFunc(GLint w, GLint h)
{
	if (h > 0)
	{
		height = h;
		width = w;
		aspect_ratio = float(w) / float(h);
	}

}
//callback for mouse movement
void window::MouseFunc(int x, int y)
{
	int current_window=glutGetWindow();
	if(current_window==handle)
	{
		if(width!=0)
		{			
			mouse_x=(x-width/2)/float(width)*2;
			mouse_y=-(y-height/2)/float(height)*2;
			//cout<<mouse.x<<" "<<mouse.y<<endl;
		}		
	}
}
//callback for key presses
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
		case 'p':
			if(game_started)
			{
				this->paused=!this->paused;
			}
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
			third->IncrementDistance();
			break;
		case '-':
			third->DecrementDistance();
			break;
		case '*':
			third->DecrementFov();
			break;
		case '/':
			third->IncrementFov();
			break;

		case 127: //delete key
			third->Decrement_orient_longitude();
			break;

		case 9: //Tab key
			myworld->myobjects->change_active_stool();
			break;
		case 96: //Back tick
			myworld->myobjects->toggle_active_stool();
			break;
		case 'c':
			mainView_is_third = !mainView_is_third;
			break;

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
		case 'x':
		case 27:
			//MainView_fbo->TakeDown();
			//ReflectionView_fbo->TakeDown();
			//TopView_fbo->TakeDown();
			cout<<"Exit pressed by user."<<endl;
			glutLeaveMainLoop();
			return;
		case 'n':
			myworld->FlipNormals();
			break;
		case 13:
			//Carriage return
			game_started = true;
			paused=false;
			mainView_is_third = false;
			break;
	}
}

void window::SpecialFunc(int c, int x, int y)
{
	switch (c)
	{
		case GLUT_KEY_UP:
			third->Increment_position_lattitude();
			break;
		case GLUT_KEY_DOWN:
			third->Decrement_position_lattitude();
			break;
		case GLUT_KEY_LEFT:
			third->Increment_position_longitude();
			break;
		case GLUT_KEY_RIGHT:
			third->Decrement_position_longitude();
			break;
		case GLUT_KEY_HOME:
			third->Decrement_orient_lattitude();
			break;
		case GLUT_KEY_END:
			third->Increment_orient_lattitude();
			break;
		case GLUT_KEY_PAGE_DOWN:
			third->Increment_orient_longitude();
			break;
		//Delete is ascii
		case GLUT_KEY_INSERT:
			third->Decrement_orient_spin();
			break;
		case GLUT_KEY_PAGE_UP:
			third->Increment_orient_spin();
			break;

		case GLUT_KEY_F1:
			third->DecrementNearplane();
			break;
		case GLUT_KEY_F2:
			third->IncrementNearplane();
			break;
		case GLUT_KEY_F3:
			third->DecrementFarplane();
			break;
		case GLUT_KEY_F4:
			third->IncrementFarplane();
			break;
		case GLUT_KEY_F5:
			third->FlipDraw();
			break;
		case GLUT_KEY_F6:
			//if(this == first)
			//{
			//	second->third->FlipDraw();
			//}
			//if(this == second)
			//{
			//	first->third->FlipDraw();
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
		case GLUT_KEY_F7:
			myworld->switch_special_effect();
			break;
		case GLUT_KEY_F8:
			after_effect = after_effect + 1;
			if(after_effect == 3)
			{
				after_effect = 0;
			}
			break;
		case GLUT_KEY_F9:
			myworld->switch_special_mode();
			break;
		default:
			return;
	}
}

void window::DisplayFunc(void)
{

	this->GLReturnedError("window::DisplayFunc - Entry");

	if(!paused)
	{
		//Update physics
		myworld->UpdatePhysicsWorld(this);
	}
	camera* myview_cam;
	
	//Render to FBOs
	if(mainView_is_third)
	{
		myview_cam = third;
	}
	else
	{
		/*  Set striker properties here  */
		GLfloat striker_dir;
		GLfloat striker_x;
		GLfloat striker_z;

		GLfloat distance;
		GLfloat orient_longitude;
		GLfloat position_longitude;

		
		striker_dir = myworld->getStrikerDirection();
		striker_x = myworld->getStriker_x_Position();
		striker_z = myworld->getStriker_z_Position();
		
		//striker_dir = 1.57f; 
		//striker_x = -24.0f;
		//striker_z = -24.0f;

		
		distance =  - (glm::length(glm::vec2(striker_x,striker_z)));
		position_longitude = -(180.0f * atan2(striker_x,striker_z))/PI;
		//orient_longitude = - (((180.0f * striker_dir)/PI) +  position_longitude);
		//orient_longitude = (- position_longitude) + (- 180.0f) + (+ ((180.0f * striker_dir)/PI));

		//This works!
		orient_longitude = (- position_longitude) + (+ ((180.0f * striker_dir)/PI));
		
		/*
		distance =  (glm::length(glm::vec2(striker_x,striker_z)));
		orient_longitude = -(180.0f * striker_dir)/PI;
		position_longitude = (180.0f * atan2(striker_x,striker_z))/PI;
		*/
		//cout << striker_x << " " <<striker_z <<" " << striker_dir << " " << distance << " " << position_longitude << " " << orient_longitude <<endl;
		
		striker->SetDistance(distance);
		striker->SetOrientLat(0.0f);
		striker->SetOrientLong(orient_longitude);
		striker->SetPosLat(0.0f);
		striker->SetPosLong(position_longitude);
		myview_cam = striker;

	}

	rendertopview = false;
	if(!RenderReflection(myview_cam, ReflectionView_fbo, 3000, 3000, 0))
	{
		cerr << "window::Render main reflection failed" << endl;
	}
	if(!Render(myview_cam,MainView_fbo, this->width, this->height, GLfloat(this->width)/GLfloat(this->height), mainview_render_attachment))
	{
		cerr << "window::Render main view failed" << endl;
	}
	rendertopview = true;
	if(!RenderReflection(top, ReflectionTop_fbo, 300, 300, 0))
	{
		cerr << "window::Render top reflection failed" << endl;
	}
	if(!Render(top, TopView_fbo, 300, 300, 1.0f, 0))
	{
		cerr << "window::Render top view failed" << endl;
	}

	this->GLReturnedError("window::DisplayFunc - After Render");


	glEnable(GL_CULL_FACE);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	this->GLReturnedError("window::DisplayFunc - Before drawing from fbo to screen via orthographic projection");

	FboToOrtho(MainView_fbo, TopView_fbo);
	this->GLReturnedError("window::DisplayFunc - After drawing from fbo to screen via orthographic projection");

	//glViewport(0, 0, 300, 300);
	//FboToOrtho(MainView_fbo);
	/*
	glViewport(0, 0, width, height);
	//Setup modelview and projection matrices
	glm::mat4 projection;
	glm::mat4 modelview;
	third->SetupCamera(this, projection, modelview);
	//Draw the world!
	glPolygonMode(GL_FRONT_AND_BACK, myworld->GetWireFrame() ? GL_LINE : GL_FILL);
	myworld->DrawWorld(this, projection,modelview);

	*/

	/*
	//Draw the cameras
	//Removing this if condition to draw the camera (is an awesome debug tool)
	//You could see the frustum border flickering in the first person view; confirms that frustum is perfect!
	if(this == second)
	{
		//TODO: modelview, projection should be 
		first->third->DrawCamera();
		second->third->DrawCamera();
	}
	*/

	if(paused)
	{
		//Display instructions on window
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		DisplayInstructions();
		this->GLReturnedError("window::DisplayFunc - After display of instructions");
	}
	if(!paused)
	{
		DisplayStatus();
		time_remaining--;
		
		if(time_remaining<0)
		{
			
			cout<<"Lost!"<<endl;
			cout<<"Time's up!"<<endl;
			glutLeaveMainLoop();
			return;
		}
	}


	glutSwapBuffers();
	this->GLReturnedError("window::DisplayFunc - After glutSwapBuffers");
	glutPostRedisplay();
	this->GLReturnedError("window::DisplayFunc - Exit");

	mainview_render_attachment = 1 - mainview_render_attachment;
	mainview_display_attachment = 1 - mainview_display_attachment;
}

bool window::Render(camera* mycam, FrameBufferObject* myfbo, GLint w, GLint h, GLfloat AR, GLint attachment)
{
	bool ret_value = true;
	myfbo->Bind(attachment);
	//glEnable(GL_CULL_FACE);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushAttrib(GL_VIEWPORT_BIT | GL_TRANSFORM_BIT);
	glViewport(0, 0, w, h);
	
	//Setup modelview and projection matrices
	glm::mat4 projection;
	glm::mat4 modelview;
	mycam->SetupCamera(AR, projection, modelview);

	//Draw the world!
	glPolygonMode(GL_FRONT_AND_BACK, myworld->GetWireFrame() ? GL_LINE : GL_FILL);


	if(!myworld->DrawWorld(projection,modelview ,glm::ivec2(w,h), this))
	{
		cerr << "window::Draw world failed" << endl;
		ret_value = false;
	}
	
	glPopAttrib();
	//glutSwapBuffers();
	//glutPostRedisplay();
	myfbo->Unbind();
	return ret_value;
}

bool window::RenderReflection(camera* mycam, FrameBufferObject* myfbo, GLint w, GLint h, GLint attachment)
{
	GLfloat reflect_pos_lat = mycam->GetPosLat();
	GLfloat reflect_dist = mycam->GetDistance();
	GLfloat reflect_pos_long = mycam->GetPosLong();
	GLfloat reflect_ybias = mycam->GetYBias();

	reflection->SetYBias(-reflect_ybias);
	reflection->SetDistance(reflect_dist);

	reflection->SetPosLat(-reflect_pos_lat);
	reflection->SetPosLong(reflect_pos_long);

	reflection->SetOrientLat(reflect_pos_lat - 90.0f);
	reflection->SetOrientLong(0.0f);
	reflection->SetOrientSpin(reflect_pos_long);

	GLfloat reflect_ht = - (sin(PI*reflect_pos_lat/180.0f) * reflect_dist) - reflect_ybias;
	assert(reflect_ht >= 0.0f);
	GLfloat reflect_signz = cos(PI*reflect_pos_lat/180.0f) * (-reflect_dist) * cos(PI*(-reflect_pos_long)/180.0f);
	GLfloat reflect_absz = abs(reflect_signz);
	GLfloat reflect_fov = 2.0f * atan((25.0f+reflect_absz)/reflect_ht) * 180.0f/PI;
	reflection->SetFOV(reflect_fov);

	GLfloat reflect_signx = cos(PI*reflect_pos_lat/180.0f) * (-reflect_dist) * sin(PI*(-reflect_pos_long)/180.0f);
	GLfloat reflect_absx = abs(reflect_signx);
	GLfloat AR = (reflect_absx + 25.0f) / (reflect_absz + 25.0f);
	
	Reflection_wcrop = reflect_signx;
	Reflection_hcrop = reflect_signz;

	if(!Render(reflection, myfbo, w, h, AR, attachment))
	{
		cerr << "window::Render main reflection failed" << endl;
		return false;
	}
	return true;
}

void window::FboToOrtho(FrameBufferObject* myfbo, FrameBufferObject* mytopfbo)
{
	this->GLReturnedError("window::FboToOrtho - Entry");
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glViewport(0, 0, this->width, this->height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, this->width, 0, this->height, 1, 10);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(0, 0, -5.5);
	glPushMatrix();
	
	this->GLReturnedError("window::FboToOrtho - Before binding first texture");
	glBindTexture(GL_TEXTURE_2D, myfbo->texture_handles[mainview_display_attachment]);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2f(GLfloat(this->width), 0.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex2f(GLfloat(this->width), GLfloat(this->height));
		glTexCoord2f(0.0f, 1.0f);
		glVertex2f(0.0f, GLfloat(this->height));
	glEnd();
	this->GLReturnedError("window::FboToOrtho - After glEnd");
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();


	glTranslated(0, 0, 1.0);
	glPushMatrix();
	this->GLReturnedError("window::FboToOrtho - After translation");

	glBindTexture(GL_TEXTURE_2D, mytopfbo->texture_handles[0]);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2f(300.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex2f(300.0f, 300.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex2f(0.0f, 300.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	
	//Draw crosshair
	if(!paused)
	{
		glLoadIdentity();
		glTranslated(GLfloat(this->width)/2.0f, GLfloat(this->height)/2.0f, -4.5);
		glPushMatrix();
		glBegin(GL_LINES);
			glVertex2f(-10.0f, 0.0f);
			glVertex2f(10.0f, 0.0f);
			glVertex2f(0.0f,-10.0f);
			glVertex2f(0.0f,10.0f);
		glEnd();
		glPopMatrix();
	}

	this->GLReturnedError("window::FboToOrtho - Exit");
}

window::~window(void)
{
	delete third;
	delete striker;
	delete top;
	delete reflection;

	delete MainView_fbo;
	delete TopView_fbo;
	delete ReflectionView_fbo;
	delete ReflectionTop_fbo;
}
//Func to display status during the game
void window::DisplayStatus()
{
	if (handle == -1)
		return;
	glLineWidth(2.0f);
	stringstream ss,ss1;
	ss<<"Time Remaining: "<< fixed << showpoint << setprecision(2) <<float(time_remaining)/60.0f;
	status_text.push_back(ss.str());
	
	ss1<<"Targets Remaining: "<< myworld->myobjects->targets_remaining;
	status_text.push_back(ss1.str());
	status_text.push_back("   ");
	vector<string> *s = &status_text;
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
	glTranslated(1500, 15 * s->size(), -5.5);
	glScaled(0.15, 0.15, 1.0);
	for (auto i = s->begin(); i < s->end(); ++i)
	{
		glPushMatrix();
		glutStrokeString(GLUT_STROKE_MONO_ROMAN, (const unsigned char *) (*i).c_str());
		glPopMatrix();
		glTranslated(0, -150, 0);
	}
	status_text.clear();
	glLineWidth(1.0f);
}
//Func to display instructions of gameplay
void window::DisplayInstructions()
{
	if (handle == -1)
		return;
	vector<string> *s = &instructions;
	glLineWidth(2.0f);
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
	glTranslated((width/2) - 400, 100+(height + (15 * s->size()))/2, -5.5);
	glScaled(0.15, 0.15, 1.0);
	for (auto i = s->begin(); i < s->end(); ++i)
	{
		if((game_started) && (s->begin() == i))
		{
			continue;
		}
		glPushMatrix();
		glutStrokeString(GLUT_STROKE_MONO_ROMAN, (const unsigned char *) (*i).c_str());
		glPopMatrix();
		glTranslated(0, -150,0);
	}
	glLineWidth(1.0f);
}

void window::CloseFunc()
{
	handle = -1;
	myworld->TakeDown();

	MainView_fbo->TakeDown();
	TopView_fbo->TakeDown();
	ReflectionView_fbo->TakeDown();
	ReflectionTop_fbo->TakeDown();
}


bool window::GLReturnedError(char * s)
{
	bool return_error = false;
#ifdef _DEBUG
	GLenum glerror;

	while ((glerror = glGetError()) != GL_NO_ERROR)
	{
		return_error = true;
		cerr << s << ": " << gluErrorString(glerror) << endl;
	}
#endif
	return return_error;
}