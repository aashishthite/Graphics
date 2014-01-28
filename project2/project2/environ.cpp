#include "environ.h"
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/*
environ::environ(bool Floor, bool Walls, bool Roof)
{
	floor = Floor;
	walls = Walls;
	roof = Roof;
}

void environ::DrawFloor(void)
{
	if(floor)
	{
		glBegin(GL_QUADS);
		bool color;
		int i;
		int j;
		color = false;
		for(i = -10; i < 10; i++)
		{
			color = !color;
			for(j = -10; j < 10; j++)
			{
				if(color)
				{
					glColor3d(238.0f/255.0f, 232.0f/255.0f, 205.0f/255.0f);
				}
				else
				{
					glColor3d(205.0f/255.0f, 200.0f/255.0f, 177.0f/255.0f);
				}
				glVertex3d(float(i)*0.5f, 0, float(j)*0.5f);
				glVertex3d(float(i)*0.5f, 0, 0.5f + float(j)*0.5f);
				glVertex3d(0.5f + float(i)*0.5f, 0, 0.5f + float(j)*0.5f);
				glVertex3d(0.5f + float(i)*0.5f, 0, float(j)*0.5f);
				color = !color;
			}
		}
		glEnd();
	}
}

void environ::DrawWalls(void)
{
	if(walls)
	{
		glBegin(GL_QUADS);
		
		
		//It is better to get rid of one wall for viewing without moving the camera
		//glColor3d(160.0f/255.0f, 160.0f/255.0f, 160.0f/255.0f);
		//wall at x = -5
		//glVertex3d(-5.0f, 0.0f, -5.0f);
		//glVertex3d(-5.0f, 0.0f, 5.0f);
		//glVertex3d(-5.0f, 10.0f, 5.0f);
		//glVertex3d(-5.0f, 10.0f, -5.0f);

		glColor3d(160.0f/255.0f, 160.0f/255.0f, 160.0f/255.0f);
		//wall at x = 5
		glVertex3d(5.0f, 0.0f, -5.0f);
		glVertex3d(5.0f, 0.0f, 5.0f);
		glVertex3d(5.0f, 6.0f, 5.0f);
		glVertex3d(5.0f, 6.0f, -5.0f);

		glColor3d(130.0f/255.0f, 130.0f/255.0f, 130.0f/255.0f);
		//wall at z = -5
		glVertex3d(-5.0f, 0.0f, -5.0f);
		glVertex3d(5.0f, 0.0f, -5.0f);
		glVertex3d(5.0f, 6.0f, -5.0f);
		glVertex3d(-5.0f, 6.0f, -5.0f);

		glColor3d(130.0f/255.0f, 130.0f/255.0f, 130.0f/255.0f);
		//wall at z = 5
		glVertex3d(-5.0f, 0.0f, 5.0f);
		glVertex3d(5.0f, 0.0f, 5.0f);
		glVertex3d(5.0f, 6.0f, 5.0f);
		glVertex3d(-5.0f, 6.0f, 5.0f);
		glEnd();
	}
}

void environ::DrawRoof(void)
{
	if(roof)
	{
		glBegin(GL_QUADS);
		glColor3d(255.0f/255.0f, 255.0f/255.0f, 255.0f/255.0f);

		glVertex3d(-5.0f, 6.0f, -5.0f);
		glVertex3d(-5.0f, 6.0f, 5.0f);
		glVertex3d(5.0f, 6.0f, 5.0f);
		glVertex3d(5.0f, 6.0f, -5.0f);

		glEnd();
	}
}

void environ::FlipFloor(void)
{
	floor = !floor;
}

void environ::FlipWalls(void)
{
	walls = !walls;
}

void environ::FlipRoof(void)
{
	roof = !roof;
}
*/