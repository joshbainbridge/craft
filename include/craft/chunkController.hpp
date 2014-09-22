#ifndef CHUNKCONTROLLER
	#define CHUNKCONTROLLER
	
	#include <craft/platformSpecification.hpp>
	#include <craft/segment.hpp>
	#include <craft/chunk.hpp>
	#include <craft/shaderVoxel.hpp>
	#include <craft/character.hpp>
	#include <craft/octreeNode.hpp>
	
	#include <vector>

	class chunkController {
		std::vector< std::vector<chunk*> > chunk_list;
		float data_buffer[16][16][16];
		int flag;
		
		octreeNode* traverseTree (int, int, int, int);
		void dataConstructor (int, int, std::vector< std::vector<chunk*> >);
		void sourceTree (octreeNode*, int, int, int, int, int*, segment*);
		void bufferConstructor (int, int, std::vector< std::vector<chunk*> >);
		
		public:
			chunkController ();
			chunkController (character*);
			~chunkController ();
			void updateSegFlag (character*);
			void updateData (character*);
			void updateBuffer ();
			void render (character*, shaderVoxel*);
			void setFlag (int);
			int getFlag ();
	};
	
#endif