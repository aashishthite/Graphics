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
void cube::Draw(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size)
{
	glm::mat4 local_modelview = modelview;
	glm::mat4 modelview_backup = local_modelview;
	
	local_modelview = glm::translate(local_modelview, glm::vec3(0.0f, 0.0f, 0.5f));
	Super_lattice::Draw(projection,local_modelview,size);
	local_modelview = glm::rotate(local_modelview, 180.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	local_modelview = glm::translate(local_modelview, glm::vec3(0.0f, 0.0f, 1.0f));
	Super_lattice::Draw(projection,local_modelview,size);

	local_modelview = modelview_backup;
	local_modelview = glm::rotate(local_modelview, 90.0f, glm::vec3(1.0f, 0.0f, 0.0f));

	local_modelview = glm::translate(local_modelview, glm::vec3(0.0f, 0.0f, 0.5f));
	Super_lattice::Draw(projection,local_modelview,size);
	local_modelview = glm::rotate(local_modelview, 180.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	local_modelview = glm::translate(local_modelview, glm::vec3(0.0f, 0.0f, 1.0f));
	Super_lattice::Draw(projection,local_modelview,size);

	local_modelview = modelview_backup;
	local_modelview = glm::rotate(local_modelview, 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

	local_modelview = glm::translate(local_modelview, glm::vec3(0.0f, 0.0f, 0.5f));
	Super_lattice::Draw(projection,local_modelview,size);
	local_modelview = glm::rotate(local_modelview, 180.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	local_modelview = glm::translate(local_modelview, glm::vec3(0.0f, 0.0f, 1.0f));
	Super_lattice::Draw(projection,local_modelview,size);
}