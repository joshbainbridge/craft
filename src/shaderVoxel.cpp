#include <craft/shaderVoxel.hpp>

shaderVoxel::shaderVoxel ()
{
}

shaderVoxel::shaderVoxel (character* player)
{
	init (player);
}

void shaderVoxel::init (character* player)
{
	
	GLfloat vertices_input[40] =
	{
		0.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 0.0f, 1.0f
	};
	
	for (int i = 0; i < 40; i++)
	{
		vertices[i] = vertices_input[i];
	}
	
	GLuint elements_input[36] =
	{
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
	
	for (int i = 0; i < 36; i++)
	{
		elements[i] = elements_input[i];
	}
	
	// Attribute Buffer
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
	// Shader
	shader.init( "../craft-master/shaders/voxel.vert", "../craft-master/shaders/voxel.frag" );
	glUseProgram(shader.getProg());
	
	vertAttrib = glGetAttribLocation(shader.getProg(), "vertex");
	uvAttrib = glGetAttribLocation(shader.getProg(), "uv");
	coordAttrib = glGetAttribLocation(shader.getProg(), "coordinate");
	scaleAttrib = glGetAttribLocation(shader.getProg(), "scale");
	
	uniView = glGetUniformLocation(shader.getProg(), "view");
	uniProj = glGetUniformLocation(shader.getProg(), "proj");
	
	glEnableVertexAttribArray(vertAttrib);
	glEnableVertexAttribArray(uvAttrib);
	glEnableVertexAttribArray(coordAttrib);
	glEnableVertexAttribArray(scaleAttrib);
	
	glVertexAttribDivisor(vertAttrib, 0);
	glVertexAttribDivisor(uvAttrib, 0);
	glVertexAttribDivisor(coordAttrib, 1);
	glVertexAttribDivisor(scaleAttrib, 1);
	
	
	// Vertex Buffer
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(vertAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(float)*5, 0);
	glVertexAttribPointer(uvAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(float)*5, (const void*) (sizeof(float)*3));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	// Element Buffer
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	// Camera - Transform
	glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr( player->getView() ));
	
	// Camera - Perspective
	glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr( player->getProj() ));
}

void shaderVoxel::useProgram ()
{
	glUseProgram(shader.getProg());
}

GLuint shaderVoxel::getUniView ()
{
	return uniView;
}

GLuint shaderVoxel::getUniProj ()
{
	return uniProj;
}

GLuint shaderVoxel::getCoordAttrib ()
{
	return coordAttrib;
}

GLuint shaderVoxel::getScaleAttrib ()
{
	return scaleAttrib;
}