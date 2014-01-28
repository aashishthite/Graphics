#version 400

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 vertex_color;

uniform mat3 normal_matrix;
uniform mat4 mvp;
out vec3 color;

mat3 mvp_3 = mat3(mvp);
void main()
{
	gl_Position = mvp * vec4(vertex_position, 1.0);
	color = vertex_color;
}
