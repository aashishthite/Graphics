#version 400

layout (location = 0) out vec4 FragColor;

flat in vec3 color;
in vec3 position;
in vec3 normal;
in vec3 raw_vertex_pos;

uniform int light_id;
uniform int special_effect;
uniform int after_effect;
uniform mat4 camera_matrix;
uniform vec3 reflectance;

const float shininess = 20.0f;
//const vec3 light_position = vec3(0.0, 0.0, 0.0);

vec4 color_preprocess;
vec3 cool_color;

struct LightInfo{
	vec4 light_position;
};

 LightInfo lights[4];

vec3 ads(int light_index )
{
  vec3 n = normal;

  if (!gl_FrontFacing)
	n = -n;
  vec3 l=vec3(lights[light_index].light_position.x,lights[light_index].light_position.y,lights[light_index].light_position.z);
  vec3 s = normalize( l- position);
  vec3 v = normalize(-position);
  vec3 r = normalize(reflect(-s, n));
  float s_dot_n = max(dot(s, n), 0.0);
  

  return cool_color * s_dot_n + (s_dot_n > 0 ? cool_color * reflectance.x * pow(max(dot(r, v), 0.0), shininess) : vec3(0.0));
}

float posterize(float in_color)
{
   int steps = 10;
   return float((1 + int(in_color * steps))) /float(steps + 1);
}

void main()
{
	float slice;
	bool gray = false;
	vec3 gray_color = vec3(0.3,0.3,0.3);
	vec3 white_color = vec3(0.8,0.8,0.8);
	switch(special_effect)
	{
		case 2:
			slice = 20.0 * (0.5+raw_vertex_pos.y);
			if(int(slice)%2 == 0)
			{
				cool_color = gray_color;
			}
			else
			{
				cool_color = color;
			}
			break;
		case 1:
			slice = 3.0 * (0.5+raw_vertex_pos.y);
			if(int(slice)%2 == 0)
			{
				gray = !gray;
			}
			slice = 3.0 * (0.5+raw_vertex_pos.x);
			if(int(slice)%2 == 0)
			{
				gray = !gray;
			}
			slice = 3.0 * (0.5+raw_vertex_pos.z);
			if(int(slice)%2 == 0)
			{
				gray = !gray;;
			}
			if(gray)
			{
				cool_color = gray_color;
			}
			else
			{
				cool_color = color;
			}
			break;
		case 3:
			cool_color = cos(raw_vertex_pos.y*15.0) * color + (1.0-cos(raw_vertex_pos.y*15.0)) * gray_color;
			break;
		default:
			cool_color = color;
			break;
	}
	
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

	vec4 temp;
	for(int i=0;i<num_of_lights;i++)
	{
		
		 temp += vec4(ads(i), 1.0);
	}
	
	color_preprocess=temp+vec4(cool_color*0.2,0.1);//add ambient
	//FragColor = vec4(ads(), 1.0);
	switch(after_effect)
	{
		case 1:
			FragColor.x = 1.0 - color_preprocess.x;
			FragColor.y = 1.0 - color_preprocess.y;
			FragColor.z = 1.0 - color_preprocess.z;
			FragColor.w = color_preprocess.w;
			break;
		case 2:
			FragColor.x = posterize(color_preprocess.x);
			FragColor.y = posterize(color_preprocess.y);
			FragColor.z = posterize(color_preprocess.z);
			break;
		default:
			FragColor=color_preprocess;
			break;
	}
}
