#ifndef CHUNKCONTROLLER
	#define CHUNKCONTROLLER
	
	#include <craft/platformSpecification.hpp>
	#include <craft/chunk.hpp>
	#include <craft/shaderVoxel.hpp>
	#include <craft/character.hpp>
	
	#include <vector>

	class chunkController {
		chunk chunk_list[9][9];
		std::vector< std::vector<chunk*> > chunk_list_new;
		
		public:
			chunkController ();
			chunkController (character*);
			~chunkController ();
			void updateData(character*);
			void updateBuffer();
			void render(shaderVoxel*);
	};
	
#endif