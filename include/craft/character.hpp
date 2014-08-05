#ifndef CHARACTER
	#include <craft/platformSpecification.hpp>
	#include <craft/settings.hpp>
	
	#include <glm/glm.hpp>

	class character {
		glm::mat4 view;
		glm::mat4 proj;
		
		float xpos, ypos, zpos;
		float zrot, xrot;
		
		settings* engine_settings;
		
		int flag;
		
		public:
			character ();
			character (float, float, float, settings*);
			void update ();
			void setXpos (float);
			void setYpos (float);
			void setZpos (float);
			void setZrot (float);
			void setXrot (float);
			glm::mat4 getView ();
			glm::mat4 getProj ();
			float getXpos ();
			float getYpos ();
			float getZpos ();
			float getZrot ();
			float getXrot ();
	};
	
	#define CHARACTER
#endif