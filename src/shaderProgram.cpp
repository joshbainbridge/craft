#include <craft/shaderProgram.hpp>

#include <string>
#include <iostream>
#include <fstream>
using namespace std;

std::string readFile(const char *filePath)
{
    std::string content;
    std::ifstream fileStream(filePath, std::ios::in);

    if(!fileStream.is_open()) {
        std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
        return "";
    }

    std::string line = "";
    while(!fileStream.eof())
    {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}

GLuint createShader (const char* source_dir, GLenum shader_type)
{
	GLuint shader = glCreateShader(shader_type);
	
	string shader_string = readFile(source_dir);
	const char* source = shader_string.c_str();
	
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);
	
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	
	if (status == !GL_TRUE)
	{
		char buffer[512];
		glGetShaderInfoLog(shader, 512, NULL, buffer);
		std::cout << source_dir << ":" << std::endl << buffer << std::endl;
	}
	
	return shader;
}

GLuint createProgram (GLuint vertex_shader, GLuint fragment_shader)
{
	GLuint program_id = glCreateProgram();
	glAttachShader(program_id, vertex_shader);
	glAttachShader(program_id, fragment_shader);
    glBindFragDataLocation(program_id, 0, "outColor");
	glLinkProgram(program_id);
	
	return program_id;
}

shaderProgram::shaderProgram ()
{
}

shaderProgram::shaderProgram (const char* vert_source_dir, const char* frag_source_dir)
{
	init (vert_source_dir, frag_source_dir);
}

void shaderProgram::init (const char* vert_source_dir, const char* frag_source_dir)
{
	vertex_shader = createShader(vert_source_dir, GL_VERTEX_SHADER);
	fragment_shader = createShader(frag_source_dir, GL_FRAGMENT_SHADER);
	
	program_id = createProgram(vertex_shader, fragment_shader);
}

void shaderProgram::createVert (const char* vert_source_dir)
{
	vertex_shader = createShader(vert_source_dir, GL_VERTEX_SHADER);
}

void shaderProgram::createFrag (const char* frag_source_dir)
{
	fragment_shader = createShader(frag_source_dir, GL_FRAGMENT_SHADER);
}

void shaderProgram::createProg ()
{
	program_id = createProgram(vertex_shader, fragment_shader);
}

void shaderProgram::setVert (GLuint input_vert)
{
	vertex_shader = input_vert;
}

void shaderProgram::setFrag (GLuint input_frag)
{
	fragment_shader = input_frag;
}

void shaderProgram::setProg (GLuint input_prog)
{
	program_id = input_prog;
}

GLuint shaderProgram::getVert ()
{
	return vertex_shader;
}

GLuint shaderProgram::getFrag ()
{
	return fragment_shader;
}

GLuint shaderProgram::getProg ()
{
	return program_id;
}