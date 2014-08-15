#version 330

in vec3 vertex;
in vec2 uv;
in vec3 coordinate;

out vec3 Color;

uniform mat4 view;
uniform mat4 proj;

void main()
{
	Color = vec3(coordinate[0] / 128, coordinate[1] / 128, coordinate[2] / 128);
    gl_Position = proj * view * vec4(vertex + coordinate, 1.0);
}