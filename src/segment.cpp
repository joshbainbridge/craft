#include <craft/segment.hpp>
#include <iostream>

segment::segment () {
	init();
}

void segment::init () {
	flag = 0;
	counter = 0;
	
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			for (int k = 0; k < 16; k++) {
				data[i][j][k] = 0.0f;
			}
		}
	}
	
	for (int i = 0; i < 12288; i++) { 
		buffer[i] = 0.0f;
	}
	
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(buffer), buffer, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void segment::updateGLBuffer () {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(buffer), NULL, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(buffer), buffer);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void segment::render (GLuint coordAttrib) {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(coordAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*3, 0);
	glDrawElementsInstanced( GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, counter / 3 );
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void segment::setFlag (char input) {
	flag = input;
}

void segment::setCounter (int input) {
	counter = input;
}

float (*segment::getData())[16][16] {
	return data;
}

GLfloat* segment::getBuffer () {
	return buffer;
}

int segment::getFlag () {
	return flag;
}

int segment::getCounter () {
	return counter;
}