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
	
	zrot = 0.5;
	xrot = 0.5;
	
	engine_settings = settings_input;
	
	view = glm::translate(glm::mat4(1.0f), glm::vec3(xpos, ypos, zpos));
	view = glm::rotate(view, glm::pi<float>() * xrot, glm::vec3(0, 0, 1));
	view = glm::rotate(view, glm::pi<float>() * zrot, glm::vec3(1, 0, 0));
	view = glm::affineInverse(view);
	
	/*
	view = glm::lookAt(
		glm::vec3(xpos, ypos, zpos),
		glm::vec3(0.0f, 0.0f, 64.0f),
		glm::vec3(0.0f, 0.0f, 1.0f)
	);
	*/
	
	proj = glm::perspective(
		45.0f,
		engine_settings->getRatio(),
		10.0f,
		80.0f
	);
	
	flag = 0;
}

void character::update () {
	if (flag == 1) {
		view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(xpos, ypos, zpos));
		view = glm::rotate(view, glm::pi<float>() * xrot, glm::vec3(0, 0, 1));
		view = glm::rotate(view, glm::pi<float>() * zrot, glm::vec3(1, 0, 0));
		view = glm::affineInverse(view);
		
		flag = 0;
	}
}

void character::setXpos (float input) {
	xpos = input;
	flag = 1;
}

void character::setYpos (float input) {
	ypos = input;
	flag = 1;
}

void character::setZpos (float input) {
	zpos = input;
	flag = 1;
}

void character::setZrot (float input) {
	zrot = input;
	flag = 1;
}

void character::setXrot (float input) {
	xrot = input;
	flag = 1;
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

float character::getZrot () {
	return zrot;
}

float character::getXrot () {
	return xrot;
}