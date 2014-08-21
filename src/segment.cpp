#include <craft/segment.hpp>
#include <iostream>

segment::segment () {
	init();
}

void segment::init () {
	flag = 0;
	count_one = 0;
	
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			for (int k = 0; k < 16; k++) {
				data[i][j][k] = 0.0f;
			}
		}
	}
	
	for (int i = 0; i < 16384; i++) { 
		buffer_one[i] = 0.0f;
	}
	
	glGenBuffers(1, &vbo_one);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_one);
	glBufferData(GL_ARRAY_BUFFER, sizeof(buffer_one), buffer_one, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	for (int i = 0; i < 2048; i++) { 
		buffer_two[i] = 0.0f;
	}
	
	glGenBuffers(1, &vbo_two);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_two);
	glBufferData(GL_ARRAY_BUFFER, sizeof(buffer_two), buffer_two, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	for (int i = 0; i < 256; i++) { 
		buffer_three[i] = 0.0f;
	}
	
	glGenBuffers(1, &vbo_three);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_three);
	glBufferData(GL_ARRAY_BUFFER, sizeof(buffer_three), buffer_three, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	for (int i = 0; i < 32; i++) { 
		buffer_four[i] = 0.0f;
	}
	
	glGenBuffers(1, &vbo_four);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_four);
	glBufferData(GL_ARRAY_BUFFER, sizeof(buffer_four), buffer_four, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	for (int i = 0; i < 4; i++) { 
		buffer_five[i] = 0.0f;
	}
	
	glGenBuffers(1, &vbo_five);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_five);
	glBufferData(GL_ARRAY_BUFFER, sizeof(buffer_five), buffer_five, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void segment::updateGLBuffer () {
	glBindBuffer(GL_ARRAY_BUFFER, vbo_one);
	glBufferData(GL_ARRAY_BUFFER, sizeof(buffer_one), NULL, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(buffer_one), buffer_one);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo_two);
	glBufferData(GL_ARRAY_BUFFER, sizeof(buffer_two), NULL, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(buffer_two), buffer_two);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo_three);
	glBufferData(GL_ARRAY_BUFFER, sizeof(buffer_three), NULL, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(buffer_three), buffer_three);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo_four);
	glBufferData(GL_ARRAY_BUFFER, sizeof(buffer_four), NULL, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(buffer_four), buffer_four);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo_five);
	glBufferData(GL_ARRAY_BUFFER, sizeof(buffer_five), NULL, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(buffer_five), buffer_five);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void segment::render (int index, GLuint coordAttrib, GLuint scaleAttrib) {
	
	switch (index) {
		case 1:
			glBindBuffer(GL_ARRAY_BUFFER, vbo_one);
			glVertexAttribPointer(coordAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*4, 0);
			glVertexAttribPointer(scaleAttrib, 1, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*4, (const void*) (sizeof(float)*3));
			glDrawElementsInstanced( GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, count_one / 4 );
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			break;
		case 2:
			glBindBuffer(GL_ARRAY_BUFFER, vbo_two);
			glVertexAttribPointer(coordAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*4, 0);
			glVertexAttribPointer(scaleAttrib, 1, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*4, (const void*) (sizeof(float)*3));
			glDrawElementsInstanced( GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, count_two / 4 );
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			break;
		case 3:
			glBindBuffer(GL_ARRAY_BUFFER, vbo_three);
			glVertexAttribPointer(coordAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*4, 0);
			glVertexAttribPointer(scaleAttrib, 1, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*4, (const void*) (sizeof(float)*3));
			glDrawElementsInstanced( GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, count_three / 4 );
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			break;
		case 4:
			glBindBuffer(GL_ARRAY_BUFFER, vbo_four);
			glVertexAttribPointer(coordAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*4, 0);
			glVertexAttribPointer(scaleAttrib, 1, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*4, (const void*) (sizeof(float)*3));
			glDrawElementsInstanced( GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, count_four / 4 );
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			break;
		case 5:
			glBindBuffer(GL_ARRAY_BUFFER, vbo_five);
			glVertexAttribPointer(coordAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*4, 0);
			glVertexAttribPointer(scaleAttrib, 1, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*4, (const void*) (sizeof(float)*3));
			glDrawElementsInstanced( GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, count_five / 4 );
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			break;
	}
	
}

void segment::setFlag (char input) {
	flag = input;
}

void segment::setCounter (int index, int input) {
	switch (index) {
		case 1:
			count_one = input;
			break;
		case 2:
			count_two = input;
			break;
		case 3:
			count_three = input;
			break;
		case 4:
			count_four = input;
			break;
		case 5:
			count_five = input;
			break;
	}
}

float (*segment::getData())[16][16] {
	return data;
}

GLfloat* segment::getBuffer (int index) {
	switch (index) {
		case 1:
			return buffer_one;
		case 2:
			return buffer_two;
		case 3:
			return buffer_three;
		case 4:
			return buffer_four;
		case 5:
			return buffer_five;
		default:
			return 0;
	}
}

int segment::getFlag () {
	return flag;
}

int segment::getCounter () {
	return count_one;
}