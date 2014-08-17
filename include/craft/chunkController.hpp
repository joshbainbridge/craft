#ifndef CHUNKCONTROLLER
	#define CHUNKCONTROLLER
	
	#include <craft/platformSpecification.hpp>
	#include <craft/chunk.hpp>
	#include <craft/shaderVoxel.hpp>
	#include <craft/character.hpp>
	
	#include <vector>

	class chunkController {
		std::vector< std::vector<chunk*> > chunk_list;
		
		public:
			chunkController ();
			chunkController (character*);
			~chunkController ();
			void updateSegFlag(character*);
			void updateData(character*);
			void updateBuffer();
			void render(shaderVoxel*);
	};
	
#endif