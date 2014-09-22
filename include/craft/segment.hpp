#ifndef SEGMENT
	#define SEGMENT
	
	#include <craft/platformSpecification.hpp>
	#include <craft/octreeNode.hpp>

	class segment {
		float data[16][16][16];
		octreeNode* octree;
		
		GLfloat buffer[163840];
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
			void setOctree (octreeNode*);
			float (*getData())[16][16];
			GLfloat* getBuffer ();
			int getFlag ();
			int getCounter ();
			octreeNode* getOctree();
	};
	
#endif