#include <craft/platformSpecification.hpp>

#include <craft/shaderVoxel.hpp>
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

settings* engine_settings = new settings();
character* player = new character(0.0f, 0.0f, 74.0f, engine_settings->getRatio());

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
        player->setXdown( -1 );
		
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
        player->setXdown( 1 );
		
    if ( (key == GLFW_KEY_LEFT && action == GLFW_RELEASE) || (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE) )
        player->setXdown( 0 );
    
		
    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
        player->setYdown( -1 );
		
    if (key == GLFW_KEY_UP && action == GLFW_PRESS)
        player->setYdown( 1 );
		
    if ( (key == GLFW_KEY_DOWN && action == GLFW_RELEASE) || (key == GLFW_KEY_UP && action == GLFW_RELEASE) )
        player->setYdown( 0 );
    
	
    if (key == GLFW_KEY_W && action == GLFW_PRESS)
        player->setXrdown( -1 );
		
    if (key == GLFW_KEY_S && action == GLFW_PRESS)
        player->setXrdown( 1 );
    
	
    if (key == GLFW_KEY_D && action == GLFW_PRESS)
        player->setZrdown( -1 );
		
    if (key == GLFW_KEY_A && action == GLFW_PRESS)
        player->setZrdown( 1 );
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

GLFWwindow* init (settings* engine_settings, character* player) {
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

void threadPrimary (GLFWwindow* window, chunkController* chunkController01, character* player, shaderVoxel* shader) {
	
	//Set Frame-rate
	chrono::milliseconds framerate( 1000 / 60 );
	
	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	
    while (!glfwWindowShouldClose(window))
    {
    	//Start Timer
    	auto start_time = chrono::high_resolution_clock::now();
		
		// Clearing Buffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// Update
		player->updateUni(shader);
		
		chunkController01->updateBuffer();
		
        //Render
        chunkController01->render(player, shader);
        
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

void threadSecondary (GLFWwindow* window, chunkController* chunkController01, character* player) {
	
	//Set Frame-rate
	chrono::milliseconds framerate( 1000 / 20 );
	
    while (!glfwWindowShouldClose(window))
    {
    	//Start Timer
    	auto start_time = chrono::high_resolution_clock::now();
        
        //Update
        player->update(chunkController01);
		
		//Sleep
		chrono::milliseconds looptime( chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start_time).count() );
		if (looptime < framerate)
		{
			this_thread::sleep_for( framerate - looptime );
		}
		
		//cout << "Logic thread frame rate is: " << 1000 / chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start_time).count() << endl;
    }
}

void threadTertiary (GLFWwindow* window, chunkController* chunkController01, character* player) {
	
	//Set Frame-rate
	chrono::milliseconds framerate( 1000 / 20 );
	
    while (!glfwWindowShouldClose(window))
    {
    	//Start Timer
    	auto start_time = chrono::high_resolution_clock::now();
        
        
        //Update
		chunkController01->updateSegFlag(player);
		chunkController01->updateData(player);
		
		//Sleep
		chrono::milliseconds looptime( chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start_time).count() );
		if (looptime < framerate)
		{
			this_thread::sleep_for( framerate - looptime );
		}
		
		//cout << "Data thread frame rate is: " << 1000 / chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start_time).count() << endl;
    }
}

int main(void)
{
	GLFWwindow* window = init(engine_settings, player);
	
	shaderVoxel* shader = new shaderVoxel(player);
	
	chunkController* chunkController01 = new chunkController(player);
	
	thread threadLogic(threadSecondary, window, chunkController01, player);
	thread threadData(threadTertiary, window, chunkController01, player);
	
	threadPrimary(window, chunkController01, player, shader);
	
	threadLogic.join();
	threadData.join();
	
    glfwDestroyWindow(window);
    
    delete chunkController01;
    delete shader;
    delete player;
    delete engine_settings;
	
    glfwTerminate();
    exit(EXIT_SUCCESS);
}