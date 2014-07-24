#ifndef PLATFORM_SPECIFICATION
	#include <craft/platformSpecification.hpp>
#endif

class shaderProgram {
	GLuint vertex_shader;
	GLuint fragment_shader;
	GLuint program_id;
	public:
		shaderProgram ();
		shaderProgram (const char* vert_source_dir, const char* frag_source_dir);
		void createVert (const char* vert_source_dir);
		void createFrag (const char* frag_source_dir);
		void createProg ();
		void setVert (GLuint input_vert);
		void setFrag (GLuint input_frag);
		void setProg (GLuint input_prog);
		GLuint getVert ();
		GLuint getFrag ();
		GLuint getProg ();
};