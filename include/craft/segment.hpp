#ifndef SEGMENT
	#define SEGMENT
	
	#include <craft/platformSpecification.hpp>

	class segment {
		float data[16][16][16];
		
		GLfloat buffer[16384];
		GLuint vbo;
		int count;
		
		int flag;
		
		public:
			segment ();
			void init ();
			void updateGLBuffer ();
			void render (GLuint, GLuint);
			void setFlag (char);
			void setCounter (int);
			float (*getData())[16][16];
			GLfloat* getBuffer ();
			int getFlag ();
			int getCounter ();
	};
	
#endif