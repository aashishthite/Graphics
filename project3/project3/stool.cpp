#include "stool.h"

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

using namespace std;

stool::stool()
{
	glm::vec3 color1 = GetColor(1);
	glm::vec3 color2 = GetColor(2);

	ConstructBase();
	ConstructSeat();
}

void stool::ConstructBase(void)
{
	//The cube which is to be stretched and sheared to form the four legs of the stool
	stoolBase.cube_leg = new cube(GetColor(1), false);
	stoolComponents.push_back(stoolBase.cube_leg);

	//Objects for the lower planck
	GLfloat height = 1.6f;
	GLdouble base_radius = 0.6-(height*0.24);
	GLdouble top_radius = 0.6-((height+0.1)*0.24);
	stoolBase.planck1_cylinder_out = new cylinder(GetColor(2), base_radius, top_radius, 0.1, false);	
	stoolBase.planck1_cylinder_in = new cylinder(GetColor(2), 0.07, 0.07, 0.1, true);	
	stoolBase.planck1_disk_top = new disk(GetColor(2), 0.07, top_radius, false);	
	stoolBase.planck1_disk_bottom = new disk(GetColor(2), 0.07, base_radius, true);
	stoolComponents.push_back(stoolBase.planck1_cylinder_out);
	stoolComponents.push_back(stoolBase.planck1_cylinder_in);
	stoolComponents.push_back(stoolBase.planck1_disk_top);
	stoolComponents.push_back(stoolBase.planck1_disk_bottom);

	//Objects for the upper planck
	height = 1.9f;
	base_radius = 0.6-(height*0.24);
	top_radius = 0.6-((height+0.1)*0.24);
	stoolBase.planck2_cylinder_out = new cylinder(GetColor(2), base_radius, top_radius, 0.1, false);
	stoolBase.planck2_cylinder_in = new cylinder(GetColor(2), 0.07, 0.07, 0.1, true);
	stoolBase.planck2_disk_top = new disk(GetColor(2), 0.07, top_radius, false);
	stoolBase.planck2_disk_bottom = new disk(GetColor(2), 0.07, base_radius, true);
	stoolComponents.push_back(stoolBase.planck2_cylinder_out);
	stoolComponents.push_back(stoolBase.planck2_cylinder_in);
	stoolComponents.push_back(stoolBase.planck2_disk_top);
	stoolComponents.push_back(stoolBase.planck2_disk_bottom);

	//Objects for the tube connecting the two plancks
	stoolBase.tube_cylinder_in = new cylinder(GetColor(1), 0.06, 0.06, 0.42, true);
	stoolBase.tube_cylinder_mid = new cylinder(GetColor(1), 0.07, 0.07, 0.4, false);
	stoolBase.tube_cylinder_out = new cylinder(GetColor(1), 0.08, 0.08, 0.02, false);
	stoolBase.tube_disk_low = new disk(GetColor(1), 0.06, 0.07, true);
	stoolBase.tube_disk_mid = new disk(GetColor(1), 0.07, 0.08, true);
	stoolBase.tube_disk_high = new disk(GetColor(1), 0.06, 0.08, false);
	stoolComponents.push_back(stoolBase.tube_cylinder_in);
	stoolComponents.push_back(stoolBase.tube_cylinder_mid);
	stoolComponents.push_back(stoolBase.tube_cylinder_out);
	stoolComponents.push_back(stoolBase.tube_disk_low);
	stoolComponents.push_back(stoolBase.tube_disk_mid);
	stoolComponents.push_back(stoolBase.tube_disk_high);

	//Object for the ring
	stoolBase.base_tuboid = new tuboid(GetColor(2), 0.46, 0.02, false);
	stoolComponents.push_back(stoolBase.base_tuboid);
}

