#include <craft/plane.hpp>
#include <iostream>

plane::plane ()
{
}

plane::plane (glm::vec3 a, glm::vec3 b, glm::vec3 p)
{
	init(a, b, p);
}

void plane::init (glm::vec3 a, glm::vec3 b, glm::vec3 p)
{
	n = glm::normalize(glm::cross(a - p, b - p));
	h = glm::length(p) * glm::dot(n, glm::normalize(p));
}

int plane::intersection(glm::vec3 p, float r)
{
	//std::cout << ( glm::dot(p, n) + r - h ) << std::endl;
	if ( ( glm::dot(p, n) + r - h ) > 0 ) {
		return 1;
	} else {
		return 0;
	}
}