#version 330

in vec3 Color;
in vec3 ec_pos;

vec3 light;
float responce;
vec3 ec_normal;

out vec4 outColor;

void main()
{
	light = vec3(-1.0, -1.0, -1.0);
	
	ec_normal = cross(dFdx(ec_pos), dFdy(ec_pos));
	
	responce = dot(normalize(ec_normal), -normalize(light)) * 0.5 + 0.5;
	
    outColor = vec4(Color * responce, 1);
}