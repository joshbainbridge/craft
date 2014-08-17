#ifndef CHUNKCONTROLLER
	#define CHUNKCONTROLLER
	
	#include <craft/platformSpecification.hpp>
	#include <craft/chunk.hpp>
	#include <craft/shaderVoxel.hpp>
	#include <craft/character.hpp>

	class chunkController {
		chunk chunk_list[9][9];
		
		public:
			chunkController ();
			chunkController (character*);
			void updateData(character*);
			void updateBuffer();
			void render(shaderVoxel*);
	};
	
#endif