#include <craft/platformSpecification.hpp>

#include <craft/shaderProgram.hpp>
#include <craft/settings.hpp>
#include <craft/simplex.hpp>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstdlib>
#include <string>
#include <iostream>
using namespace std;

settings engine_settings;
float x_pos = 7.5;
float y_pos = 7.5;
float z_pos = 7.5;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
		
    if (key == GLFW_KEY_LEFT && action == GLFW_REPEAT)
        x_pos += 0.5f;
		
    if (key == GLFW_KEY_RIGHT && action == GLFW_REPEAT)
        x_pos -= 0.5f;
		
    if (key == GLFW_KEY_DOWN && action == GLFW_REPEAT)
        y_pos += 0.5f;
		
    if (key == GLFW_KEY_UP && action == GLFW_REPEAT)
        y_pos -= 0.5f;
		
    if (key == GLFW_KEY_A && action == GLFW_REPEAT)
        z_pos += 0.5f;
		
    if (key == GLFW_KEY_Z && action == GLFW_REPEAT)
        z_pos -= 0.5f;
}

GLFWwindow* createWindow()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	
    GLFWwindow* window = glfwCreateWindow(engine_settings.getResX(), engine_settings.getResY(), "Craft", NULL,NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    
    glfwSetKeyCallback(window, keyCallback);
	glfwSwapInterval(0);
	
	return window;
}

void errorContext()
{
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		cout << "OpenGL error: " << error << endl;
		exit(EXIT_FAILURE);
	}
	
	#ifdef _WIN32
	glewExperimental = GL_TRUE;
	GLenum glewinit = glewInit();
	if (glewinit != GLEW_OK) {
		cout << "Glew not okay: " << glewinit << endl;
		exit(EXIT_FAILURE);
	}
	#endif
}

