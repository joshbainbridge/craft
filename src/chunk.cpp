#include <craft/chunk.hpp>

chunk::chunk () {
}

chunk::chunk (int xinput, int yinput, GLuint* attrib_input) {
	init (xinput, yinput, attrib_input);
}

void chunk::init (int xinput, int yinput, GLuint* attrib_input) {
	flag = 0;
	
	xpos = xinput;
	ypos = yinput;
	
	attrib_loc = attrib_input;
	
	for (int i = 0; i < 8; i++) {
		segment_list[i].init(xpos, ypos, i, attrib_loc);
	}
}

void chunk::renderSeg () {
	for (int i = 0; i < 8; i++) {
		segment_list[i].render();
	}
}

void chunk::updateSegData () {
	for (int i = 0; i < 8; i++) {
		segment_list[i].updateData(xpos, ypos, i);
	}
}

void chunk::updateSegBuffer () {
	for (int i = 0; i < 8; i++) {
		segment_list[i].updateBuffer();
	}
}

int chunk::getxpos () {
	return xpos;
}

int chunk::getypos () {
	return ypos;
}

char chunk::getflag () {
	return flag;
}

segment chunk::getSeg (int index) {
	return segment_list[index];
}