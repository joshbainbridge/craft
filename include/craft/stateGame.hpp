#ifndef STATEGAME_H__
	#define STATEGAME_H__
	
	#include <craft/platformSpecification.hpp>
	#include <craft/settings.hpp>
	#include <craft/state.hpp>
	
	class stateGame: public state
	{
	
		public:
			stateGame ();
			stateGame (GLFWwindow*, settings*);
			void run ();
	};
	
#endif