int main(void)
{
	int err = glfwInit();
    if (!err)
	{
        exit(EXIT_FAILURE);
	}
	
	GLFWwindow* window = createWindow();
	
	errorContext();
	
	//Shader
	shaderProgram shader01( "../craft/shaders/vertexShader.vtx", "../craft/shaders/fragmentShader.frg" );
	glUseProgram(shader01.getProg());
	
	//Data
	GLfloat vertices[] = {
		-0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f
	};
	
	GLuint elements[] = {
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
	
	GLfloat data[100][100][10];
	for (int i = 0; i < 100; i += 1) {
		for (int j = 0; j < 100; j += 1) {
			for (int k = 0; k < 10; k += 1) {
				
				data[i][j][k] = simplex_noise(2, (float) i * 0.05f, (float) j * 0.05f, (float) k * 0.05f) + ((float) k - 5) * 0.2;
				
			}
		}
	}
	
	int count = 0;
	GLfloat position[300000];
	for (int i = 0; i < 100; i += 1) {
		for (int j = 0; j < 100; j += 1) {
			for (int k = 0; k < 10; k += 1) {
				if (data[i][j][k] < 0) {
					if ( data[(i + 1) % 100][j][k] < 0 && data[(i - 1) % 100][j][k] < 0 && data[i][(j + 1) % 100][k] < 0 && data[i][(j - 1) % 100][k] < 0 && data[i][j][(k + 1) % 10] < 0 && data[i][j][(k - 1) % 10] < 0 ) {
					} else {
						position[count] = i - 50;
						position[count + 1] = j - 50;
						position[count + 2] = k - 5;
						count += 3;
					}
				}
			}
		}
	}
	
	//Attribute Buffer
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
	
	//Vertex Buffer
	GLuint pos_vbo;
	glGenBuffers(1, &pos_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, pos_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(position), position, GL_STREAM_DRAW);
	
	GLuint cenAttrib = glGetAttribLocation(shader01.getProg(), "centre");
	glEnableVertexAttribArray(cenAttrib);
	glVertexAttribPointer(cenAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, 0);
	
	//
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	GLuint posAttrib = glGetAttribLocation(shader01.getProg(), "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(float)*6, 0);
	
	GLuint colAttrib = glGetAttribLocation(shader01.getProg(), "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(float)*6, (const void*) (sizeof(float)*3));
	
	//Element Buffer
	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
	
	glVertexAttribDivisor(posAttrib, 0);
	glVertexAttribDivisor(colAttrib, 0);
	glVertexAttribDivisor(cenAttrib, 1);
	
	GLuint alpha = glGetUniformLocation(shader01.getProg(), "alpha");
	glUniform1f(alpha, 0.1f);
	
	glm::mat4 rotate;
	GLuint uni_rotate = glGetUniformLocation(shader01.getProg(), "rotate");
	
	//Camera
	glm::mat4 view = glm::lookAt(
		glm::vec3(x_pos, y_pos, z_pos),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f)
	);
	GLuint uni_view = glGetUniformLocation(shader01.getProg(), "view");
	glUniformMatrix4fv(uni_view, 1, GL_FALSE, glm::value_ptr(view));
	
	glm::mat4 proj = glm::perspective(
		45.0f,
		engine_settings.getRatio(),
		1.0f,
		50.0f
	);
	GLuint uni_proj = glGetUniformLocation(shader01.getProg(), "proj");
	glUniformMatrix4fv(uni_proj, 1, GL_FALSE, glm::value_ptr(proj));
	
	//Loop Setup Code
	double looptime;
	double framerate = (double) 1 / 60;
	float looplength = 0;
	//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	
    while (!glfwWindowShouldClose(window))
    {
		glfwSetTime((double) 0);
		looplength++;
		
		for (int i = 0; i < 100; i += 1) {
			for (int j = 0; j < 100; j += 1) {
				for (int k = 0; k < 10; k += 1) {
					
					data[i][j][k] = simplex_noise(1, (float) i * 0.05f + (float) looplength * 0.01f, (float) j * 0.05f, (float) k * 0.05f) + ((float) k - 5) * 0.2;
					
				}
			}
		}
		
		int count = 0;
		for (int i = 0; i < 100; i += 1) {
			for (int j = 0; j < 100; j += 1) {
				for (int k = 0; k < 10; k += 1) {
					if (data[i][j][k] < 0) {
						if ( data[(i + 1) % 100][j][k] < 0 && data[(i - 1) % 100][j][k] < 0 && data[i][(j + 1) % 100][k] < 0 && data[i][(j - 1) % 100][k] < 0 && data[i][j][(k + 1) % 10] < 0 && data[i][j][(k - 1) % 10] < 0 ) {
						} else {
							position[count] = i - 50;
							position[count + 1] = j - 50;
							position[count + 2] = k - 5;
							count += 3;
						}
					}
				}
			}
		}
		
		view = glm::lookAt(
			glm::vec3(x_pos, y_pos, z_pos),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 1.0f)
		);
		glUniformMatrix4fv(uni_view, 1, GL_FALSE, glm::value_ptr(view));
		
		rotate = glm::rotate(rotate, 0.01f, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uni_rotate, 1, GL_FALSE, glm::value_ptr(rotate));
		glUniform1f(alpha, glm::sin(looplength * 0.025)*0.1+0.9);
		
		glBindBuffer(GL_ARRAY_BUFFER, pos_vbo);
		/*
		for (int i = 0; i < count; i += 3) {
			position[i+2] += glm::sin(looplength * 0.04 + (position[i]*position[i+1])*0.1)*0.02;
		}
		*/
		glBufferData(GL_ARRAY_BUFFER, sizeof(position), position, GL_STREAM_DRAW);
		
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, count / 3);
        
        glfwSwapBuffers(window);
		looptime = glfwGetTime();
		if (looptime < framerate)
		{
			Sleep( ( framerate - looptime ) * 1000 );
		}
		
		//cout << (double) 1 / glfwGetTime() << endl;
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
