#include "Window.h"

Window::Window(
	int32 IniWidth, 
	int32 IniHeight, 
	const string& InsTitle) :
	iWidth(IniWidth),
	iHeight(IniHeight),
	sTitle(InsTitle)
{
	Initialize();
}

Window::Window(Window&& InrWindow) noexcept :
	iWidth(InrWindow.iWidth),
	iHeight(InrWindow.iHeight),
	iRatioX(InrWindow.iRatioX),
	iRatioY(InrWindow.iRatioY),
	sTitle(InrWindow.sTitle),
	rVidMode(InrWindow.rVidMode)
{
	rWindow = InrWindow.rWindow;
	rWindow = nullptr;

	rMonitor = InrWindow.rMonitor;
	rMonitor = nullptr;
}

Window::Window(const Window& InrWindow) noexcept :
	iWidth(InrWindow.iWidth),
	iHeight(InrWindow.iHeight),
	iRatioX(InrWindow.iRatioX),
	iRatioY(InrWindow.iRatioY),
	sTitle(InrWindow.sTitle),
	rVidMode(InrWindow.rVidMode)
{
	rWindow = InrWindow.rWindow;
	rMonitor = InrWindow.rMonitor;
}

Window::~Window()
{
	Destroy();
}

Window& Window::operator=(const Window& InrWindow) noexcept
{
	if (this != &InrWindow)
	{
		iWidth = InrWindow.iWidth;
		iHeight = InrWindow.iHeight;
		iRatioX = InrWindow.iRatioX;
		iRatioY = InrWindow.iRatioY;
		sTitle = InrWindow.sTitle;
		rVidMode = InrWindow.rVidMode;
		rWindow = InrWindow.rWindow;
		rMonitor = InrWindow.rMonitor;
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
		rVidMode = InrWindow.rVidMode;
		rWindow = InrWindow.rWindow;
		rMonitor = InrWindow.rMonitor;

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
	iRatioX = (IniAspectX > 1) ? IniAspectX : 1;
	iRatioY = (IniAspectY > 1) ? IniAspectY : 1;

	iHeight = GetAspectRatioHeight() * GetWidth();
}

void Window::Initialize()
{
	rLog = Log("LogWindow");

	CreateWindow();

	if (rWindow == nullptr)
		rLog.WriteAndDisplay("Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");

	glfwMakeContextCurrent(rWindow);

	glfwSetWindowAspectRatio(rWindow, iRatioX, iRatioY);
	glfwSetInputMode(rWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

}