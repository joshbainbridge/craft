#ifndef SEGMENT
	#include <craft/platformSpecification.hpp>

	class segment {
		float data[16][16][16];
		GLfloat buffer[12288];
		int flag;
		
		int counter;
		GLuint vbo;
		
		public:
			segment ();
			void init ();
			void updateGLBuffer ();
			void render (GLuint*);
			void setFlag (char);
			void setCounter (int);
			float (*getData())[16][16];
			GLfloat* getBuffer ();
			int getFlag ();
			int getCounter ();
	};
	
	#define SEGMENT
#endif