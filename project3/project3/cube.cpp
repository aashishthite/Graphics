#include "cube.h"

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "vertexattributes.h"

cube::cube(glm::vec3 clr, bool flipSurface) : square()
{
	color = clr;
	flip_surface = flipSurface;
}
bool cube::Draw(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size)
{
	glm::mat4 local_modelview = modelview;
	glm::mat4 modelview_backup = local_modelview;
	
	local_modelview = glm::translate(local_modelview, glm::vec3(0.0f, 0.0f, 0.5f));
	if(!Super_lattice::Draw(projection,local_modelview,size))
	{
		std::cerr << "cube::Draw face1 failed" << std::endl;
		return false;
	}
	local_modelview = glm::rotate(local_modelview, 180.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	local_modelview = glm::translate(local_modelview, glm::vec3(0.0f, 0.0f, 1.0f));
	if(!Super_lattice::Draw(projection,local_modelview,size))
	{
		std::cerr << "cube::Draw face2 failed" << std::endl;
		return false;
	}

	local_modelview = modelview_backup;
	local_modelview = glm::rotate(local_modelview, 90.0f, glm::vec3(1.0f, 0.0f, 0.0f));

	local_modelview = glm::translate(local_modelview, glm::vec3(0.0f, 0.0f, 0.5f));
	if(!Super_lattice::Draw(projection,local_modelview,size))
	{
		std::cerr << "cube::Draw face3 failed" << std::endl;
		return false;
	}
	local_modelview = glm::rotate(local_modelview, 180.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	local_modelview = glm::translate(local_modelview, glm::vec3(0.0f, 0.0f, 1.0f));
	if(!Super_lattice::Draw(projection,local_modelview,size))
	{
		std::cerr << "cube::Draw face4 failed" << std::endl;
		return false;
	}

	local_modelview = modelview_backup;
	local_modelview = glm::rotate(local_modelview, 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

	local_modelview = glm::translate(local_modelview, glm::vec3(0.0f, 0.0f, 0.5f));
	if(!Super_lattice::Draw(projection,local_modelview,size))
	{
		std::cerr << "cube::Draw face5 failed" << std::endl;
		return false;
	}
	local_modelview = glm::rotate(local_modelview, 180.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	local_modelview = glm::translate(local_modelview, glm::vec3(0.0f, 0.0f, 1.0f));
	if(!Super_lattice::Draw(projection,local_modelview,size))
	{
		std::cerr << "cube::Draw face6 failed" << std::endl;
		return false;
	}

	return true;
}