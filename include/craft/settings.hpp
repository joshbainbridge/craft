#ifndef PLATFORM_SPECIFICATION
	#include <craft/platformSpecification.hpp>
#endif

class settings {
	int resx;
    int resy;
    char cuda;
  public:
    settings ();
    settings (int x_input, int y_input);
    void setResX (int input);
    void setResY (int input);
    int getResX ();
    int getResY ();
    float getRatio ();
};