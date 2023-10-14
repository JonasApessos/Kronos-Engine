#include "Window.h"

Window::Window(
	int32 IniWidth, 
	int32 IniHeight, 
	string const& InsTitle) :
	iWidth(IniWidth),
	iHeight(IniHeight),
	sTitle(InsTitle)
{
	Initialize();
}

Window::Window(Window&& InrWindow) noexcept :
	iRatioX(InrWindow.iRatioX),
	iRatioY(InrWindow.iRatioY),
	iWidth(InrWindow.iWidth),
	iHeight(InrWindow.iHeight),
	sTitle(InrWindow.sTitle),
	rWindow(InrWindow.rWindow),
	rMonitor(InrWindow.rMonitor),
	rVidMode(InrWindow.rVidMode)	
{
	InrWindow.rWindow = nullptr;
	InrWindow.rMonitor = nullptr;
}

Window::Window(Window const& InrWindow) noexcept :
	iRatioX(InrWindow.iRatioX),
	iRatioY(InrWindow.iRatioY),
	iWidth(InrWindow.iWidth),
	iHeight(InrWindow.iHeight),
	sTitle(InrWindow.sTitle),
	rWindow(InrWindow.rWindow),
	rMonitor(InrWindow.rMonitor),
	rVidMode(InrWindow.rVidMode) {}

Window::~Window()
{
	Destroy();
}

Window& Window::operator=(Window const& InrWindow) noexcept
{
	if (this != &InrWindow)
	{
		iWidth = InrWindow.iWidth;
		iHeight = InrWindow.iHeight;
		iRatioX = InrWindow.iRatioX;
		iRatioY = InrWindow.iRatioY;
		sTitle = InrWindow.sTitle;
		rWindow = InrWindow.rWindow;
		rMonitor = InrWindow.rMonitor;
		rVidMode = InrWindow.rVidMode;
	}

	return *this;
}

Window& Window::operator=(Window&& InrWindow) noexcept
{
	if (this != &InrWindow)
	{
		iWidth = InrWindow.iWidth;
		iHeight = InrWindow.iHeight;
		iRatioX = InrWindow.iRatioX;
		iRatioY = InrWindow.iRatioY;
		sTitle = InrWindow.sTitle;
		rWindow = InrWindow.rWindow;
		rMonitor = InrWindow.rMonitor;
		rVidMode = InrWindow.rVidMode;

		InrWindow.rWindow = nullptr;
		InrWindow.rMonitor = nullptr;
	}

	return *this;
}

void Window::Destroy()
{
	if (rWindow != nullptr)
	{
		glfwDestroyWindow(rWindow);

		rWindow = nullptr;
	}

	if (rMonitor != nullptr)
	{
		delete rMonitor;

		rMonitor = nullptr;
	}
}

void Window::SetAspect(float InfAspectScalar)
{
	iRatioY = iRatioX = (InfAspectScalar > 1) ? InfAspectScalar : iRatioX;

	SetHeight(GetWidth());
}

void Window::SetAspect(float IniAspectX, float IniAspectY)
{
	iRatioX = (IniAspectX > 1.0f) ? IniAspectX : 1.0f;
	iRatioY = (IniAspectY > 1.0f) ? IniAspectY : 1.0f;

	iHeight = GetAspectRatioHeight() * GetWidth();
}

void Window::OnResize(GLFWwindow* InrWindow, int32 IniWidth, int32 IniHeight)
{
	glViewport(0, 0, static_cast<GLsizei>(IniWidth), static_cast<GLsizei>(IniHeight));
	glfwSetWindowSize(InrWindow, IniWidth, IniHeight);
}

void Window::Initialize()
{
	CreateWindow();

	if (rWindow == nullptr)
		rLog.WriteAndDisplay("Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible.\n");

	glfwMakeContextCurrent(rWindow);

	glfwSetWindowAspectRatio(rWindow, iRatioX, iRatioY);
	glfwSetInputMode(rWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glViewport(0, 0, GetWidth(), GetHeight());

	glfwSetWindowSizeCallback(rWindow, Window::OnResize);

	printf("%s\n", glGetString(GL_VERSION));
}