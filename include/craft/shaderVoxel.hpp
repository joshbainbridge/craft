#ifndef SHADERVOXEL
	#define SHADERVOXEL
	
	#include <craft/platformSpecification.hpp>
	#include <craft/shaderProgram.hpp>
	#include <craft/character.hpp>
	
	#define GLM_FORCE_RADIANS
	#include <glm/glm.hpp>
	#include <glm/gtc/matrix_transform.hpp>
	#include <glm/gtc/type_ptr.hpp>
	
	class shaderVoxel {
		
		GLfloat vertices[64];
		GLuint elements[36];
		
		shaderProgram shader;
		
		GLuint vao;
		GLuint vbo;
		GLuint ebo;
		
		GLuint coordAttrib;
		GLuint scaleAttrib;
		GLuint vertAttrib;
		GLuint uvAttrib;
		GLuint normAttrib;
		
		GLuint uniView;
		GLuint uniProj;
		
		public:
			shaderVoxel ();
			shaderVoxel (character*);
			void init (character*);
			void useProgram ();
			GLuint getUniView ();
			GLuint getUniProj ();
			GLuint getCoordAttrib ();
			GLuint getScaleAttrib ();
	};
	
#endif