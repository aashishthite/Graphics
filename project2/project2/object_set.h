#pragma once
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "stool.h"
#include "tree.h"
#include "textured_square.h"
#include "textured_disk.h"
#include "textured_cuboid.h"

class object_set
{
	private:
		std::vector<stool_params> stool_properties;
		std::vector<tree_params> tree_properties;
		stool* stool_model;
		tree* tree_model;
		int curr_stool; 
		textured_disk* ground;
		textured_cuboid* building;

public:
		void Draw(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size);
		object_set();

		void change_active_stool(void);
		void toggle_active_stool(void);

		void Decrease_stool_heights(void);
		void Increase_stool_heights(void);

		bool Initialize(int slices);
		void TakeDown(void);
		void FlipNormals(void);
		~object_set();
		void switch_shader(void);
};