void stool::ConstructSeat(void)
{
	//Objects for the planck
	stoolSeat.planck_cylinder_regular = new cylinder(GetColor(2), 0.5, 0.5, 0.04, false);
	stoolSeat.planck_disk_top = new disk(GetColor(2), 0.0, 0.5, true);
	stoolSeat.planck_cylinder_tapered = new cylinder(GetColor(2), 0.5, 0.25, 0.04, false);
	stoolComponents.push_back(stoolSeat.planck_cylinder_regular);
	stoolComponents.push_back(stoolSeat.planck_disk_top);
	stoolComponents.push_back(stoolSeat.planck_cylinder_tapered);


	//Objects for highlighted planck
	stoolSeat.planck_cylinder_regular_highlight = new cylinder(GetColor(3), 0.5, 0.5, 0.04, false);
	stoolSeat.planck_disk_top_highlight = new disk(GetColor(3), 0.0, 0.5, true);
	stoolSeat.planck_cylinder_tapered_highlight = new cylinder(GetColor(3), 0.5, 0.25, 0.04, false);
	stoolComponents.push_back(stoolSeat.planck_cylinder_regular_highlight);
	stoolComponents.push_back(stoolSeat.planck_disk_top_highlight);
	stoolComponents.push_back(stoolSeat.planck_cylinder_tapered_highlight);

	//Square for selected stools;
	stoolSeat.square_stool_selected = new square(GetColor(1), true);
	stoolComponents.push_back(stoolSeat.square_stool_selected);

	//Objects for the connector
	//Alternate colors for better visibility
	stoolSeat.connector1_cylinder = new cylinder(GetColor(1), 0.25, 0.25, 0.01, false);
	stoolSeat.connector1_disk_top = new disk(GetColor(1), 0.0, 0.25, true);
	stoolSeat.connector1_disk_bottom = new disk(GetColor(1), 0.0, 0.25, false);
	stoolComponents.push_back(stoolSeat.connector1_cylinder);
	stoolComponents.push_back(stoolSeat.connector1_disk_top);
	stoolComponents.push_back(stoolSeat.connector1_disk_bottom);

	stoolSeat.connector2_cylinder_in = new cylinder(GetColor(2), 0.15, 0.1, 0.03, false);
	stoolSeat.connector2_cylinder_out = new cylinder(GetColor(2), 0.07, 0.07, 0.03, true);
	stoolSeat.connector2_disk_top = new disk(GetColor(2), 0.07, 0.15, true);
	stoolSeat.connector2_disk_bottom = new disk(GetColor(2), 0.07, 0.1, false);
	stoolComponents.push_back(stoolSeat.connector2_cylinder_in);
	stoolComponents.push_back(stoolSeat.connector2_cylinder_out);
	stoolComponents.push_back(stoolSeat.connector2_disk_top);
	stoolComponents.push_back(stoolSeat.connector2_disk_bottom);

	//The stem is composed of one thicker cylinders at the connector, followed by a long narrow cylinder forming the stem
	stoolSeat.stem_cylinder_out = new cylinder(GetColor(1), 0.085, 0.085, 0.015, false);
	stoolSeat.stem_cylinder_in = new cylinder(GetColor(2), 0.05, 0.05, 1.2, false);
	stoolSeat.stem_disk_top = new disk(GetColor(1), 0.05, 0.085, false);
	stoolSeat.stem_disk_bottom = new disk(GetColor(2), 0.0, 0.05, false);
	stoolComponents.push_back(stoolSeat.stem_cylinder_out);
	stoolComponents.push_back(stoolSeat.stem_cylinder_in);
	stoolComponents.push_back(stoolSeat.stem_disk_top);
	stoolComponents.push_back(stoolSeat.stem_disk_bottom);

	//Objects for the helix
	stoolSeat.thread_top_helix = new helix(GetColor(2), 0.05, 0.06, 0.05, 23, false, false);
	stoolSeat.thread_bottom_helix = new helix(GetColor(2), 0.05, 0.06, 0.05, 23, true, true);
	stoolComponents.push_back(stoolSeat.thread_top_helix);
	stoolComponents.push_back(stoolSeat.thread_bottom_helix);
}

bool stool::Initialize(int slices)
{
	//Initialize all geometries which are part of the stool
	unsigned int i;
	for(i=0; i<stoolComponents.size(); i++)
	{
		if(!stoolComponents[i]->Initialize(slices))
			return false;
	}
	return true;
}

