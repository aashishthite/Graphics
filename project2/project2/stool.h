#pragma once
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "object.h"
#include "shader.h"
#include "square.h"
#include "cube.h"
#include "disk.h"
#include "cylinder.h"
#include "tuboid.h"
#include "helix.h"

class lattice;

class stool_params
{
	public:
		GLfloat pos_x;
		GLfloat pos_y;
		GLfloat pos_z;
		GLfloat rot_y;
		GLfloat seat_height; //In multiples of .0025 foot (over the minimum height)
		stool_params(const GLfloat & Posx, const GLfloat & Posy, const GLfloat & Posz, const GLfloat & Roty, const GLfloat & SeatHt);
		stool_params(const stool_params & other);
		bool highlight_seat;
		bool adjust_height;
		void Increase_stool_height(void);
		void Decrease_stool_height(void);
		void toggle_highlight(void);
		void toggle_active_stool(void);
};

struct stool_base
{
	cube* cube_leg;

	cylinder* planck1_cylinder_out;
	cylinder* planck1_cylinder_in;
	disk* planck1_disk_top;
	disk* planck1_disk_bottom;

	cylinder* planck2_cylinder_out;
	cylinder* planck2_cylinder_in;
	disk* planck2_disk_top;
	disk* planck2_disk_bottom;

	cylinder* tube_cylinder_in;
	cylinder* tube_cylinder_mid;
	cylinder* tube_cylinder_out;
	disk* tube_disk_low;
	disk* tube_disk_mid;
	disk* tube_disk_high;

	tuboid* base_tuboid;
};

struct stool_seat
{
	cylinder* planck_cylinder_regular;
	cylinder* planck_cylinder_tapered;
	disk* planck_disk_top;

	cylinder* planck_cylinder_regular_highlight;
	cylinder* planck_cylinder_tapered_highlight;
	disk* planck_disk_top_highlight;

	square* square_stool_selected;

	cylinder* connector1_cylinder;
	disk* connector1_disk_top;
	disk* connector1_disk_bottom;
	cylinder* connector2_cylinder_in;
	cylinder* connector2_cylinder_out;
	disk* connector2_disk_top;
	disk* connector2_disk_bottom;

	cylinder* stem_cylinder_out;
	cylinder* stem_cylinder_in;
	disk* stem_disk_top;
	disk* stem_disk_bottom;

	helix* thread_top_helix;
	helix* thread_bottom_helix;
};

class stool
{
	private:
		glm::vec3 GetColor(GLint color);

		stool_base stoolBase;
		stool_seat stoolSeat;

		std::vector<lattice*> stoolComponents;

		void ConstructBase(void);
		void ConstructSeat(void);

		void DrawBase(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size);
		void DrawBase_leg(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size);
		void DrawBase_plancks(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size);
		void DrawBase_tube(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size);
		void DrawBase_ring(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size);

		void DrawSeat(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size, bool adjust_height, bool highlight_seat);
		void DrawSeat_planck(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size, bool adjust_height, bool highlight_seat);
		void DrawSeat_connector(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size);
		void DrawSeat_stem(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size);
		void DrawSeat_thread(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size);

public:
		void stool::Draw(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size, GLfloat pos_x, GLfloat pos_y, GLfloat pos_z, GLfloat rot_y, GLfloat seat_height, bool adjust_height, bool highlight_seat);
		stool();

		void FlipNormals(void);
		bool Initialize(int slices);
		void TakeDown(void);
		~stool();
		void switch_shader(void);
};