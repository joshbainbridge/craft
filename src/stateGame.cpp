#include <craft/stateGame.hpp>
#include <craft/shaderProgram.hpp>
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

float x_pos = 10.0f;
float y_pos = 10.0f;
float z_pos = 74.0f;

void threadPrimary (GLFWwindow* window, settings* engine_settings, chunkController* chunkController01) {
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
		glm::vec3(0.0f, 0.0f, 64.0f),
		glm::vec3(0.0f, 0.0f, 1.0f)
	);
	
	glUniformMatrix4fv(uni_view, 1, GL_FALSE, glm::value_ptr(view));
	
	// Camera - Perspective
	glm::mat4 proj = glm::perspective(
		45.0f,
		engine_settings->getRatio(),
		10.0f,
		80.0f
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
			glm::vec3(0.0f, 0.0f, 64.0f),
			glm::vec3(0.0f, 0.0f, 1.0f)
		);
		
		glUniformMatrix4fv(uni_view, 1, GL_FALSE, glm::value_ptr(view));
		
		// Clearing Buffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        //Render
        chunkController01->renderChunk();
        
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

void threadSecond (GLFWwindow* window) {
	//Loop Setup Code
	chrono::milliseconds framerate( 1000 / 30 );
	
    while (!glfwWindowShouldClose(window))
    {
    	auto start_time = chrono::high_resolution_clock::now();
		
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

stateGame::stateGame () {
}

stateGame::stateGame (GLFWwindow* window_input, settings* settings_input) {
	window = window_input;
	engine_settings = settings_input;
}

void stateGame::run () {
	GLuint loc = 0;
	chunkController* chunkController01 = new chunkController(&loc);
	
	thread threadLogic(threadSecond, window);
	thread threadData(threadThird, window);
	
	threadPrimary(window, engine_settings, chunkController01);
	
	threadLogic.join();
	threadData.join();
	
	delete chunkController01;
}