glm::vec3 stool::GetColor(GLint color)
{
	switch(color)
	{
		case 1: //Theme color 1 - Indigo
			return glm::vec3(76.0f/255.0f, 0.0f/255.0f, 153.0f/255.0f);
			break;
		case 2: //Theme color 2 - Amber
			return glm::vec3(215.0f/255.0f, 172.0f/255.0f, 0.0f/255.0f);
			break;
		case 3: //only for highlighted seats
			return glm::vec3(139.0f/255.0f, 20.0f/255.0f, 150.0f/255.0f);
			break;
		case 4: //Darker shade of 2; for threads, screws
			return glm::vec3(152.0f/255.0f, 122.0f/255.0f, 3.0f/255.0f);
			break;
		case 5: //Lighter shade of 2; for threads, screws
			return glm::vec3(249.0f/255.0f, 229.0f/255.0f, 149.0f/255.0f);
			break;
		default:
			cerr << "stool::GetColor - Illegal color; setting to white" <<endl;
			return glm::vec3(1.0f, 1.0f, 1.0f);
			break;
	}
}

bool stool::Draw(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size, GLfloat pos_x, GLfloat pos_y, GLfloat pos_z, GLfloat rot_y, GLfloat seat_height, bool adjust_height, bool highlight_seat)
{
	if(seat_height < 0)
	{
		seat_height = 0;
	}
	if(seat_height > 199)
	{
		seat_height = 199;
	}

	glm::mat4 local_modelview = modelview;

	//STEP1: Translate to the stool location, Rotate to stool orientation
	local_modelview = glm::translate(local_modelview, glm::vec3(pos_x, pos_y, pos_z));
	local_modelview = glm::rotate(local_modelview, rot_y, glm::vec3(0.0f, 1.0f, 0.0f));

	//STEP2: Draw the stool base
	if(!DrawBase(projection, local_modelview, size))
	{
		std::cerr << "stool::Draw DrawBase failed" << std::endl;
		return false;
	}

	//STEP3: Translate,rotate before drawing seat
	GLfloat effective_seat_height = seat_height/400.0f;
	GLfloat effective_seat_angle = seat_height*3600.0f/400.0f;
	local_modelview = glm::translate(local_modelview, glm::vec3(0.0f, effective_seat_height, 0.0f));
	local_modelview = glm::rotate(local_modelview, effective_seat_angle, glm::vec3(0.0f, 1.0f, 0.0f));

	//STEP4: Draw the stool seat
	if(!DrawSeat(projection, local_modelview, size, adjust_height, highlight_seat))
	{
		std::cerr << "stool::Draw DrawSeat failed" << std::endl;
		return false;
	}
	return true;
}

