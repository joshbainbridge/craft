#ifndef PLANE_H__
	#define PLANE_H__
	
	#ifndef GLM_FORCE_RADIANS
		#define GLM_FORCE_RADIANS
	#endif
	#include <glm/glm.hpp>

	class plane
	{
		glm::vec3 n;
		float h;
		
		public:
			plane ();
			plane (glm::vec3, glm::vec3, glm::vec3);
			void init(glm::vec3, glm::vec3, glm::vec3);
			int intersection(glm::vec3, float);
	};
	
#endif