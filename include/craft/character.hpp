#ifndef CHARACTER
	#include <craft/platformSpecification.hpp>
	#include <craft/settings.hpp>
	
	#include <glm/glm.hpp>

	class character {
		glm::mat4 view;
		glm::mat4 proj;
		
		float xpos, ypos, zpos;
		int xdown, ydown, zdown;
		float xvel, yvel, zvel;
		
		float zrot, xrot;
		int zrdown, xrdown;
		float zrvel, xrvel;
		
		settings* engine_settings;
		
		int flag;
		
		public:
			character ();
			character (float, float, float, settings*);
			void update ();
			void setXdown (int);
			void setYdown (int);
			void setZdown (int);
			void setZrdown (int);
			void setXrdown (int);
			void setFlag (int);
			glm::mat4 getView ();
			glm::mat4 getProj ();
			float getXpos ();
			float getYpos ();
			float getZpos ();
			int getFlag ();
	};
	
	#define CHARACTER
#endif