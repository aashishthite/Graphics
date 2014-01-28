#version 400

layout (location = 0) in vec3 vertex_position;
layout (location = 3) in vec2 texture_coordinates;
layout (location = 2) in vec3 vertex_normal;

uniform mat4 mvp;
uniform mat4 modelview_matrix;
uniform mat3 normal_matrix;



out vec2 tc;
out vec3 normal;
out vec3 position;
out vec3 raw_vertex_pos;





void main()
{
	tc = texture_coordinates;
	raw_vertex_pos = vertex_position;
	gl_Position = mvp * vec4(vertex_position, 1.0);
	position = vec3(modelview_matrix * vec4(vertex_position,1.0));
	normal = normalize(normal_matrix * vertex_normal);
}
