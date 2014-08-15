#ifndef CHUNK
	#define CHUNK
	
	#include <craft/platformSpecification.hpp>
	#include <craft/segment.hpp>

	class chunk {
		segment segment_list[8];
		char flag;
		
		public:
			chunk ();
			void init ();
			char getFlag ();
			segment* getSeg (int);
			void setFlag (char);
	};
	
#endif