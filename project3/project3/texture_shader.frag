#version 400

layout (location = 0) out vec4 FragColor;

in vec2 tc;
uniform sampler2D picture;
uniform mat4 camera_matrix;
uniform int light_id;
uniform float wcrop;
uniform float hcrop;
uniform vec2 striker_coord;
uniform int special_mode;


in vec3 raw_vertex_pos;
in vec3 normal;
in vec3 position;

vec3 my_tex_color;
vec3 my_flat_color;
vec3 my_total_color;

const float shininess = 20.0f;
//const vec3 light_position = vec3(0.0, 0.0, 0.0);

vec2 cropped_tc;

struct LightInfo{
	vec4 light_position;
};

 LightInfo lights[4];

vec2 croptexture(vec2 tc)
{
  vec2 newtc;

  float wlimit;
  float hlimit;
  float wscale;
  float hscale;
  float abswcrop;
  float abshcrop;
  
  if(wcrop < 0.0)
  {
    abswcrop = -wcrop;
    wlimit = (abswcrop) / (abswcrop + 25.0);
    wscale = 1.0 - wlimit;
    newtc.x = wlimit + tc.x * wscale;
  }
  else if (wcrop > 0.0)
  {
    abswcrop = wcrop;
    wlimit = 25.0 / (abswcrop + 25.0);
    newtc.x = wlimit * tc.x;
  }
  else
  {
    newtc.x = tc.x;
  }

  if(hcrop < 0.0)
  {
    abshcrop = -hcrop;
    hlimit = (abshcrop) / (abshcrop + 25.0);
    hscale = 1.0 - hlimit;
    newtc.y = hlimit + tc.y * hscale;
  }
  else if (hcrop > 0.0)
  {
    abshcrop = hcrop;
    hlimit = 25.0 / (abshcrop + 25.0);
    newtc.y = hlimit * tc.y;
  }
  else
  {
    newtc.y = tc.y;
  }
  return newtc;
}

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
  

  return my_total_color * s_dot_n + (s_dot_n > 0 ? my_total_color * 0.4 * pow(max(dot(r, v), 0.0), shininess) : vec3(0.0));
}

void main()
{
	float slice;
	float weight;
	//float strike_dist = sqrt(pow((striker_coord.x-raw_vertex_pos.x),2.0)+pow((striker_coord.y-raw_vertex_pos.y),2.0));
	//float strike_dist = sqrt(pow((striker_coord.x-0.0f),2.0)+pow((striker_coord.y-0.0f),2.0));
	float strike_dist = sqrt(pow((striker_coord.x/50.0-raw_vertex_pos.x),2.0)+pow((-striker_coord.y/50.0-raw_vertex_pos.y),2.0));
	//float strike_dist = sqrt(pow((striker_coord.x-position.x),2.0)+pow((striker_coord.y-position.z),2.0));
	weight = (sin(2.0 * strike_dist) + 1.0) / 2.0;
	//if(strike_dist >0.05)
	//{
	//  weight = 1.0;
	//}
	//else
	//{
	//  weight = 0.0;
	//}
	bool colorbool = true;
	cropped_tc = croptexture(tc);
	my_tex_color = vec3(texture(picture, cropped_tc));
	switch(special_mode)
	{
		case 0:
			my_total_color = my_tex_color;
			break;

		case 1:
			slice = 50.0 * (25.0 + raw_vertex_pos.x);
			if(int(slice)%2 == 0)
			{
				colorbool = !colorbool;
			}
			slice = 50.0 * (25.0 + raw_vertex_pos.y);
			if(int(slice)%2 == 0)
			{
				colorbool = !colorbool;
			}
			if(colorbool)
			{
				my_flat_color = vec3(0.7,0.7,0.7);
			}
			else
			{
				my_flat_color = vec3(0.2,0.2,0.2);
			}
			my_total_color = my_flat_color;
			break;
		case 2:
			slice = 50.0 * (25.0 + raw_vertex_pos.x);
			if(int(slice)%2 == 0)
			{
				colorbool = !colorbool;
			}
			slice = 50.0 * (25.0 + raw_vertex_pos.y);
			if(int(slice)%2 == 0)
			{
				colorbool = !colorbool;
			}
			if(colorbool)
			{
				my_flat_color = vec3(0.7,0.7,0.7);
			}
			else
			{
				my_flat_color = vec3(0.2,0.2,0.2);
			}
			my_total_color = (my_tex_color + my_flat_color)/2.0;
			break;
		case 3:
			weight = pow(3.0,-strike_dist * 2.0) * (cos(30.0 * strike_dist) + 1.0) / 2.0;
			slice = 50.0 * (25.0 + raw_vertex_pos.x);
			if(int(slice)%2 == 0)
			{
				colorbool = !colorbool;
			}
			slice = 50.0 * (25.0 + raw_vertex_pos.y);
			if(int(slice)%2 == 0)
			{
				colorbool = !colorbool;
			}
			if(colorbool)
			{
				my_flat_color = vec3(0.7,0.7,0.7);
			}
			else
			{
				my_flat_color = vec3(0.2,0.2,0.2);
			}
			//my_total_color = (my_tex_color + my_flat_color)/2.0;
			my_total_color = (1.0 - weight) * my_tex_color +  (weight) * my_flat_color;
			break;
		case 4:
			my_flat_color = vec3(0.2,0.2,0.5);
			my_total_color = (my_tex_color + my_flat_color)/2.0;
			break;
		case 5:
			my_flat_color = vec3(0.7,0.2,0.5);
			my_total_color = (my_tex_color + my_flat_color)/2.0;
			break;
		case 6:
			my_flat_color = vec3(0.3,0.8,0.1);
			my_total_color = (my_tex_color + my_flat_color)/2.0;
			break;
		default:
			my_flat_color = vec3(0.2,0.5,0.9);
			my_total_color = (my_tex_color + my_flat_color)/2.0;
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
		
		 temp += vec4(ads(i),1.0);
	}
	FragColor = temp+vec4(my_total_color*0.2,1.0);
}
