#pragma once
#include "shader.h"


class TexturedShader : public Shader
{
public:
	TexturedShader();
	virtual bool Initialize(char * vertex_shader_file, char * fragment_shader_file);
	virtual void CustomSetup(const GLfloat Wcrop, const GLfloat Hcrop, const glm::vec2 striker_coord);
	void switch_special_mode(void);
private:
	typedef Shader super;
	GLuint texture_handle;
	GLuint texture_wcrop_handle;
	GLuint texture_hcrop_handle;
	GLuint special_mode_handle;
	GLuint striker_coord_handle;
	GLint special_mode;
};
