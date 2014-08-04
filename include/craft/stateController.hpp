#ifndef STATECONTROLLER
	#include <craft/platformSpecification.hpp>
	#include <craft/state.hpp>
	
	#include <vector>
	using namespace std;

	class stateController {
		vector<state*> state_array;
		int active;
		int flag;
		
		public:
			stateController ();
			stateController (state*);
			void run ();
	};
	
	#define STATECONTROLLER
#endif