#version 330
#define M_PI 3.1415926535897932384626433832795

in vec3 vertex;
in vec2 uv;
in vec3 coordinate;
in float scale;

out vec3 Color;

uniform mat4 view;
uniform mat4 proj;

mat4 inverted;
vec3 camera;
float fog;

float cs;
float sn;
float theta;
vec3 pos1;
vec3 pos2;
vec3 pos3;

void main()
{
	inverted = inverse(view);
	camera = vec3(inverted[3][0], inverted[3][1], inverted[3][2]);
	fog = ( distance(camera, coordinate) / 64 ) * -1 + 1;
	Color = vec3(1 * ( sin(coordinate[0]*0.03) * 0.5 + 0.5 ), 1 * ( sin(coordinate[1]*0.02) * 0.5 + 0.5 ), 1 * ( sin(coordinate[2]*0.025) * 0.5 + 0.5 )) * fog;
	Color = smoothstep(0, 1, Color * 2);
	
	pos1 = (vertex * scale) + coordinate;
	pos2 = pos1;
	pos3 = pos2;
	
	theta = pos1[0] - camera[0];
	cs = cos(M_PI * theta * -0.1);
	sn = sin(M_PI * theta * -0.1);
	pos1[0] = 0;
	pos2[0] = pos1[0] * cs - pos1[2] * sn;
	pos2[2] = pos1[0] * sn + pos1[2] * cs;
	pos2[0] += pos3[0];
	
	theta = pos1[1] - camera[1];
	cs = cos(M_PI * theta * -0.1);
	sn = sin(M_PI * theta * -0.1);
	pos2[1] = 0;
	pos1[1] = pos2[1] * cs - pos2[2] * sn;
	pos1[2] = pos2[1] * sn + pos2[2] * cs;
	pos1[1] += pos3[1];
	
    gl_Position = proj * view * vec4(pos1, 1.0);
}