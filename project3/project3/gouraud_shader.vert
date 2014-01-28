#version 400

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 vertex_color;
layout (location = 2) in vec3 vertex_normal;


uniform mat4 mvp;
uniform mat4 modelview_matrix;
uniform mat3 normal_matrix;
uniform int light_id;
uniform mat4 camera_matrix;

out vec3 color;

vec3 normal;
vec3 position;


const float shininess = 20.0f;
//const vec3 light_position = vec3(0.0, 0.0, 0.0);

struct LightInfo{
	vec4 light_position;
};

LightInfo lights[4];

vec3 ads(int light_index)
{
  vec3 n = normal;

  //if (!gl_FrontFacing) //loooks like this cant be used in vertext shader
	//n = -n;
vec3 l=vec3(lights[light_index].light_position.x,lights[light_index].light_position.y,lights[light_index].light_position.z);
  vec3 s = normalize(l - position);
  vec3 v = normalize(-position);
  vec3 r = normalize(reflect(-s, n));
  float s_dot_n = max(dot(s, n), 0.0);
  

  
  return vertex_color * s_dot_n + (s_dot_n > 0 ? vertex_color * pow(max(dot(r, v), 0.0), shininess) : vec3(0.0));

}


void main()
{
	normal = normalize(normal_matrix * vertex_normal);
	position = vec3(modelview_matrix * vec4(vertex_position,1.0));
	gl_Position = mvp * vec4(vertex_position, 1.0);


	int num_of_lights=0;
	if(mod(light_id,2)==0)
	{
		lights[num_of_lights].light_position=camera_matrix*vec4(0.0,100.0,0.0,1.0);
		num_of_lights++;
	}
	if(mod(light_id,3)==0)
	{
		lights[num_of_lights].light_position=camera_matrix*vec4(200.0,0.0,100.0,1.0);
		num_of_lights++;
	}
	if(mod(light_id,5)==0)
	{
		lights[num_of_lights].light_position=camera_matrix*vec4(-200.0,0.0,100.0,1.0);
		num_of_lights++;
	}
	if(mod(light_id,7)==0)
	{
		lights[num_of_lights].light_position=camera_matrix*vec4(0.0,-200.0,0.0,1.0);
		num_of_lights++;
	}

	vec3 temp;
	for(int i=0;i<num_of_lights;i++)
	{		
		 temp += ads(i);
	}
	temp = temp + vertex_color*0.2;
	color=temp;//add ambient
}
