#include "camera.h"
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

glm::mat4 copy_modelview;

camera::camera(GLint Distance, GLint Fov, GLint O_lat, GLint O_long, GLint O_spin, GLint P_lat, GLint P_long, GLint Nearplane, GLint Farplane, bool Draw)
{
	distance =  Distance;
	if(distance < -100)
	{
		distance = -100;
	}
	else if(distance > 0)
	{
		distance = 0;
	}
	fov = Fov;
	if(fov < 1)
	{
		fov = 1;
	}
	else if(fov > 89)
	{
		fov = 89;
	}
	orient_lattitude = O_lat;
	if(orient_lattitude > 89)
	{
		orient_lattitude = 89;
	}
	else if(orient_lattitude < -89)
	{
		orient_lattitude = -89;
	}
	orient_longitude = O_long;
	if(orient_longitude > 359)
	{
		orient_longitude = 0;
	}
	else if(orient_longitude < -359)
	{
		orient_longitude = 0;
	}
	orient_spin = O_spin;
	if(orient_spin > 359)
	{
		orient_spin = 0;
	}
	else if(orient_spin < -359)
	{
		orient_spin = 0;
	}
	position_lattitude = P_lat;
	if(position_lattitude > 89)
	{
		position_lattitude = 89;
	}
	else if(position_lattitude < -89)
	{
		position_lattitude = -89;
	}
	position_longitude = P_long;
	if(position_longitude > 359)
	{
		position_longitude = 0;
	}
	else if(position_longitude < -359)
	{
		position_longitude = 0;
	}
	nearplane = Nearplane;
	farplane = Farplane;
	draw = Draw;
}

void camera::SetupCamera(window *parentwin, glm::mat4 & projection, glm::mat4 & modelview)
{	
	//Setup the projection matrix
	projection = glm::perspective(float(fov), float(parentwin->width) / float(parentwin->height), float(nearplane), float(farplane));

	//The order of the following steps is very important:
	//STEP1: setup the orientation of the camera
	glm::mat4 camera_matrix = glm::mat4(1.0f);
	camera_matrix = glm::rotate(camera_matrix, float(orient_spin), glm::vec3(0.0f, 0.0f, 1.0f));
	camera_matrix = glm::rotate(camera_matrix, float(orient_lattitude), glm::vec3(1.0f, 0.0f, 0.0f));
	camera_matrix = glm::rotate(camera_matrix, float(orient_longitude), glm::vec3(0.0f, 1.0f, 0.0f));

	//STEP2: Translate the camera with respect to the world origin
	camera_matrix = glm::translate(camera_matrix, glm::vec3(0.0f, 0.0f, float(distance)));
	
	//STEP3: Locate the camera on the surface of the imaginary sphere defined by radius = 'distance'
	camera_matrix = glm::rotate(camera_matrix, float(position_lattitude), glm::vec3(1.0f, 0.0f, 0.0f));
	camera_matrix = glm::rotate(camera_matrix, float(position_longitude), glm::vec3(0.0f, 1.0f, 0.0f));
	
	copy_modelview=camera_matrix;
	modelview = camera_matrix;
}

void camera::DrawCamera(void)
{
	if(draw)
	{
		/*
		/////////////////////////////////////////////////////////////////////////////////////
		//STEP1: Move to the location of the camera
		glm::mat4 modelview_matrix = glm::mat4(1.0f);
		glm::mat4 backup_matrix = modelview_matrix;

		//Note that the order of transformations are inverted as compared to that of the ones on the projection matrix.
		//NOTE: Imagine that the modelview matrix is always transformed with respect to its origin (and not the world origin)
		
		modelview_matrix = glm::rotate(modelview_matrix, float(position_longitude), glm::vec3(0.0f, -1.0f, 0.0f));
		modelview_matrix = glm::rotate(modelview_matrix, float(position_lattitude), glm::vec3(-1.0f, 0.0f, 0.0f));
		modelview_matrix = glm::translate(modelview_matrix, glm::vec3(0.0f, 0.0f, -float(distance)));
		
		modelview_matrix = glm::rotate(modelview_matrix, float(orient_longitude), glm::vec3(0.0f, -1.0f, 0.0f));
		modelview_matrix = glm::rotate(modelview_matrix, float(orient_lattitude), glm::vec3(-1.0f, 0.0f, 0.0f));
		modelview_matrix = glm::rotate(modelview_matrix, float(orient_spin), glm::vec3(0.0f, 0.0f, -1.0f));

		glLoadMatrixf(glm::value_ptr(modelview_matrix));
		
		/////////////////////////////////////////////////////////////////////////////////////
		//STEP2: Draw the view frustum
		DrawCamera_frustum();
		
		/////////////////////////////////////////////////////////////////////////////////////
		//STEP3: Now draw the camera
		DrawCamera_body(modelview_matrix);

		//Attempt to list out commands on the screen
		//unsigned char a[5] = "abc";
		//glutStrokeString(GLUT_STROKE_ROMAN, a);

		modelview_matrix = backup_matrix;
		glLoadMatrixf(glm::value_ptr(modelview_matrix));
		*/
	}
}

