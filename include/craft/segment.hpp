#ifndef SEGMENT
	#include <craft/platformSpecification.hpp>
	#include <craft/shaderProgram.hpp>

	class segment {
		float data[16][16][16];
		GLfloat buffer[4096];
	
		int xpos, ypos, zpos;
		char flag;
		
		GLuint attrib_loc;
	
		int counter;
		GLuint vbo;
		GLuint vao;
	
		public:
			segment ();
			segment (int, int, int, GLuint);
			void render ();
	};
	
	#define SEGMENT
#endif