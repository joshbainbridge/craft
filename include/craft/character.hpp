#ifndef CHARACTER
	#include <craft/platformSpecification.hpp>
	#include <craft/settings.hpp>
	
	#include <glm/glm.hpp>
	
	struct frustum {
		
		glm::vec3 fc;
		glm::vec3 ftl;
		glm::vec3 ftr;
		glm::vec3 fbl;
		glm::vec3 fbr;
		glm::vec3 nc;
		glm::vec3 ntl;
		glm::vec3 ntr;
		glm::vec3 nbl;
		glm::vec3 nbr;
		
	};

	class character {
		glm::mat4 view;
		glm::mat4 proj;
		
		frustum view_frustum;
		
		float fov;
		float nclip;
		float fclip;
		
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
			void setFov (float input);
			void setNclip (float input);
			void setFclip (float input);
			void setFlag (int);
			glm::mat4 getView ();
			glm::mat4 getProj ();
			float getXpos ();
			float getYpos ();
			float getZpos ();
			float getFov ();
			float getNclip ();
			float getFclip ();
			int getFlag ();
	};
	
	#define CHARACTER
#endif