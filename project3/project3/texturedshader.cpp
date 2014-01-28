/*	Perry Kivolowitz - University of Wisconsin - Madison 
	Computer Sciences Department

	A sample hello world like program demonstrating modern
	OpenGL techniques. 

	Created:	2/25/13
	Updates:
*/

#include "texturedshader.h"

/*	BAD DESIGN WARNING...
	This code has not been properly planned and was tossed in right before lecture.
	The useful concepts are that a texture has to be bound to a texture unit (which
	has been hard coded to zero as the shaders making use of this texture will expect
	the sampler2D to be on zero.
*/

TexturedShader::TexturedShader() : super()
{
	this->texture_handle = GLuint(-1);
	this->texture_wcrop_handle = GLuint(-1);
	this->texture_hcrop_handle = GLuint(-1);
	this->special_mode_handle = GLuint(-1);
	this->striker_coord_handle = GLuint(-1);
	this->special_mode = 0;
}

bool TexturedShader::Initialize(char * vertex_shader_file, char * fragment_shader_file)
{
	if (super::Initialize(vertex_shader_file, fragment_shader_file) == false)
		return false;

	this->Use();
	this->texture_handle = glGetUniformLocation(this->program_id, (const GLchar *) "picture");
	this->texture_wcrop_handle = glGetUniformLocation(this->program_id, (const GLchar *) "wcrop");
	this->texture_hcrop_handle = glGetUniformLocation(this->program_id, (const GLchar *) "hcrop");
	this->special_mode_handle = glGetUniformLocation(this->program_id, (const GLchar *) "special_mode");
	this->striker_coord_handle = glGetUniformLocation(this->program_id, (const GLchar *) "striker_coord");
	glUseProgram(0);
	return true;
}

void TexturedShader::CustomSetup(const GLfloat Wcrop, const GLfloat Hcrop, const glm::vec2 striker_coord)
{
	glUniform1i(this->texture_handle, 0);
	glUniform1f(this->texture_wcrop_handle, Wcrop);
	glUniform1f(this->texture_hcrop_handle, Hcrop);
	glUniform2f(this->striker_coord_handle, striker_coord.x, striker_coord.y);
	glUniform1i(this->special_mode_handle, this->special_mode);
}

void TexturedShader::switch_special_mode(void)
{
	this->special_mode += 1;
	if(this->special_mode == 8)
	{
		this->special_mode = 0;
	}
}
