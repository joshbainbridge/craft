#include <craft/chunkController.hpp>

chunkController::chunkController (GLuint* attrib_input) {
	attrib_loc = attrib_input;
	
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			chunk_list[i][j].init(i - 4, j - 4, attrib_loc);
		}
	}
}

void chunkController::renderChunk () {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			chunk_list[i][j].renderSeg();
		}
	}
}
