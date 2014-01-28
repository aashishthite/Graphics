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
#include "fmod.h"
#include "fmod_errors.h"
#include "world.h"
#include "window.h"

using namespace std;
using namespace glm;

FSOUND_SAMPLE* BackgroundStream = NULL;
FSOUND_SAMPLE* OvationStream = NULL;
int channel;
bool stream_var = false;


bool LoadMusic()
{
	BackgroundStream = FSOUND_Sample_Load( FSOUND_FREE, "Alexander Blu.mp3" , FSOUND_2D , 0 , 0 );/////////////http://www.last.fm/music/+free-music-downloads/background
	OvationStream = FSOUND_Sample_Load( FSOUND_FREE, "Ovation.mp3" , FSOUND_2D , 0 , 0 );////////////////http://soundbible.com/free-sound-effects-12.html
	// make sure mp3 opened OK
	if(!BackgroundStream | ! OvationStream)
	{
		std::cerr << "[ERROR] could not open music file\n";
		return false;
	}
	return true;
}


void MusicSwitch()
{
	 //attempt to open the mp3 file as a stream
	stream_var=!stream_var;
	if(stream_var)
	{
		channel = FSOUND_PlaySound(FSOUND_FREE,BackgroundStream);
		FSOUND_SetLoopMode(channel,FSOUND_LOOP_NORMAL);
		
	}
	else
	{
		channel = FSOUND_PlaySound(FSOUND_FREE,OvationStream);
		FSOUND_SetLoopMode(channel,FSOUND_LOOP_OFF);
	}
	
	FSOUND_SetPaused(channel, true);
	FSOUND_SetVolume(channel, 50);
	FSOUND_SetPaused(channel, false);	
}
int main(int argc, char * argv[])
{

	int num=10;
	if(argc==1 || argc>3)
	{
		cout<<"Enter correct input arguments. Setting ball number to a default value"<<endl;
		num=10;
	}
	if(argc==2)
	{
		//cout<<*argv<< " number of balls initialized"<< endl;
		num=atoi(argv[1]);
		
	}
	if(argc==3)
	{
		//cout<<*argv<< " number of balls initialized"<< endl;
		num=atoi(argv[1]);
		srand(abs(atoi(argv[2])));
	}

	glutInit(&argc , argv);
	
	world* myworld = new world(num);
	
	//Argument list of window constructor:
	//X coordinate of window; not guaranteed
	//Y coordinate of window; not guaranteed
	//Pointer to world
	//window name
	window* simpleview = new window(25, 100, myworld, "On the Moon");
		
	if (glewInit() != GLEW_OK)
	{
		cerr << "GLEW failed to initialize." << endl;
		return 0;
	}

	if(!simpleview->Initialize())
	{
			cerr << "main: Initialization of window has failed" << endl;
			return 1;
	}
	if( FSOUND_Init(44000,64,0) == FALSE )
	{
		std::cerr << "[ERROR] Could not initialise fmod\n";
	}

	if(!LoadMusic())
	{
		std::cerr << "[ERROR] Could not load music\n";
	}
	MusicSwitch();

	if(!myworld->Initialize())
	{
			cerr << "main: Initialization of world has failed" << endl;
			return 1;
	}

	glutMainLoop();
	FSOUND_StopSound(channel);
	if(myworld->myobjects->game_won)
	{
		MusicSwitch();
		cout<<"Won!"<<endl;
		cout<<"With "<< fixed << showpoint << setprecision(2) <<simpleview->time_remaining/60.0f<<" seconds remaining."<<endl;
	}
	delete myworld;
	delete simpleview;
	cout<<"Press any key to exit"<<endl;
	cin.get();
	FSOUND_StopSound(channel);
	return 0;
}
