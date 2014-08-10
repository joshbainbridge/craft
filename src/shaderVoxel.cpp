#include <craft/shaderVoxel.hpp>

shaderVoxel::shaderVoxel () {
}

shaderVoxel::shaderVoxel (character* player_input) {
	init (player_input);
}

void shaderVoxel::init (character* player_input) {
	player = player_input;
	
	// Attribute Buffer
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
	// Shader
	shader.init( "../craft-master/shaders/vertexShader.vtx", "../craft-master/shaders/fragmentShader.frg" );
	glUseProgram(shader.getProg());
	
	vertAttrib = glGetAttribLocation(shader.getProg(), "vertex");
	uvAttrib = glGetAttribLocation(shader.getProg(), "uv");
	coordAttrib = glGetAttribLocation(shader.getProg(), "coordinate");
	
	uniView = glGetUniformLocation(shader.getProg(), "view");
	uniProj = glGetUniformLocation(shader.getProg(), "proj");
	
	glEnableVertexAttribArray(coordAttrib);
	glEnableVertexAttribArray(vertAttrib);
	glEnableVertexAttribArray(uvAttrib);
	
	glVertexAttribDivisor(vertAttrib, 0);
	glVertexAttribDivisor(uvAttrib, 0);
	glVertexAttribDivisor(coordAttrib, 1);
	
	// Vertex Buffer
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(vertAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(float)*5, 0);
	glVertexAttribPointer(uvAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(float)*5, (const void*) (sizeof(float)*3));
	
	// Element Buffer
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
	
	// Camera - Transform
	glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr( player->getView() ));
	
	// Camera - Perspective
	glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr( player->getProj() ));
}

void shaderVoxel::useProgram () {
	glUseProgram(shader.getProg());
}

GLuint* shaderVoxel::getUniView () {
	return &uniView;
}

GLuint* shaderVoxel::getUniProj () {
	return &uniProj;
}

GLuint* shaderVoxel::getCoordAttrib () {
	return &coordAttrib;
}