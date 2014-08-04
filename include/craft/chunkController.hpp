#ifndef CHUNKCONTROLLER
	#include <craft/platformSpecification.hpp>
	#include <craft/chunk.hpp>

	class chunkController {
		chunk chunk_list[9][9];
		
		GLuint* attrib_loc;
	
		public:
			chunkController (GLuint*);
			void renderChunk ();
	};
	
	#define CHUNKCONTROLLER
#endif