void camera::IncrementDistance(void)
{
	if(0 != distance)
	{
		distance = distance + 1;
	}
}

void camera::DecrementDistance(void)
{
	if(-100 != distance)
	{
		distance = distance - 1;
	}
}

void camera::IncrementFov(void)
{
	if(89 != fov)
	{
		fov = fov + 1;
	}		
}

void camera::DecrementFov(void)
{
	if(1 != fov)
	{
		fov = fov - 1;
	}
}

void camera::Increment_orient_lattitude(void)
{
	if(89 != orient_lattitude)
	{
		orient_lattitude = orient_lattitude + 1;
	}
}

void camera::Decrement_orient_lattitude(void)
{
	if(-89 != orient_lattitude)
	{
		orient_lattitude = orient_lattitude - 1;
	}
}

void camera::Increment_orient_longitude(void)
{
	orient_longitude = orient_longitude + 1;
	if(360 == orient_longitude)
	{
		orient_longitude = 0;
	}
}

void camera::Decrement_orient_longitude(void)
{
	orient_longitude = orient_longitude - 1;
	if(-360 == orient_longitude)
	{
		orient_longitude = 0;
	}
}

void camera::Increment_orient_spin(void)
{
	orient_spin = orient_spin + 1;
	if(360 == orient_spin)
	{
		orient_spin = 0;
	}
}

void camera::Decrement_orient_spin(void)
{
	orient_spin = orient_spin - 1;
	if(-360 == orient_spin)
	{
		orient_spin = 0;
	}
}

void camera::Increment_position_lattitude(void)
{
	if(89 != position_lattitude)
	{
		position_lattitude = position_lattitude + 1;
	}
}

void camera::Decrement_position_lattitude(void)
{
	if(-89 != position_lattitude)
	{
		position_lattitude = position_lattitude - 1;
	}
}

void camera::Increment_position_longitude(void)
{
	position_longitude = position_longitude + 1;
	if(360 == position_longitude)
	{
		position_longitude = 0;
	}
}

void camera::Decrement_position_longitude(void)
{
	position_longitude = position_longitude - 1;
	if(-360 == position_longitude)
	{
		position_longitude = 0;
	}
}

void camera::IncrementNearplane(void)
{
	if(nearplane != farplane - 1)
	{
		nearplane = nearplane + 1;
	}
}

void camera::DecrementNearplane(void)
{
	if(nearplane != 1)
	{
		nearplane = nearplane - 1;
	}
}

void camera::IncrementFarplane(void)
{
	if(farplane != MAX)
	{
		farplane = farplane + 1;
	}
}

void camera::DecrementFarplane(void)
{
	if(farplane != nearplane + 1)
	{
		farplane = farplane - 1;
	}
}

void camera::FlipDraw(void)
{
	draw = !draw;
}

