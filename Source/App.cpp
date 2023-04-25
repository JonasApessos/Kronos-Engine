#include "App.h"

App::App(int iniCommandIndex, char** IncCommandArguments)
{
	rLog = Log("LogGlew");

	InitGLFW();

	bIsInitSuccess = bIsGLFWInit;
}

App::~App()
{
	Destroy();
}

void App::Destroy()
{
	glfwTerminate();
}

void App::InitGLFW()
{
	// Initialise GLFW
	if (glfwInit())
	{
		glfwWindowHint(GLFW_SAMPLES, 8); // 2x antialiasing
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // We want OpenGL 4.6
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

		bIsGLFWInit = true;
		
	}
	else
		rLog.WriteAndDisplay("Failed to initialize GLFW", ELogSeverity::ELS_Critical);
}