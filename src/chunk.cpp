#include <craft/chunk.hpp>

chunk::chunk () {
	init ();
}

void chunk::init () {
	flag = 0;
	
	for (int i = 0; i < 8; i++) {
		segment_list[i].init();
	}
}

char chunk::getFlag () {
	return flag;
}

segment* chunk::getSeg (int index) {
	return &segment_list[index];
}

void chunk::setFlag (char input) {
	flag = input;
}