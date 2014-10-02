#ifndef CHUNK_H__
	#define CHUNK_H__
	
	#include <craft/platformSpecification.hpp>
	#include <craft/segment.hpp>

	class chunk
	{
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