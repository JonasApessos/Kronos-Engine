#include "App.h"

App::App(int iniCommandIndex, char** IncCommandArguments)
{
	rLog = Log("LogApp");

	bIsGLFWInit = InitGLFW();

	if(!bIsGLFWInit)
		rLog.WriteAndDisplay("Failed to initialize GLFW", ELogSeverity::ELS_Critical);
}

App::~App()
{
	Destroy();
}

void App::Destroy()
{
	DestroyImguiContext();
	glfwTerminate();
}

bool App::InitGLFW()
{
	// Initialise GLFW
	if (glfwInit())
	{
		glfwWindowHint(GLFW_SAMPLES, 4); // 2x antialiasing
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // We want OpenGL 4.6
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

		return true;
		
	}
	
	return false;
}

bool App::InitGlad()
{
	iGladVersion = gladLoadGL((GLADloadfunc)glfwGetProcAddress);

	if ( iGladVersion == 0)
		return false;

	return true;
}

bool App::InitImgui(Canvas const* InrCanvas)
{
	if(InrCanvas != nullptr)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		if(!ImGui_ImplGlfw_InitForOpenGL(InrCanvas->GetWindow(), true))
		{
			rLog.WriteAndDisplay("Imgui failed to bind to Opengl", ELogSeverity::ELS_Critical);
			return false;
		}

		if(!ImGui_ImplOpenGL3_Init(
			string(
				"#version " + to_string(GLAD_VERSION_MAJOR(iGladVersion)) + to_string(GLAD_VERSION_MINOR(iGladVersion)) + "0").c_str()))
		{
			rLog.WriteAndDisplay("Imgui failed to detect requested opengl version", ELogSeverity::ELS_Critical);
			return false;
		}
	}
	else
		return false;

	return true;
}

bool App::Init(Canvas const* InrCanvas)
{
	if(!(bIsGladInit = InitGlad()))
		rLog.WriteAndDisplay("Failed to init glad...clossing application", ELogSeverity::ELS_Critical);

	if(!(bIsImguiInit = InitImgui(InrCanvas)))
		rLog.WriteAndDisplay("Failed to init ImGui. Closing", ELogSeverity::ELS_Critical);

	return bIsInitSuccess = bIsGLFWInit & bIsGladInit & bIsImguiInit;
}

void App::DestroyImguiContext()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}