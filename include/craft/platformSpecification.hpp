#ifndef PLATFORM_SPECIFICATION
	#ifdef _WIN32
		#define GLEW_STATIC
		#include <GL/glew.h>
		#include <GLFW/glfw3.h>
		#include <windows.h>
	#elif __APPLE__
		#define GLFW_INCLUDE_GLCOREARB
		#include <GLFW/glfw3.h>
		#include <unistd.h>
		#define Sleep(x) usleep((x)*1000)
	#elif __linux__
	#endif
	
	#define PLATFORM_SPECIFICATION
#endif