#ifndef SETTINGS
	#include <craft/platformSpecification.hpp>

	class settings {
		int resx;
		int resy;
		float fov;
		char cuda;
	  public:
		settings ();
		settings (int x_input, int y_input);
		void setResX (int input);
		void setResY (int input);
		void setFov (float input);
		int getResX ();
		int getResY ();
		float getFov ();
		float getRatio ();
	};
	
	#define SETTINGS
#endif