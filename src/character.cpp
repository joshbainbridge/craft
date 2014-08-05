#include <craft/character.hpp>

#define GLM_FORCE_RADIANS
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_inverse.hpp> 
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

character::character () {
}

character::character (float xpos_input, float ypos_input, float zpos_input, settings* settings_input) {
	xpos = xpos_input;
	ypos = ypos_input;
	zpos = zpos_input;
	
	xdown = 0;
	ydown = 0;
	zdown = 0;
	
	xvel = 0;
	yvel = 0;
	zvel = 0;
	
	zrot = 0.5;
	xrot = 0.5;
	
	zrdown = 0;
	xrdown = 0;
	
	zrvel = 0;
	xrvel = 0;
	
	engine_settings = settings_input;
	
	view = glm::translate(glm::mat4(1.0f), glm::vec3(xpos, ypos, zpos));
	view = glm::rotate(view, glm::pi<float>() * xrot, glm::vec3(0, 0, 1));
	view = glm::rotate(view, glm::pi<float>() * zrot, glm::vec3(1, 0, 0));
	view = glm::affineInverse(view);
	
	proj = glm::perspective(
		45.0f,
		engine_settings->getRatio(),
		10.0f,
		80.0f
	);
	
	flag = 0;
}

void character::update () {
	if (xdown == 1) {
		xvel += 0.5f;
	} else if (xdown == -1) {
		xvel -= 0.5f;
	}
	
	if (ydown == 1) {
		yvel += 0.5f;
	} else if (ydown == -1) {
		yvel -= 0.5f;
	}
	
	if (zdown == 1) {
		zvel += 0.5f;
	} else if (zdown == -1) {
		zvel -= 0.5f;
	}
	
	if (zrdown == 1) {
		zrvel += 0.01f;
	} else if (zrdown == -1) {
		zrvel -= 0.01f;
	}
	
	if (xrdown == 1) {
		xrvel += 0.01f;
	} else if (xrdown == -1) {
		xrvel -= 0.01f;
	}
	
	view = glm::translate(glm::mat4(1.0f), glm::vec3(xpos, ypos, zpos));
	view = glm::rotate(view, glm::pi<float>() * xrot + xrvel, glm::vec3(0, 0, 1));
	view = glm::rotate(view, glm::pi<float>() * zrot + zrvel, glm::vec3(1, 0, 0));
	view = view * glm::translate(glm::mat4(1.0f), glm::vec3(xvel, yvel, zvel));
	
	xpos = view[3][0];
	ypos = view[3][1];
	zpos = view[3][2];
	
	xrot = xrot + xrvel;
	zrot = zrot + zrvel;
	
	view = glm::affineInverse(view);
	
	xvel *= 0.5;
	yvel *= 0.5;
	zvel *= 0.5;
	
	zrvel *= 0.5;
	xrvel *= 0.5;
	
	flag = 2;
}

void character::setXdown (int input) {
	xdown = input;
	flag = 1;
}

void character::setYdown (int input) {
	ydown = input;
	flag = 1;
}

void character::setZdown (int input) {
	zdown = input;
	flag = 1;
}

void character::setZrdown (int input) {
	zrdown = input;
	flag = 1;
}

void character::setXrdown (int input) {
	xrdown = input;
	flag = 1;
}

void character::setFlag (int input) {
	flag = input;
}

glm::mat4 character::getView () {
	return view;
}

glm::mat4 character::getProj () {
	return proj;
}

float character::getXpos () {
	return xpos;
}

float character::getYpos () {
	return ypos;
}

float character::getZpos () {
	return zpos;
}

int character::getFlag () {
	return flag;
}