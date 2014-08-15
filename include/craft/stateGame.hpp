#ifndef STATEGAME
	#define STATEGAME
	
	#include <craft/platformSpecification.hpp>
	#include <craft/settings.hpp>
	#include <craft/state.hpp>
	
	class stateGame: public state {
	
		public:
			stateGame ();
			stateGame (GLFWwindow*, settings*);
			void run ();
	};
	
#endif