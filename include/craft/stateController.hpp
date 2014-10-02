#ifndef STATECONTROLLER_H__
	#define STATECONTROLLER_H__
	
	#include <craft/platformSpecification.hpp>
	#include <craft/state.hpp>
	
	#include <vector>

	class stateController {
		std::vector<state*> state_array;
		int active;
		int flag;
		
		public:
			stateController ();
			stateController (state*);
			void run ();
	};
	
#endif