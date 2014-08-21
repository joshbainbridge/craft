#ifndef SEGMENT
	#define SEGMENT
	
	#include <craft/platformSpecification.hpp>

	class segment {
		float data[16][16][16];
		
		GLfloat buffer_one[16384];
		GLfloat buffer_two[2048];
		GLfloat buffer_three[256];
		GLfloat buffer_four[32];
		GLfloat buffer_five[4];
		GLuint vbo_one;
		int count_one;
		GLuint vbo_two;
		int count_two;
		GLuint vbo_three;
		int count_three;
		GLuint vbo_four;
		int count_four;
		GLuint vbo_five;
		int count_five;
		
		int flag;
		
		public:
			segment ();
			void init ();
			void updateGLBuffer ();
			void render (int, GLuint, GLuint);
			void setFlag (char);
			void setCounter (int, int);
			float (*getData())[16][16];
			GLfloat* getBuffer (int);
			int getFlag ();
			int getCounter ();
	};
	
#endif