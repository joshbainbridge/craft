#version 330
#define M_PI 3.1415926535897932384626433832795

in vec3 vertex;
in vec2 uv;
in vec3 coordinate;
in float scale;

out vec3 Color;
out vec3 ec_pos;

uniform mat4 view;
uniform mat4 proj;

mat4 inverted;
vec3 camera;
float fog;
vec3 gamma;

float cs;
float sn;
float theta;
vec3 pos1;
vec3 pos2;

void main()
{
	inverted = inverse(view);
	camera = vec3(inverted[3][0], inverted[3][1], inverted[3][2]);
	fog = ( distance(camera, coordinate) / 64 ) * -1 + 1;
	Color = vec3(1 * ( sin(coordinate[0]*0.03) * 0.5 + 0.5 ), 1 * ( sin(coordinate[1]*0.02) * 0.5 + 0.5 ), 1 * ( sin(coordinate[2]*0.025) * 0.5 + 0.5 ));
	
	if ( (view * vec4(coordinate[0] + (scale * 0.5), coordinate[1] + (scale * 0.5), coordinate[2] + (scale * 0.5), 1.0))[2] >= (25 + (scale * 0.5)) * -1 ) {
		Color = vec3(0.5, 0.2, 0.2);
	}
	
	Color = Color * fog;
	Color = smoothstep(0, 1, Color);
	gamma = vec3(1.0/2.2, 1.0/2.2, 1.0/2.2);
	Color = vec3(pow(Color.r, gamma.r), pow(Color.g, gamma.g), pow(Color.b, gamma.b));
	
	pos1 = (vertex * scale * 0.999) + coordinate;
	pos2 = pos1;
	/*
	theta = pos1[0] - camera[0];
	cs = cos(M_PI * theta * -0.004);
	sn = sin(M_PI * theta * -0.004);
	pos1[0] = 0;
	pos1[2] += 16;
	pos2[0] = pos1[0] * cs - pos1[2] * sn;
	pos2[2] = pos1[0] * sn + pos1[2] * cs;
	pos2[0] += camera[0];
	pos2[2] -= 16;
	*/
	ec_pos = (view * vec4(pos2, 1.0)).xyz;
	
    gl_Position = proj * view * vec4(pos2, 1.0);
}