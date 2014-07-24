#version 150

in vec3 Color;

out vec4 outColor;

uniform float alpha;

void main()
{
    outColor = vec4(Color * alpha, 1);
}