#include <craft/stateController.hpp>

stateController::stateController () {
}

stateController::stateController (state* initial_state) {
	state_array.push_back(initial_state);
	active = 0;
	flag = 0;
}

void stateController::run () {
	state_array[active]->run();
}