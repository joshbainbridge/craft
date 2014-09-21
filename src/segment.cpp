#include <craft/segment.hpp>
#include <iostream>

segment::segment () {
	init();
}

void segment::init () {
	flag = 0;
	count = 0;
	
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			for (int k = 0; k < 16; k++) {
				data[i][j][k] = 0.0f;
			}
		}
	}
	
	for (int i = 0; i < 16384; i++) { 
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

void segment::render (GLuint coordAttrib, GLuint scaleAttrib) {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(coordAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*4, 0);
	glVertexAttribPointer(scaleAttrib, 1, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*4, (const void*) (sizeof(float)*3));
	glDrawElementsInstanced( GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, count / 4 );
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void segment::setFlag (char input) {
	flag = input;
}

void segment::setCounter (int input) {
	count = input;
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
	return count;
}