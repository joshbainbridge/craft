#ifndef SEGMENT
	#include <craft/platformSpecification.hpp>

	class segment {
		float data[16][16][16];
		GLfloat buffer[12288];
	
		int xpos, ypos, zpos;
		char flag;
		
		GLuint* attrib_loc;
	
		int counter;
		GLuint vbo;
	
		public:
			segment ();
			segment (int, int, int, GLuint*);
			void init (int, int, int, GLuint*);
			void render ();
			void updateData (int, int, int);
			void updateBuffer ();
			int getxpos ();
			int getypos ();
			int getzpos ();
			char getflag ();
	};
	
	#define SEGMENT
#endif