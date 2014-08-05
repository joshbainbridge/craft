#include <craft/platformSpecification.hpp>

#include <craft/shaderProgram.hpp>
#include <craft/settings.hpp>
#include <craft/character.hpp>
#include <craft/chunkController.hpp>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <chrono>
#include <thread>
#include <iostream>
using namespace std;


static settings engine_settings;
static character player(10.0f, 10.0f, 74.0f, &engine_settings);


GLFWwindow* createWindow(settings* engine_settings) {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_SAMPLES, 2);
	
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	
    GLFWwindow* window = glfwCreateWindow(engine_settings->getResX(), engine_settings->getResY(), "Craft", NULL,NULL);
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
	
	
    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
        player.setXdown( -1 );
		
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
        player.setXdown( 1 );
		
    if ( (key == GLFW_KEY_LEFT && action == GLFW_RELEASE) || (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE) )
        player.setXdown( 0 );
    
		
    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
        player.setZdown( 1 );
		
    if (key == GLFW_KEY_UP && action == GLFW_PRESS)
        player.setZdown( -1 );
		
    if ( (key == GLFW_KEY_DOWN && action == GLFW_RELEASE) || (key == GLFW_KEY_UP && action == GLFW_RELEASE) )
        player.setZdown( 0 );
    
	
    if (key == GLFW_KEY_W && action == GLFW_PRESS)
        player.setZrdown( 1 );
		
    if (key == GLFW_KEY_S && action == GLFW_PRESS)
        player.setZrdown( -1 );
		
    if ( (key == GLFW_KEY_W && action == GLFW_RELEASE) || (key == GLFW_KEY_S && action == GLFW_RELEASE) )
        player.setZrdown( 0 );
    
	
    if (key == GLFW_KEY_A && action == GLFW_PRESS)
        player.setXrdown( 1 );
		
    if (key == GLFW_KEY_D && action == GLFW_PRESS)
        player.setXrdown( -1 );
		
    if ( (key == GLFW_KEY_A && action == GLFW_RELEASE) || (key == GLFW_KEY_D && action == GLFW_RELEASE) )
        player.setXrdown( 0 );
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

GLFWwindow* init (settings* engine_settings) {
	int err = glfwInit();
    if (!err)
	{
        exit(EXIT_FAILURE);
	}
	
	GLFWwindow* window = createWindow(engine_settings);
	
    glfwSetKeyCallback(window, keyCallback);
	
	errorContext();
	
	return window;
}

void threadPrimary (GLFWwindow* window, chunkController* chunkController01, GLuint uni_view, GLuint uni_proj) {
	
	//Set Frame-rate
	chrono::milliseconds framerate( 1000 / 60 );
	
	//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	
    while (!glfwWindowShouldClose(window))
    {
    	//Start Timer
    	auto start_time = chrono::high_resolution_clock::now();
		
		// Clearing Buffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		if (player.getFlag() == 2) {
			glUniformMatrix4fv(uni_view, 1, GL_FALSE, glm::value_ptr( player.getView() ));
			glUniformMatrix4fv(uni_proj, 1, GL_FALSE, glm::value_ptr( player.getProj() ));
		}
        
        //Render
        chunkController01->renderChunk();
        
        // Swap Buffer
        glfwSwapBuffers(window);
		
		//Check Events
		glfwPollEvents();
        
        //Sleep
		chrono::milliseconds looptime( chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start_time).count() );
		if (looptime < framerate)
		{
			this_thread::sleep_for( framerate - looptime );
		}
		
		//cout << "Primary thread frame rate is: " << 1000 / chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start_time).count() << endl;
    }
}

void threadSecond (GLFWwindow* window) {
	
	//Set Frame-rate
	chrono::milliseconds framerate( 1000 / 20 );
	
    while (!glfwWindowShouldClose(window))
    {
    	//Start Timer
    	auto start_time = chrono::high_resolution_clock::now();
        
        //Update
        player.update();
		
		//Sleep
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
	GLFWwindow* window = init(&engine_settings);
	
	
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
	
	// Camera - Transform
	glUniformMatrix4fv(uni_view, 1, GL_FALSE, glm::value_ptr( player.getView() ));
	
	// Camera - Perspective
	glUniformMatrix4fv(uni_proj, 1, GL_FALSE, glm::value_ptr( player.getProj() ));
	
	
	
	
	chunkController* chunkController01 = new chunkController(&cenAttrib);
	
	thread threadLogic(threadSecond, window);
	thread threadData(threadThird, window);
	
	threadPrimary(window, chunkController01, uni_view, uni_proj);
	
	threadLogic.join();
	threadData.join();
	
	delete chunkController01;
	
    glfwDestroyWindow(window);
	
    glfwTerminate();
    exit(EXIT_SUCCESS);
}