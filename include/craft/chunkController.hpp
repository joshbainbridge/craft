#ifndef CHUNKCONTROLLER
	#include <craft/platformSpecification.hpp>
	#include <craft/chunk.hpp>
	#include <craft/shaderVoxel.hpp>
	#include <craft/character.hpp>

	class chunkController {
		chunk chunk_list[9][9];
		
		character* player;
		shaderVoxel* shader;
		
		public:
			chunkController ();
			chunkController (character*, shaderVoxel*);
			chunk* getChunk (int, int);
			void updateData();
			void updateBuffer();
			void render();
	};
	
	#define CHUNKCONTROLLER
#endif