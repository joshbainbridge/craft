#ifndef CHARACTER
	#define CHARACTER
	
	#include <craft/platformSpecification.hpp>
	#include <craft/plane.hpp>
	
	#include <glm/glm.hpp>
	
	//Forward reference
	class shaderVoxel;
	class chunkController;
	
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
		plane planes[7];
		
		float fov;
		float ratio;
		float nclip;
		float fclip;
		int scale;
		
		int size;
		
		int xseg, yseg;
		
		float xpos, ypos, zpos;
		int xdown, ydown, zdown;
		float xvel, yvel, zvel;
		
		float zrot, xrot;
		int zrdown, xrdown;
		float zrvel, xrvel;
		float xlimitmax, xlimitmin;
		float zlimitmax, zlimitmin;
		
		int flag;
		
		// Frustum Calc Data
		glm::vec3 p;
		glm::vec3 d;
		glm::vec3 right;
		glm::vec3 up;
		float nearDist;
		float Hnear;
		float Wnear;
		float farDist;
		float Hfar;
		float Wfar;
		float cs;
		float sn;
		float xn;
		float yn;
		float zn;
		
		void velocity ();
		void collision ();
		void transform ();
		void frustumBuild ();
		void setFlagAuto();
		
		public:
			character ();
			character (float, float, float, float);
			void init ();
			void update (chunkController*);
			void updateUni(shaderVoxel*);
			int frustumCheck(float, float, float, float);
			void setXdown (int);
			void setYdown (int);
			void setZdown (int);
			void setXseg (int);
			void setYseg (int);
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
			int getXseg ();
			int getYseg ();
			float getFov ();
			float getNclip ();
			float getFclip ();
			int getFlag ();
	};
	
#endif