void camera::DrawCamera_frustum(void)
{
	/*
	//tan needs arguments as radians; had a tough time guessing this
	//also fov is the full angle and not the half angle.
	GLfloat farplane_xy = float(farplane) * float(tan(float(fov)*PI/360.0f));
	GLfloat nearplane_xy = float(nearplane) * float(tan(float(fov)*PI/360.0f));
	
	glColor3d(1, 1, 1);

	glBegin(GL_LINES);
	
	//Segments defining inclined sides of frustum
	glVertex3d(0.0f, 0.0f, 0.0f);
	glVertex3d(farplane_xy, farplane_xy, -farplane);

	glVertex3d(0.0f, 0.0f, 0.0f);
	glVertex3d(-farplane_xy, farplane_xy, -farplane);

	glVertex3d(0.0f, 0.0f, 0.0f);
	glVertex3d(-farplane_xy, -farplane_xy, -farplane);

	glVertex3d(0.0f, 0.0f, 0.0f);
	glVertex3d(farplane_xy, -farplane_xy, -farplane);

	//Segments defining far clipping plane
	glVertex3d(farplane_xy, farplane_xy, -farplane);
	glVertex3d(-farplane_xy, farplane_xy, -farplane);

	glVertex3d(-farplane_xy, farplane_xy, -farplane);
	glVertex3d(-farplane_xy, -farplane_xy, -farplane);

	glVertex3d(-farplane_xy, -farplane_xy, -farplane);
	glVertex3d(farplane_xy, -farplane_xy, -farplane);

	glVertex3d(farplane_xy, -farplane_xy, -farplane);
	glVertex3d(farplane_xy, farplane_xy, -farplane);

	//Segments defining near clipping plane
	glVertex3d(nearplane_xy, nearplane_xy, -nearplane);
	glVertex3d(-nearplane_xy, nearplane_xy, -nearplane);

	glVertex3d(-nearplane_xy, nearplane_xy, -nearplane);
	glVertex3d(-nearplane_xy, -nearplane_xy, -nearplane);

	glVertex3d(-nearplane_xy, -nearplane_xy, -nearplane);
	glVertex3d(nearplane_xy, -nearplane_xy, -nearplane);

	glVertex3d(nearplane_xy, -nearplane_xy, -nearplane);
	glVertex3d(nearplane_xy, nearplane_xy, -nearplane);

	glEnd();
	*/
}
void camera::DrawCamera_body(glm::mat4 modelview)
{
	/*
	glm::mat4 modelview_matrix = modelview;
	glLoadMatrixf(glm::value_ptr(modelview_matrix));

	GLUquadric * q = gluNewQuadric();

	//The cone at the lens of the camera
	glColor3d(177.0f/255.0f, 173.0f/255.0f, 150.0f/255.0f);
	modelview_matrix = glm::translate(modelview_matrix, glm::vec3(0.0f, 0.0f, -0.5f));
	glLoadMatrixf(glm::value_ptr(modelview_matrix));
	gluCylinder(q, 0.5, 0.0, 0.5, 30, 1);

	//Camera body: A cylinder and two disks
	glColor3d(197.0f/255.0f, 193.0f/255.0f, 170.0f/255.0f);
	modelview_matrix = modelview;
	glLoadMatrixf(glm::value_ptr(modelview_matrix));
	gluDisk(q, 0.0, 0.5, 30, 1);
	gluCylinder(q, 0.5, 0.5, 1.5, 30, 1);
	modelview_matrix = glm::translate(modelview_matrix, glm::vec3(0.0f, 0.0f, 1.5f));
	glLoadMatrixf(glm::value_ptr(modelview_matrix));
	gluDisk(q, 0.0, 0.5, 30, 1);

	//First ring on top of camera
	glColor3d(177.0f/255.0f, 173.0f/255.0f, 150.0f/255.0f);
	modelview_matrix = modelview;
	modelview_matrix = glm::rotate(modelview_matrix, 90.0f, glm::vec3(0.0f, -1.0f, 0.0f));
	modelview_matrix = glm::translate(modelview_matrix, glm::vec3(0.45f, 0.8f, -0.05f));
	glLoadMatrixf(glm::value_ptr(modelview_matrix));
	gluCylinder(q, 0.3, 0.3, 0.1, 30, 1);
	modelview_matrix = glm::translate(modelview_matrix, glm::vec3(0.0f, 0.0f, 0.1));
	glLoadMatrixf(glm::value_ptr(modelview_matrix));
	gluDisk(q, 0.0, 0.3, 30, 1);
	modelview_matrix = glm::translate(modelview_matrix, glm::vec3(0.0f, 0.0f, -0.1));
	glLoadMatrixf(glm::value_ptr(modelview_matrix));
	gluDisk(q, 0.0, 0.3, 30, 1);

	//Second ring on top of camera
	modelview_matrix = modelview;
	modelview_matrix = glm::rotate(modelview_matrix, 90.0f, glm::vec3(0.0f, -1.0f, 0.0f));
	modelview_matrix = glm::translate(modelview_matrix, glm::vec3(1.05f, 0.8f, -0.05f));
	glLoadMatrixf(glm::value_ptr(modelview_matrix));
	gluCylinder(q, 0.3, 0.3, 0.1, 30, 1);
	modelview_matrix = glm::translate(modelview_matrix, glm::vec3(0.0f, 0.0f, 0.1));
	glLoadMatrixf(glm::value_ptr(modelview_matrix));
	gluDisk(q, 0.0, 0.3, 30, 1);
	modelview_matrix = glm::translate(modelview_matrix, glm::vec3(0.0f, 0.0f, -0.1));
	glLoadMatrixf(glm::value_ptr(modelview_matrix));
	gluDisk(q, 0.0, 0.3, 30, 1);

	gluDeleteQuadric(q);

	modelview_matrix = modelview;
	glLoadMatrixf(glm::value_ptr(modelview_matrix));
	*/
}