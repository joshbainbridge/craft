#include <craft/platformSpecification.hpp>

#include <craft/shaderProgram.hpp>
#include <craft/settings.hpp>
#include <craft/simplex.hpp>
#include <craft/segment.hpp>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <chrono>
#include <thread>
#include <iostream>
using namespace std;

settings engine_settings;
float x_pos = 7.5;
float y_pos = 7.5;
float z_pos = 7.5;
int seg_ypos = 0;

GLFWwindow* createWindow() {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_SAMPLES, 2);
	
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	
    GLFWwindow* window = glfwCreateWindow(engine_settings.getResX(), engine_settings.getResY(), "Craft", NULL,NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    
	glfwSwapInterval(0);
	
	return window;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
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
		
    if (key == GLFW_KEY_S && action == GLFW_PRESS)
        seg_ypos++;
}

void errorContext() {
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

GLFWwindow* init () {
	int err = glfwInit();
    if (!err)
	{
        exit(EXIT_FAILURE);
	}
	
	GLFWwindow* window = createWindow();
	
    glfwSetKeyCallback(window, keyCallback);
	
	errorContext();
	
	return window;
}

void threadPrimary (GLFWwindow* window, segment* segment01, segment* segment02, segment* segment03, segment* segment04) {
	// Data
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
	
	// Attribute Buffer
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
	// Shader
	shaderProgram shader01( "../Craft-master/shaders/vertexShader.vtx", "../Craft-master/shaders/fragmentShader.frg" );
	glUseProgram(shader01.getProg());
	
	GLuint cenAttrib = glGetAttribLocation(shader01.getProg(), "centre");
	GLuint posAttrib = glGetAttribLocation(shader01.getProg(), "position");
	GLuint colAttrib = glGetAttribLocation(shader01.getProg(), "color");
	
	GLuint uni_view = glGetUniformLocation(shader01.getProg(), "view");
	GLuint uni_proj = glGetUniformLocation(shader01.getProg(), "proj");
	
	glEnableVertexAttribArray(cenAttrib);
	glEnableVertexAttribArray(posAttrib);
	glEnableVertexAttribArray(colAttrib);
	
	glVertexAttribDivisor(posAttrib, 0);
	glVertexAttribDivisor(colAttrib, 0);
	glVertexAttribDivisor(cenAttrib, 1);
	
	// Vertex Buffer
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(float)*6, 0);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(float)*6, (const void*) (sizeof(float)*3));
	
	// Element Buffer
	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
	
	// Camera - Look At
	glm::mat4 view = glm::lookAt(
		glm::vec3(x_pos, y_pos, z_pos),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f)
	);
	
	glUniformMatrix4fv(uni_view, 1, GL_FALSE, glm::value_ptr(view));
	
	// Camera - Perspective
	glm::mat4 proj = glm::perspective(
		45.0f,
		engine_settings.getRatio(),
		1.0f,
		50.0f
	);
	
	glUniformMatrix4fv(uni_proj, 1, GL_FALSE, glm::value_ptr(proj));
	
	//Loop Setup Code
	chrono::milliseconds framerate( 1000 / 60 );
	
	//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	
    while (!glfwWindowShouldClose(window))
    {
    	auto start_time = chrono::high_resolution_clock::now();
		
		// Camera - Look At
		view = glm::lookAt(
			glm::vec3(x_pos, y_pos, z_pos),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 1.0f)
		);
		
		glUniformMatrix4fv(uni_view, 1, GL_FALSE, glm::value_ptr(view));
		
		// Clearing Buffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        if (segment01->getflag() == 1) {
        	segment01->updateBuffer();
        }
		
		// Render
		segment01->render();
		segment02->render();
		segment03->render();
		segment04->render();
        
        // Swap Buffer
        glfwSwapBuffers(window);
		
		glfwPollEvents();
        
		chrono::milliseconds looptime( chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start_time).count() );
		if (looptime < framerate)
		{
			this_thread::sleep_for( framerate - looptime );
		}
		
		//cout << "Primary thread frame rate is: " << 1000 / chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start_time).count() << endl;
    }
}

void threadSecond (GLFWwindow* window, segment* segment01, segment* segment02, segment* segment03, segment* segment04) {
	//Loop Setup Code
	chrono::milliseconds framerate( 1000 / 30 );
	
    while (!glfwWindowShouldClose(window))
    {
    	auto start_time = chrono::high_resolution_clock::now();
		
		if (segment01->getypos() != seg_ypos) {
			segment01->update(0, seg_ypos, 0);
		}
		
		chrono::milliseconds looptime( chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start_time).count() );
		if (looptime < framerate)
		{
			this_thread::sleep_for( framerate - looptime );
		}
		
		//cout << "Logic thread frame rate is: " << 1000 / chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start_time).count() << endl;
    }
}

void threadThird (GLFWwindow* window) {
}

int main(void)
{
	GLFWwindow* window = init();
	
	segment *segment01 = new segment(0, 0, 0, 0);
	segment *segment02 = new segment(0, -1, 0, 0);
	segment *segment03 = new segment(0, 0, -1, 0);
	segment *segment04 = new segment(0, -1, -1, 0);
	
	thread threadLogic(threadSecond, window, segment01, segment02, segment03, segment04);
	thread threadData(threadThird, window);
	
	threadPrimary(window, segment01, segment02, segment03, segment04);
	
	threadLogic.join();
	threadData.join();
    
    delete segment01;
    delete segment02;
    delete segment03;
    delete segment04;
	
    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}