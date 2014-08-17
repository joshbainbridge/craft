#ifndef CHUNK
	#define CHUNK
	
	#include <craft/platformSpecification.hpp>
	#include <craft/segment.hpp>

	class chunk {
		segment segment_list[8];
		int flag;
		
		public:
			chunk ();
			void init ();
			int getFlag ();
			segment* getSeg (int);
			void setFlag (int);
	};
	
#endif