bool stool::DrawBase(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size)
{
	glm::mat4 local_modelview = modelview;

	////////////////////////////////////////////////////////////////////////////
	//STEP1: Draw the four legs
	//It should be easier to use a function for shear. Writing matrix for four kinds of shear will be difficult
	if(!DrawBase_leg(projection, local_modelview, size))
	{
		std::cerr << "stool::Draw DrawBase_leg failed" << std::endl;
		return false;
	}
	local_modelview = glm::rotate(local_modelview, 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	if(!DrawBase_leg(projection, local_modelview, size))
	{
		std::cerr << "stool::Draw DrawBase_leg failed" << std::endl;
		return false;
	}
	local_modelview = glm::rotate(local_modelview, 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	if(!DrawBase_leg(projection, local_modelview, size))
	{
		std::cerr << "stool::Draw DrawBase_leg failed" << std::endl;
		return false;
	}
	local_modelview = glm::rotate(local_modelview, 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	if(!DrawBase_leg(projection, local_modelview, size))
	{
		std::cerr << "stool::Draw DrawBase_leg failed" << std::endl;
		return false;
	}

	////////////////////////////////////////////////////////////////////////////
	//STEP2: Draw the two planks between the legs
	if(!DrawBase_plancks(projection, local_modelview, size))
	{
		std::cerr << "stool::Draw DrawBase_plancks failed" << std::endl;
		return false;
	}

	////////////////////////////////////////////////////////////////////////////
	//STEP3: Tube connecting the two planks
	if(!DrawBase_tube(projection, local_modelview, size))
	{
		std::cerr << "stool::Draw DrawBase_tube failed" << std::endl;
		return false;
	}
	////////////////////////////////////////////////////////////////////////////
	//STEP4: The ring connecting the legs near the bottom
	if(!DrawBase_ring(projection, local_modelview, size))
	{
		std::cerr << "stool::Draw DrawBase_ring failed" << std::endl;
		return false;
	}

	return true;
}

bool stool::DrawSeat(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size, bool adjust_height, bool highlight_seat)
{
	glm::mat4 local_modelview = modelview;
	
	////////////////////////////////////////////////////////////////////////////
	//STEP1: Translate to the height of the stool base
	// Base hieght + Projection on base + Seat projections
	//To see separation, add 0.02f
	GLfloat default_min_seat_displacement = 2.0f+0.02f+0.135f;
	local_modelview = glm::translate(local_modelview, glm::vec3(0.0f, default_min_seat_displacement, 0.0f));
	local_modelview = glm::rotate(local_modelview, 90.0f, glm::vec3(1.0f, 0.0f, 0.0f));

	////////////////////////////////////////////////////////////////////////////
	//STEP2: Draw the planck which forms the seat
	//For moving the seat, it is good to have a non-circular figure on the seat. Otherwise rotations can't be seen
	/*
	if(adjust_height)
	{
		SetColor(1);
		glBegin(GL_QUADS);
		glVertex3d(-0.25f,-0.25f,-0.0001f);
		glVertex3d(-0.25f,0.25f,-0.0001f);
		glVertex3d(0.25f,0.25f,-0.0001f);
		glVertex3d(0.25f,-0.25f,-0.0001f);
		glEnd();
	}
	if(highlight_seat)
	{
		//takedown seat
		//setup seat with new color
	}
	*/
	
	if(!DrawSeat_planck(projection, local_modelview, size, adjust_height, highlight_seat))
	{
		std::cerr << "stool::Draw DrawSeat_planck failed" << std::endl;
		return false;
	}

	////////////////////////////////////////////////////////////////////////////
	//STEP3: Draw the piece connecting the seat to the stem
	//For parts with more than one color, it is better to set the color within the function for drawing the part
	if(!DrawSeat_connector(projection, local_modelview, size))
	{
		std::cerr << "stool::Draw DrawSeat_connector failed" << std::endl;
		return false;
	}

	////////////////////////////////////////////////////////////////////////////
	//STEP4: Draw the stem
	if(!DrawSeat_stem(projection, local_modelview, size))
	{
		std::cerr << "stool::Draw DrawSeat_stem failed" << std::endl;
		return false;
	}

	////////////////////////////////////////////////////////////////////////////
	//STEP5: Draw the thread on the stem
	if(!DrawSeat_thread(projection, local_modelview, size))
	{
		std::cerr << "stool::Draw DrawSeat_thread failed" << std::endl;
		return false;
	}

	return true;
}

bool stool::DrawBase_leg(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size)
{
	glm::mat4 local_modelview = modelview;

	float sm[16] = {1.0f, 0.0f, 0.0f, 0.0f, -6.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
	glm::mat4 shear_matrix = glm::make_mat4(sm);

	local_modelview = glm::translate(local_modelview, glm::vec3(0.4f, 1.0f, 0.0f));
	local_modelview = glm::scale(local_modelview, glm::vec3(0.08, 2.0f, 0.08f));
	local_modelview = local_modelview * shear_matrix;

	if(!stoolBase.cube_leg->Draw(projection, local_modelview, size))
	{
		std::cerr << "stool::Draw stoolBase.cube_leg failed" << std::endl;
		return false;
	}

	return true;
}

bool stool::DrawBase_plancks(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size)
{
	glm::mat4 local_modelview = modelview;

	GLfloat height = 1.6f;
	local_modelview = glm::rotate(local_modelview, -90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	local_modelview = glm::translate(local_modelview, glm::vec3(0.0f, 0.0f, height));
	
	if(!stoolBase.planck1_cylinder_out->Draw(projection, local_modelview, size))
	{
		std::cerr << "stool::Draw stoolBase.planck1_cylinder_out failed" << std::endl;
		return false;
	}
	if(!stoolBase.planck1_cylinder_in->Draw(projection, local_modelview, size))
	{
		std::cerr << "stool::Draw stoolBase.planck1_cylinder_in failed" << std::endl;
		return false;
	}
	if(!stoolBase.planck1_disk_bottom->Draw(projection, local_modelview, size))
	{
		std::cerr << "stool::Draw stoolBase.planck1_disk_bottom failed" << std::endl;
		return false;
	}

	local_modelview = glm::translate(local_modelview, glm::vec3(0.0f, 0.0f, 0.1f));
	if(!stoolBase.planck1_disk_top->Draw(projection, local_modelview, size))
	{
		std::cerr << "stool::Draw stoolBase.planck1_disk_top failed" << std::endl;
		return false;
	}

	local_modelview = modelview;

	height = 1.9f;
	local_modelview = glm::rotate(local_modelview, -90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	local_modelview = glm::translate(local_modelview, glm::vec3(0.0f, 0.0f, height));
	
	if(!stoolBase.planck2_cylinder_out->Draw(projection, local_modelview, size))
	{
		std::cerr << "stool::Draw stoolBase.planck2_cylinder_out failed" << std::endl;
		return false;
	}
	if(!stoolBase.planck2_cylinder_in->Draw(projection, local_modelview, size))
	{
		std::cerr << "stool::Draw stoolBase.planck2_cylinder_in failed" << std::endl;
		return false;
	}
	if(!stoolBase.planck2_disk_bottom->Draw(projection, local_modelview, size))
	{
		std::cerr << "stool::Draw stoolBase.planck2_disk_bottom failed" << std::endl;
		return false;
	}

	local_modelview = glm::translate(local_modelview, glm::vec3(0.0f, 0.0f, 0.1f));
	if(!stoolBase.planck2_disk_top->Draw(projection, local_modelview, size))
	{
		std::cerr << "stool::Draw stoolBase.planck2_disk_top failed" << std::endl;
		return false;
	}

	return true;
}

bool stool::DrawBase_tube(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size)
{
	glm::mat4 local_modelview = modelview;
	
	local_modelview = glm::rotate(local_modelview, -90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	
	local_modelview = glm::translate(local_modelview, glm::vec3(0.0f, 0.0f, 1.6f));
	if(!stoolBase.tube_cylinder_in->Draw(projection, local_modelview, size))
	{
		std::cerr << "stool::Draw stoolBase.tube_cylinder_in failed" << std::endl;
		return false;
	}
	if(!stoolBase.tube_cylinder_mid->Draw(projection, local_modelview, size))
	{
		std::cerr << "stool::Draw stoolBase.tube_cylinder_mid failed" << std::endl;
		return false;
	}
	if(!stoolBase.tube_disk_low->Draw(projection, local_modelview, size))
	{
		std::cerr << "stool::Draw stoolBase.tube_disk_low failed" << std::endl;
		return false;
	}

	local_modelview = glm::translate(local_modelview, glm::vec3(0.0f, 0.0f, 0.40f));
	if(!stoolBase.tube_cylinder_out->Draw(projection, local_modelview, size))
	{
		std::cerr << "stool::Draw stoolBase.tube_cylinder_out failed" << std::endl;
		return false;
	}
	if(!stoolBase.tube_disk_mid->Draw(projection, local_modelview, size))
	{
		std::cerr << "stool::Draw stoolBase.tube_disk_mid failed" << std::endl;
		return false;
	}

	local_modelview = glm::translate(local_modelview, glm::vec3(0.0f, 0.0f, 0.02f));
	if(!stoolBase.tube_disk_high->Draw(projection, local_modelview, size))
	{
		std::cerr << "stool::Draw stoolBase.tube_disk_high failed" << std::endl;
		return false;
	}

	return true;
}

bool stool::DrawBase_ring(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size)
{
	glm::mat4 local_modelview = modelview;
	local_modelview = glm::translate(local_modelview, glm::vec3(0.0f, 0.5f, 0.0f));
	if(!stoolBase.base_tuboid->Draw(projection, local_modelview, size))
	{
		std::cerr << "stool::Draw stoolBase.base_tuboid failed" << std::endl;
		return false;
	}
	return true;
}

bool stool::DrawSeat_planck(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size, bool adjust_height, bool highlight_seat)
{
	cylinder* regular;
	cylinder* tapered;
	disk* top;

	if(highlight_seat)
	{
		regular = this->stoolSeat.planck_cylinder_regular_highlight;
		tapered = this->stoolSeat.planck_cylinder_tapered_highlight;
		top = this->stoolSeat.planck_disk_top_highlight;
	}
	else
	{
		regular = this->stoolSeat.planck_cylinder_regular;
		tapered = this->stoolSeat.planck_cylinder_tapered;
		top = this->stoolSeat.planck_disk_top;
	}

	//The planck is composed of a regular cylinder on the top, followed by a tapered cylinder beneath
	glm::mat4 local_modelview = modelview;
	if(!regular->Draw(projection, local_modelview, size))
	{
		std::cerr << "stool::Draw regular failed" << std::endl;
		return false;
	}
	if(!top->Draw(projection, local_modelview, size))
	{
		std::cerr << "stool::Draw top failed" << std::endl;
		return false;
	}

	local_modelview = glm::translate(local_modelview, glm::vec3(0.0f, 0.0f, 0.04f));
	if(!tapered->Draw(projection, local_modelview, size))
	{
		std::cerr << "stool::Draw tapered failed" << std::endl;
		return false;
	}

	if(adjust_height)
	{
		local_modelview = glm::translate(local_modelview, glm::vec3(0.0f, 0.0f, -0.0401f));
		local_modelview = glm::scale(local_modelview, glm::vec3(0.5, 0.5f, 0.5f));
		//local_modelview = glm::rotate(local_modelview, 180.0f, glm::vec3(0.0f, 0.0f, 0.0f));
		if(!this->stoolSeat.square_stool_selected->Draw(projection, local_modelview, size))
		{
			std::cerr << "stool::Draw stoolSeat.square_stool_selected failed" << std::endl;
			return false;
		}
	}

	return true;
}

bool stool::DrawSeat_connector(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size)
{
	//The connector between the seat and the stem is composed of various pieces.
	glm::mat4 local_modelview = modelview;
	
	local_modelview = glm::translate(local_modelview, glm::vec3(0.0f, 0.0f, 0.08f));
	if(!stoolSeat.connector1_cylinder->Draw(projection, local_modelview, size))
	{
			std::cerr << "stool::Draw stoolSeat.connector1_cylinder failed" << std::endl;
			return false;
	}
	if(!stoolSeat.connector1_disk_top->Draw(projection, local_modelview, size))
	{
			std::cerr << "stool::Draw stoolSeat.connector1_disk_top failed" << std::endl;
			return false;
	}

	local_modelview = glm::translate(local_modelview, glm::vec3(0.0f, 0.0f, 0.01f));
	if(!stoolSeat.connector1_disk_bottom->Draw(projection, local_modelview, size))
	{
			std::cerr << "stool::Draw stoolSeat.connector1_disk_bottom failed" << std::endl;
			return false;
	}

	if(!stoolSeat.connector2_cylinder_in->Draw(projection, local_modelview, size))
	{
			std::cerr << "stool::Draw stoolSeat.connector2_cylinder_in failed" << std::endl;
			return false;
	}
	if(!stoolSeat.connector2_cylinder_out->Draw(projection, local_modelview, size))
	{
			std::cerr << "stool::Draw stoolSeat.connector2_cylinder_out failed" << std::endl;
			return false;
	}
	if(!stoolSeat.connector2_disk_top->Draw(projection, local_modelview, size))
	{
			std::cerr << "stool::Draw stoolSeat.connector2_disk_top failed" << std::endl;
			return false;
	}

	local_modelview = glm::translate(local_modelview, glm::vec3(0.0f, 0.0f, 0.03f));
	if(!stoolSeat.connector2_disk_bottom->Draw(projection, local_modelview, size))
	{
			std::cerr << "stool::Draw stoolSeat.connector2_disk_bottom failed" << std::endl;
			return false;
	}

	return true;
}

bool stool::DrawSeat_stem(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size)
{
	//The stem is composed of one thicker cylinders at the connector, followed by a long narrow cylinder forming the stem
	glm::mat4 local_modelview = modelview;

	local_modelview = glm::translate(local_modelview, glm::vec3(0.0f, 0.0f, 0.12f));
	if(!stoolSeat.stem_cylinder_out->Draw(projection, local_modelview, size))
	{
			std::cerr << "stool::Draw stoolSeat.stem_cylinder_out failed" << std::endl;
			return false;
	}

	local_modelview = glm::translate(local_modelview, glm::vec3(0.0f, 0.0f, 0.015f));
	if(!stoolSeat.stem_cylinder_in->Draw(projection, local_modelview, size))
	{
			std::cerr << "stool::Draw stoolSeat.stem_cylinder_in failed" << std::endl;
			return false;
	}
	if(!stoolSeat.stem_disk_top->Draw(projection, local_modelview, size))
	{
			std::cerr << "stool::Draw stoolSeat.stem_disk_top failed" << std::endl;
			return false;
	}

	local_modelview = glm::translate(local_modelview, glm::vec3(0.0f, 0.0f, 1.2f));
	if(!stoolSeat.stem_disk_bottom->Draw(projection, local_modelview, size))
	{
			std::cerr << "stool::Draw stoolSeat.stem_disk_bottom failed" << std::endl;
			return false;
	}

	return true;
}

bool stool::DrawSeat_thread(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size)
{
	glm::mat4 local_modelview = modelview;
	local_modelview = glm::translate(local_modelview, glm::vec3(0.0f, 0.0f, 0.2f));
	if(!stoolSeat.thread_top_helix->Draw(projection, local_modelview, size))
	{
			std::cerr << "stool::Draw stoolSeat.thread_top_helix failed" << std::endl;
			return false;
	}
	if(!stoolSeat.thread_bottom_helix->Draw(projection, local_modelview, size))
	{
			std::cerr << "stool::Draw stoolSeat.thread_bottom_helix failed" << std::endl;
			return false;
	}
	
/*
	//The thread is composed of quadrilaterals defined by three spirals
	// (outer_point) One spiral has a radius larger than the stem
	// The other two  spirals have exactly the same radius as the stem, but are displaced in either direction along the axis of the stem with respect to the outer spiral
	// the lower face of the thread is colored with a lighter color and the upper face with a darker shade to give the illusion of lighting
	glm::mat4 modelview_matrix = modelview;
	glLoadMatrixf(glm::value_ptr(modelview_matrix));

	glm::mat4 thread_matrix_in1;
	glm::mat4 thread_matrix_in2;
	glm::mat4 thread_matrix_out;
	GLfloat effective_point_height;
	GLfloat effective_point_angle;
	glm::vec4 outer_point;
	glm::vec4 inner1_point;
	glm::vec4 inner2_point;
	glm::vec4 last_outer_point;
	glm::vec4 last_inner1_point;
	glm::vec4 last_inner2_point;
	int i;

	for(i=0; i<450; i++)
	{
		effective_point_height = float(i)/400.0f;
		effective_point_angle = float(i)*3600.0f/200.0f;
		//Matrices defining the three spirals
		thread_matrix_in1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.15f+effective_point_height-0.02f));
		thread_matrix_in2 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.15f+effective_point_height+0.02f));
		thread_matrix_out = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.15f+effective_point_height));
		thread_matrix_in1 = glm::rotate(thread_matrix_in1, effective_point_angle, glm::vec3(0.0f, 0.0f, 1.0f));
		thread_matrix_in2 = glm::rotate(thread_matrix_in2, effective_point_angle, glm::vec3(0.0f, 0.0f, 1.0f));
		thread_matrix_out = glm::rotate(thread_matrix_out, effective_point_angle, glm::vec3(0.0f, 0.0f, 1.0f));
		thread_matrix_in1 = glm::translate(thread_matrix_in1, glm::vec3(0.0f, 0.05f, 0.0f));
		thread_matrix_in2 = glm::translate(thread_matrix_in2, glm::vec3(0.0f, 0.05f, 0.0f));
		thread_matrix_out = glm::translate(thread_matrix_out, glm::vec3(0.0f, 0.06f, 0.0f));

		inner2_point = thread_matrix_in2 * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
		inner1_point = thread_matrix_in1 * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
		outer_point = thread_matrix_out * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
		if(i != 0)
		{
			//Quad1: Defines the upper surface of the thread
			glBegin(GL_QUADS);
			SetColor(4);
			glVertex3d(last_inner1_point.x, last_inner1_point.y, last_inner1_point.z);
			glVertex3d(last_outer_point.x, last_outer_point.y, last_outer_point.z);
			glVertex3d(outer_point.x, outer_point.y, outer_point.z);
			glVertex3d(inner1_point.x, inner1_point.y, inner1_point.z);
			//Quad2 :Defines the lower surface of the thread
			SetColor(5);
			glVertex3d(last_inner2_point.x, last_inner2_point.y, last_inner2_point.z);
			glVertex3d(last_outer_point.x, last_outer_point.y, last_outer_point.z);
			glVertex3d(outer_point.x, outer_point.y, outer_point.z);
			glVertex3d(inner2_point.x, inner2_point.y, inner2_point.z);
			glEnd();
		}
		//the two ends of the threads have a triangular opening, close them out using triangles
		if((i == 0) || (i == 449))
		{
			SetColor(4);
			glBegin(GL_TRIANGLES);
			glVertex3d(inner1_point.x, inner1_point.y, inner1_point.z);
			glVertex3d(outer_point.x, outer_point.y, outer_point.z);
			glVertex3d(inner2_point.x, inner2_point.y, inner2_point.z);
			glEnd();
		}
		//Store of the points so that they are available for the trailing points when defining the next quadrilateral
		last_inner1_point = inner1_point;
		last_inner2_point = inner2_point;
		last_outer_point = outer_point;
	}
	
	modelview_matrix = modelview;
	glLoadMatrixf(glm::value_ptr(modelview_matrix));
*/
	return true;
}


void stool::TakeDown()
{
	//Takedown each object
	unsigned int i;
	for(i=0; i<stoolComponents.size(); i++)
	{
		stoolComponents[i]->TakeDown();
	}
	/*
	top1->TakeDown();
	square1->TakeDown();
	cube1->TakeDown();
	disk1->TakeDown();
	cylinder1->TakeDown();
	*/
}

void stool::FlipNormals(void)
{
	//flip normals for each object
	unsigned int i;
	for(i=0; i<stoolComponents.size(); i++)
	{
		stoolComponents[i]->FlipNormals();
	}
	/*
	top1->FlipNormals();
	square1->FlipNormals();
	cube1->FlipNormals();
	disk1->FlipNormals();
	cylinder1->FlipNormals();
	*/
}

stool::~stool()
{
	//Delete all objects
	unsigned int i;
	for(i=0; i<stoolComponents.size(); i++)
	{
		delete stoolComponents[i];
	}
	/*
	delete top1;
	delete square1;
	delete cube1;
	delete disk1;
	delete cylinder1;
	*/
}

void stool::switch_shader(void)
{
	unsigned int i;
	for(i=0; i<stoolComponents.size(); i++)
	{
		stoolComponents[i]->switch_shader();
	}
}

//////////////////////////////////
//functions for stool_param
stool_params::stool_params(const GLfloat & Posx, const GLfloat & Posy, const GLfloat & Posz, const GLfloat & Roty, const GLfloat & SeatHt)
{
	this->pos_x = Posx;
	this->pos_y = Posy;
	this->pos_z = Posz;
	this->rot_y = Roty;
	this->seat_height = SeatHt;
	this->highlight_seat = false;
	this->adjust_height = false;
}

stool_params::stool_params(const stool_params & other)
{
	this->pos_x = other.pos_x;
	this->pos_y = other.pos_y;
	this->pos_z = other.pos_z;
	this->rot_y = other.rot_y;
	this->seat_height = other.seat_height;
	this->highlight_seat = other.highlight_seat;
	this->adjust_height = other.adjust_height;
}
void stool_params::Increase_stool_height(void)
{
	if((adjust_height) && (seat_height != 199))
	{
		seat_height = seat_height + 1;
	}
}

void stool_params::Decrease_stool_height(void)
{
	if((adjust_height) && (seat_height != 0))
	{
		seat_height = seat_height - 1;
	}
}

void stool_params::toggle_highlight(void)
{
	highlight_seat = !highlight_seat;
}

void stool_params::toggle_active_stool(void)
{
	adjust_height = !adjust_height;
}