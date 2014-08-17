#version 330

in vec3 vertex;
in vec2 uv;
in vec3 coordinate;

out vec3 Color;

uniform mat4 view;
uniform mat4 proj;

mat4 inverted;
vec3 camera;
float fog;

void main()
{
	inverted = inverse(view);
	camera = vec3(inverted[3][0], inverted[3][1], inverted[3][2]);
	fog = ( distance(camera, coordinate) / 64 ) * -1 + 1;
	Color = vec3(1, 1, 1) * fog;
    gl_Position = proj * view * vec4(vertex + coordinate, 1.0);
}