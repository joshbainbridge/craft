#ifndef STATE_H__
	#define STATE_H__
	
	#include <craft/platformSpecification.hpp>
	#include <craft/settings.hpp>

	class state
	{
		
		protected:
			GLFWwindow* window;
			settings* engine_settings;
	
		public:
			state ();
			virtual void run () =0;
	};
	
#endif