#ifndef SEGMENT_H__
	#define SEGMENT_H__
	
	#include <craft/platformSpecification.hpp>
	#include <craft/octreeNode.hpp>

	class segment
	{
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
			GLfloat* getBuffer ();
			int getFlag ();
			int getCounter ();
			octreeNode* getOctree();
	};
	
#endif