#ifndef CHUNK
	#include <craft/platformSpecification.hpp>
	#include <craft/segment.hpp>

	class chunk {
		int xpos, ypos;
		char flag;
		
		GLuint* attrib_loc;
		
		segment segment_list[8];
	
		public:
			chunk ();
			chunk (int, int, GLuint*);
			void init (int, int, GLuint*);
			void renderSeg ();
			void updateSegData ();
			void updateSegBuffer ();
			int getxpos ();
			int getypos ();
			char getflag ();
			segment getSeg (int);
	};
	
	#define CHUNK
#endif