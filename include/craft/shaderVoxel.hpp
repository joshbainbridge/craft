#ifndef SHADERVOXEL
	#include <craft/platformSpecification.hpp>
	#include <craft/shaderProgram.hpp>
	#include <craft/character.hpp>
	
	#define GLM_FORCE_RADIANS
	#include <glm/glm.hpp>
	#include <glm/gtc/matrix_transform.hpp>
	#include <glm/gtc/type_ptr.hpp>
	
	class shaderVoxel {
		
		character* player;
		
		GLfloat vertices[40] = {
			-0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f, 0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f, 0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
			 0.5f, -0.5f, -0.5f, 0.0f, 1.0f
		};
	
		GLuint elements[36] = {
			0, 1, 2,
			1, 2, 3,
			4, 5, 6,
			5, 6, 7,
			0, 1, 5,
			0, 5, 4,
			1, 3, 7,
			1, 7, 5,
			2, 3, 6,
			3, 6, 7,
			0, 2, 4,
			2, 4, 6
		};
		
		shaderProgram shader;
		
		GLuint vao;
		
		GLuint vbo;
		
		GLuint ebo;
		
		GLuint coordAttrib;
		GLuint vertAttrib;
		GLuint uvAttrib;
	
		GLuint uniView;
		GLuint uniProj;
		
		public:
			shaderVoxel ();
			shaderVoxel (character*);
			void init (character*);
			void useProgram ();
			GLuint* getUniView ();
			GLuint* getUniProj ();
			GLuint* getCoordAttrib ();
	};
	
	#define SHADERVOXEL
#endif