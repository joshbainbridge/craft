#include <craft/stateGame.hpp>

stateGame::stateGame () {
}

stateGame::stateGame (GLFWwindow* window_input, settings* settings_input) {
	window = window_input;
	engine_settings = settings_input;
}

void stateGame::run () {
}