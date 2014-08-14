#include <craft/settings.hpp>

settings::settings () {
	resx = 940;
	resy = 480;
	cuda = 0;
}

settings::settings (int x_input, int y_input) {
	resx = x_input;
	resy = y_input;
	cuda = 0;
}

void settings::setResX (int input) {
	resx = input;
}

void settings::setResY (int input) {
	resy = input;
}

int settings::getResX () {
	return resx;
}

int settings::getResY () {
	return resy;
}

float settings::getRatio () {
	return (float) resx / (float) resy;
}