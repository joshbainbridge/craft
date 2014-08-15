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
	
	fov = 2.0f;
	nclip = 2.0f;
	fclip = 80.0f;
	
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
		fov,
		engine_settings->getRatio(),
		nclip,
		fclip
	);
	/*
	proj = glm::ortho(
		-10.0f,
		10.0f,
		-10.0f,
		10.0f,
		nclip,
		fclip
	);
	*/
	
	
	glm::vec3 p;
	glm::vec3 d;
	glm::vec3 right;
	glm::vec3 up;
	float nearDist;
	float Hnear;
	float Wnear;
	float farDist;
	float Hfar;
	float Wfar;
	
	p = glm::vec3(0.0f, 0.0f, 0.0f);
	d = glm::vec3(0.0f, 1.0f, 0.0f);
	//d = glm::rotate(d, glm::pi<float>() * xrot, glm::vec3(0, 0, 1));
	//d = glm::rotate(d, glm::pi<float>() * zrot, glm::vec3(1, 0, 0));
	right = glm::normalize( glm::cross(d, glm::vec3(1.0f,0.0f,0.0f)) );
	up = glm::normalize(glm::cross(d, right));
	
	nearDist = nclip;
	Hnear = glm::tan( fov/2.0f ) * nearDist;
	Wnear = Hnear * engine_settings->getRatio();
	
	farDist = fclip;
	Hfar = glm::tan( fov/2.0f ) * farDist;
	Wfar = Hfar * engine_settings->getRatio();
	
	view_frustum.fc = p + d * farDist;
	view_frustum.ftl = view_frustum.fc + (up * Hfar) - (right * Wfar);
	view_frustum.ftr = view_frustum.fc + (up * Hfar) + (right * Wfar);
	view_frustum.fbl = view_frustum.fc - (up * Hfar) - (right * Wfar);
	view_frustum.fbr = view_frustum.fc - (up * Hfar) + (right * Wfar);
	
	view_frustum.nc = p + d * nearDist;
	view_frustum.ntl = view_frustum.nc + (up * Hnear) - (right * Wnear);
	view_frustum.ntr = view_frustum.nc + (up * Hnear) + (right * Wnear);
	view_frustum.nbl = view_frustum.nc - (up * Hnear) - (right * Wnear);
	view_frustum.nbr = view_frustum.nc - (up * Hnear) + (right * Wnear);
	
	
	flag = 0;
}

void character::update () {
	if (flag == 1) {
		if (xdown == 1) {
			xvel += 0.3f;
		} else if (xdown == -1) {
			xvel -= 0.3f;
		}
	
		if (ydown == 1) {
			yvel += 0.3f;
		} else if (ydown == -1) {
			yvel -= 0.3f;
		}
	
		if (zdown == 1) {
			zvel += 0.3f;
		} else if (zdown == -1) {
			zvel -= 0.3f;
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
	
		xrot = xrot + xrvel;
		zrot = zrot + zrvel;
		
		view = glm::translate(glm::mat4(1.0f), glm::vec3(xpos, ypos, zpos));
		view = glm::rotate(view, glm::pi<float>() * xrot, glm::vec3(0, 0, 1));
		view = glm::rotate(view, glm::pi<float>() * zrot, glm::vec3(1, 0, 0));
		view = view * glm::translate(glm::mat4(1.0f), glm::vec3(xvel, yvel, zvel));
	
		xpos = view[3][0];
		ypos = view[3][1];
		zpos = view[3][2];
	
		view = glm::affineInverse(view);
	
		if (xvel != 0) {
			xvel *= 0.75;
			if ( (xvel < 0.01f && xvel > 0.0f) || (xvel > -0.01f && xvel < 0.0f) )
				xvel = 0; 
		}
	
		if (yvel != 0) {
			yvel *= 0.75;
			if ( (yvel < 0.01f && yvel > 0.0f) || (yvel > -0.01f && yvel < 0.0f) )
				yvel = 0; 
		}
	
		if (zvel != 0) {
			zvel *= 0.75;
			if ( (zvel < 0.01f && zvel > 0.0f) || (zvel > -0.01f && zvel < 0.0f) )
				yvel = 0; 
		}
	
		if (zrvel != 0) {
			zrvel *= 0.5;
			if ( (zrvel < 0.001f && zrvel > 0.0f) || (zrvel > -0.001f && zrvel < 0.0f) )
				zrvel = 0; 
		}
	
		if (xrvel != 0) {
			xrvel *= 0.5;
			if ( (xrvel < 0.001f && xrvel > 0.0f) || (xrvel > -0.001f && xrvel < 0.0f) )
				xrvel = 0; 
		}
	
		flag = 2;
	}
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

void character::setFov (float input) {
	fov = input;
}

void character::setNclip (float input) {
	nclip = input;
}

void character::setFclip (float input) {
	fclip = input;
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

float character::getFov () {
	return fov;
}

float character::getNclip () {
	return nclip;
}

float character::getFclip () {
	return fclip;
}

int character::getFlag () {
	return flag;
}