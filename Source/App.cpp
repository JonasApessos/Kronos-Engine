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
	if (!glfwInit())
		return false;

	switch(glfwGetPlatform())
		{
			case GLFW_PLATFORM_ERROR:
				rLog.WriteAndDisplay("Failed to load platform");
				break;
			
			case GLFW_PLATFORM_NULL:
				rLog.WriteAndDisplay("No platform found");
				break;
			
			case GLFW_PLATFORM_UNAVAILABLE:
				rLog.WriteAndDisplay("Platform is unavailable");
				break;
			
			case GLFW_PLATFORM_WAYLAND:
				rLog.WriteAndDisplay("Loaded Platform: Wayland");
				break;
			
			case GLFW_PLATFORM_X11:
				rLog.WriteAndDisplay("Loaded Platform: X11");
				break;
			
			case GLFW_PLATFORM_WIN32:
				rLog.WriteAndDisplay("Loaded Platform: Windows");
				break;
			
			case GLFW_PLATFORM_COCOA:
				rLog.WriteAndDisplay("Loaded Platform: Cocoa");
				break;

			default:
				rLog.WriteAndDisplay("Returned platform not recognised");
				break;
		}
	
	return true;
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

void App::GLFWErrorCallback(int IniErrorCode, const char* IncDescription)
{
	rLog.WriteAndDisplay(
		"GLFW Error Code : "
		+ to_string(IniErrorCode)
		+ ", Error Name: "
		+ GLFWErrorToString(static_cast<uint32>(IniErrorCode))
		+ ", Error Description: " + string(IncDescription), ELogSeverity::ELS_Error);
}